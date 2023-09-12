#include "systemwindy.hpp"

SystemWindy::SystemWindy() //ustawianie danych poczatkowych dla elementów wizualnych
{
    backgroundTexture.loadFromFile("./background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1.0f, 1.0f);
    backgroundSprite.setPosition(638, 0);


    shaftTexture.loadFromFile("./shaft.png");
    shaftSprite.setTexture(shaftTexture);
    shaftSprite.setScale(0.5f, 1.55f);
    shaftSprite.setPosition(0, 0);


    floorbackgroundTexture.loadFromFile("./floorbackground.jpg");
    floorbackgroundSprite.setTexture(floorbackgroundTexture);
    floorbackgroundSprite.setScale(0.675f, 1.5f);
    floorbackgroundSprite.setPosition(187, 0);

    boxTexture.loadFromFile("./reklama.jpg");
    boxSprite.setTexture(boxTexture);
    boxSprite.setScale(0.175f, 0.175f);
    boxSprite.setPosition(947, 725);



    font.loadFromFile("Oswald.ttf");

    WyswietlanieWagi.setFont(font);
    WyswietlanieWagi.setCharacterSize(32);
    WyswietlanieWagi.setFillColor(sf::Color::Black);
    WyswietlanieWagi.setOutlineThickness(3);
    WyswietlanieWagi.setOutlineColor(sf::Color::Yellow);
    WyswietlanieWagi.setString(to_string((int)winda.aktualnaWaga));
    WyswietlanieWagi.setPosition(1025,850);



    for (int i = 725; i >= 0; i -= 175) //ustawianie danych dla pieter i przycisków - do użytku
    {
        Pietro *tmp = new Pietro;
        tmp->body.setPosition(187, i);
        tmp->buttons.setPosition(670, i);
        pietra.emplace_back(tmp);
    }

    for(int i = 0; i < (int)pietra.size(); i++) //dezaktywacja przycisków
    {
        pietra[i]->buttons.buttons[i].setFillColor(sf::Color::Black);
    }
}

void SystemWindy::dodajDoKolejkiPieter(int pietro) //w zależności od kierunku oraz pozycji pietra dodaje do ocz. lub durg.
{
    //cout << 0.1 << endl;
    if (sortingType)
    {
        if (pietro > winda.nrPietra)
        {
            winda.oczekujacy.emplace_back(pietro);
            //cout << "oczek" << endl;
        }
        else
        {
            winda.drugorzedneOczekujace.emplace_back(pietro);
            //cout << "drugo" << endl;
        }
        if (winda.oczekujacy.size() != 0) sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortGrowing);
        if (winda.drugorzedneOczekujace.size() != 0) sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortShrinking);
    }
    else if (!sortingType)
    {
        if (pietro < winda.nrPietra)
        {
            winda.oczekujacy.emplace_back(pietro);
            //cout << "oczek" << endl;
        }
        else
        {
            winda.drugorzedneOczekujace.emplace_back(pietro);
            //cout << "drugo" << endl;
        }
        if (winda.oczekujacy.size() != 0) sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortShrinking);
        if (winda.drugorzedneOczekujace.size() != 0) sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortGrowing);
    }


}

void SystemWindy::events(sf::RenderWindow &window, sf::Event &event) //kontrolowanie eventów (rzeczy, które dzieją się tylko raz przy wywołaniu)
{
    for(int i = 0; i < (int)pietra.size(); i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if (pietra[i]->buttons.buttons[j].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (i != j)
                {
                    pietra[i]->add(j); //dodanie osoby oczekujacej do pietra
                    dodajDoKolejkiPieter(i); //dodawanie osoby do kolejki windy (u góry)
                }
            }
        }
    }

}

void SystemWindy::moveWinda(bool czekac) //kontorla kierunku ruchu windy
{
    if (!czekac)
    {
        //            if (winda.cel == winda.nrPietra)
        //            {
        //                if (winda.kierunek != Idle) winda.setKierunek(Kierunek::Idle);
        //            }
        if (winda.cel < winda.nrPietra)
        {
            if (winda.kierunek != Down) winda.setKierunek(Kierunek::Down);
        }
        else if (winda.cel > winda.nrPietra )
        {
            if (winda.kierunek != Up)  winda.setKierunek(Kierunek::Up);
        }
        //cout << "winda ruszyla sie na pietro: " << pietro << endl;
    }
    else if (winda.kierunek != Idle) winda.setKierunek(Kierunek::Idle);
}

void SystemWindy::checkPietro() //ustalanie numeru piętra windy w czasie rzeczywistym
{
    if (winda.body.getPosition().y > pietra[0]->body.getPosition().y)
    {
        winda.nrPietra = 0;
    }
    else
    {
        for(int i = 0; i < (int)pietra.size(); i++)
        {
            if (winda.body.getPosition().y > pietra[pietra.size()-1-i]->body.getPosition().y - 5 && winda.body.getPosition().y < pietra[pietra.size()-1-i]->body.getPosition().y + 5)
            {
                //cout << "Winda jest na pietrze: " << pietra.size()-1-i << endl;
                winda.nrPietra = pietra.size()-1-i;
                break;
            }
            else if (winda.body.getPosition().y < pietra[pietra.size()-1-i]->body.getPosition().y + pietra[i]->body.getGlobalBounds().height + 30)
            {
                //cout << "Winda jest na pol pietrze: " << pietra.size()-2-i + 0.5 << endl;
                winda.nrPietra = pietra.size()-2-i + 0.5;
                break;
            }
        }
    }
}

void SystemWindy::debugCheckVectors()
{
    //    for(int i = 0; i < (int)winda.oczekujacy.size(); i++)
    //    {
    //        cout << winda.oczekujacy[i] << " ";
    //    }
    //    cout << endl;
    //    for(int i = 0; i < (int)winda.drugorzedneOczekujace.size(); i++)
    //    {
    //        cout << winda.drugorzedneOczekujace[i] << " ";
    //    }
    //    cout << endl << "///" << endl;
}

void SystemWindy::timerLogic() //ustawia keidy logika windy ma zajść - ta logika dzieje się RAZ, na każdym piętrze
{
    checkPietro();  // aktualizaujemy aktualny nrPietra
    if (winda.nrPietra == winda.cel)  //dzieje sie jednorazowo
    {
        moveWinda(true);    //zatrzymuje winde - speed = 0
        logikaWindy();      // wchodzenie osob wychdozenie sotrowanie + WYBÓR NOWEGO CELU!!! (co spodowuje efekt jednorazowy - opisane wczensiej)
        stopTimer.restart();    // timer kontrolujacy zatrzymanie windy
    }
    else    // dzieje sie w kazdej klatce oprócz jednej, w której dzieje się if!!!
    {
        int time = 1000; //czas czekania
        if (winda.oczekujacy.size() == 0 && winda.drugorzedneOczekujace.size() == 0) // warunek spradzajacy czy insteniją osoby - pietra oraz pasażerowie
            time = 5000; //czas czekania - 5 sekund oczekiwania na pasażera
        else time = 1000;
        if (stopTimer.getElapsedTime().asMilliseconds() > time) // nie ruszy sie winda dopóki ten warunek nie zostanie spełniony
        {
            moveWinda(false); // rusza windę
        }
    }
}

void SystemWindy::logikaWindy()
{
    //wychodzacy
    for(int i = 0; i < (int)winda.pasazerowie.size(); i++)
    {
        if (winda.pasazerowie.size() != 0)
        {
            if ((int)winda.nrPietra == winda.pasazerowie[i]->pietroDo) //sprawdzic czy pasazer w windzie jest na pietrze do ktorego chce isc
            {
                winda.aktualnaWaga -= winda.pasazerowie[i]->waga; //odjac wage od windy
                winda.pasazerowie[i]->setPosition(pietra[(int)winda.nrPietra]->body.getPosition().x + rand() % 50, pietra[(int)winda.nrPietra]->body.getPosition().y+60); //ustawic pozycje osoby wychodzacej na pietrze
                pietra[(int)winda.nrPietra]->wychodzacy.emplace_back(winda.pasazerowie[i]); //dodac osobe do wychodzacych na pietrze
                winda.pasazerowie.erase(winda.pasazerowie.begin()+i); //usunac osobe z windy
                i--;
            }
        }
    }

    //wchodzeniem do windy
    for(int i = 0; i < (int)pietra[(int)winda.nrPietra]->kolejka.size(); i++)
    {
        if (winda.aktualnaWaga+pietra[(int)winda.nrPietra]->kolejka[i]->waga <= winda.maxWaga)
        {
            //dodawanie celu pasazera do oczekujacych lub drugo w zaleznosci od kierunku windy i czy po drodze
            if (pietra[(int)winda.nrPietra]->kolejka[i]->pietroDo > winda.nrPietra && winda.kierunek == Up)
            {
                winda.oczekujacy.emplace_back(pietra[(int)winda.nrPietra]->kolejka[i]->pietroDo);
            }
            else if (pietra[(int)winda.nrPietra]->kolejka[i]->pietroDo < winda.nrPietra && winda.kierunek == Down)
            {
                winda.oczekujacy.emplace_back(pietra[(int)winda.nrPietra]->kolejka[i]->pietroDo);
            }
            else
            {
                winda.drugorzedneOczekujace.emplace_back(pietra[(int)winda.nrPietra]->kolejka[i]->pietroDo);
            }
            winda.pasazerowie.emplace_back(pietra[(int)winda.nrPietra]->kolejka[i]);
            winda.aktualnaWaga += pietra[(int)winda.nrPietra]->kolejka[i]->waga;
            pietra[(int)winda.nrPietra]->kolejka.erase(pietra[(int)winda.nrPietra]->kolejka.begin()+i);
            i--;
        }
        else
        {
            winda.drugorzedneOczekujace.emplace_back(pietra[(int)winda.nrPietra]->kolejka[i]->pietroDo);
        }
    }
    pietra[(int)winda.nrPietra]->ustawieniaLudziPietro();
    winda.ustawieniaPasazerow();
    if (sortingType) sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortGrowing);
    else if (!sortingType) sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortShrinking);
    if (sortingType) sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortShrinking);
    else if (!sortingType) sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortGrowing);




    for(int i = 0; i < (int)winda.oczekujacy.size(); i++)
    {
        if (winda.oczekujacy[i] == winda.nrPietra)
        {
            winda.oczekujacy.erase(winda.oczekujacy.begin()+i);
            i--;
        }
    }


    //ustawianie nastepnego celu windy
    if (winda.oczekujacy.size() == 0 && winda.drugorzedneOczekujace.size() == 0)
    {
        if (endClock.getElapsedTime().asMilliseconds() > 5000)
        {
            winda.cel = 0;
        }
    }
    else if (winda.oczekujacy.size() == 0 && winda.drugorzedneOczekujace.size() != 0)
    {
        for(int i = 0; i < (int)winda.drugorzedneOczekujace.size(); i++)
        {
            winda.oczekujacy.emplace_back(winda.drugorzedneOczekujace[i]);
        }
        winda.drugorzedneOczekujace.clear();
        winda.cel = winda.oczekujacy[0];
        sortingType = !sortingType;
    }
    else
    {
        winda.cel = winda.oczekujacy[0];
    }
}

void SystemWindy::windaMovement()
{
    if(winda.timer.getElapsedTime().asMilliseconds() >= 5)
    {
        //cout << enum_string[winda.kierunek] << " " << winda.speed << " " << stop << endl;
        winda.body.move(0,winda.speed);
        for(int i = 0; i < (int)winda.pasazerowie.size(); i++)
        {
            winda.pasazerowie[i]->move(0,winda.speed);
        }
        //cout << 11.1 << endl;
        for(int i = 0; i < (int)pietra.size(); i++)
        {
            for(int j = 0; j < (int)pietra[i]->wychodzacy.size(); j++)
            {
                if (pietra[i]->wychodzacy[j]->body.getPosition().x > 600)
                {
                    delete pietra[i]->wychodzacy[j];
                    pietra[i]->wychodzacy.erase(pietra[i]->wychodzacy.begin()+j);
                    j--;
                }
                else
                {
                    pietra[i]->wychodzacy[j]->move(1,0);
                }
            }
        }

        WyswietlanieWagi.setString(to_string(winda.aktualnaWaga));
        //cout << 11.2 << endl;
        winda.timer.restart();
    }
    //cout << 11.3 << endl;
}

void SystemWindy::drawScreen(sf::RenderWindow &window)
{

    window.draw(backgroundSprite);
    window.draw(shaftSprite);
    window.draw(floorbackgroundSprite);

    window.draw(boxSprite);
    window.draw(WyswietlanieWagi);

    window.draw(winda.body);
    for(int i = 0; i < (int)winda.pasazerowie.size(); i++)
    {
        winda.pasazerowie[i]->draw(window);
    }
    for(int i = 0; i < (int)pietra.size(); i++)
    {
        pietra[i]->draw(window);
    }
}
