#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;


bool sortGrowing(int a, int b)
{
    if (a < b) return true;
    else return false;
}

bool sortShrinking(int a, int b)
{
    if (a > b) return true;
    else return false;
}

class ButtonGroup
{
public:
    vector<sf::RectangleShape> buttons; //wizualny fizyczny zbior prostokatow buttonow
    vector<sf::Text*> text; //zbior textow - numery
    sf::Font font;

    ButtonGroup() //konsturkot tworzacy przyciski i tekst - podstawowe wartosci
    {
        font.loadFromFile("Oswald.ttf");
        for(int i=0; i<5;i++)
        {
            sf::RectangleShape tmp;

            tmp.setSize({25,25});
            tmp.setFillColor(sf::Color::Yellow);
            tmp.setOutlineColor(sf::Color::Black);
            tmp.setOutlineThickness(2);
            buttons.emplace_back(tmp);

            sf::Text *tmpText = new sf::Text;
            tmpText->setFont(font);
            tmpText->setCharacterSize(18);
            tmpText->setFillColor(sf::Color::Black);
            tmpText->setString(to_string(i));
            text.emplace_back(tmpText);
        }
    }

    ~ButtonGroup() //destruktor dynamicznych elementów - napisów na przyciskach (na końcu progarmu)
    {
        for(int i=0; i<5;i++)
        {
            delete text[i];
        }
    }

    void setPosition(int x, int y) //funkcja ustwiająca pozycje przycisków i tesktów
    {
        for(int i=4; i>=0;i--)
        {
            buttons[i].setPosition(x,y+ (4-i)*30);
            text[i]->setPosition(x+7,y+ (4-i)*30+2);
        }
    }

    void draw(sf::RenderWindow &window) //funkcja rysująca przysciki i teksty
    {
        for(int i=0; i<5;i++)
        {
            window.draw(buttons[i]);
            window.draw(*text[i]);
        }
    }
};

class Osoba //jednostki(osoby) na piętrach
{
public:
    float pietroDo; //oznaczenie numery piętra, do którego jedzie dana osboa - wykorzsytanie floata przez pólpiętra
    int waga = 70;
    sf::Texture texture;
    sf::Sprite body;
    sf::Text OznaczenieOsoby;
    sf::Font font;


    Osoba(float doPietra) : pietroDo((int)doPietra) //konstruktor jedno elementowy, który tworzy osobę z daną pietra
    {
        texture.loadFromFile("./corpo.png");
        body.setTexture(texture);
        body.setScale(0.2,0.2);


        font.loadFromFile("Oswald.ttf");

        OznaczenieOsoby.setFont(font);
        OznaczenieOsoby.setCharacterSize(24);
        OznaczenieOsoby.setFillColor(sf::Color::Black);
        OznaczenieOsoby.setOutlineThickness(3);
        OznaczenieOsoby.setOutlineColor(sf::Color::Yellow);
        OznaczenieOsoby.setString(to_string((int)doPietra));
    }


    void setPosition(int x, int y) //funkcja ustwiająca pozycje osoby i oznacznia
    {
        body.setPosition(x,y);
        OznaczenieOsoby.setPosition(x+42,y+40);
    }

    void move(int x, int y) //przesunięcie o dane wartosci równolegle osoby i oznaczenia
    {
        body.move(x,y);
        OznaczenieOsoby.move(x,y);
    }


    void draw(sf::RenderWindow &window) //rsyowanie
    {
        window.draw(body);
        window.draw(OznaczenieOsoby);
    }
};

class Pietro // jednostka pietra
{
public:
    sf::Texture texture;
    sf::Sprite body;
    vector<Osoba*> kolejka; //zbiór osób oczekujących na winde na pietree
    vector<Osoba*> wychodzacy; // zbiór osób wyschdozacych z windy
    ButtonGroup buttons; // intrakcja uzytkowanika na przyciskach


    Pietro()
    {
        texture.loadFromFile("./pietro.jpg");
        body.setTexture(texture);
        body.setScale(0.29f, 0.25f);
    }

    ~Pietro()
    {
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            delete kolejka[i];
        }
    }


    sf::Vector2f getPosition() //pobieramy pozycje pieter
    {
        return body.getPosition();
    }

    void add(int nr) //dodawanie osob do pietra
    {
        kolejka.emplace_back(new Osoba(nr)); //dodwanie osob do kolejki
        ustawieniaLudziPietro();
    }

    void ustawieniaLudziPietro() //ustawianie/update pozycji osób na pietrze --- działa na wszytko przez zbiór osób
    {
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            kolejka[i]->setPosition(225 + i*50, body.getPosition().y + 60);
        }
    }

    void draw(sf::RenderWindow &window) //rysowanie
    {
        window.draw(body);
        buttons.draw(window);
        for(int i = 0; i < (int)wychodzacy.size(); i++)
        {
            wychodzacy[i]->draw(window);
        }

        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            kolejka[i]->draw(window);
        }
    }
};

//tu koniec analizy końcowej

enum Kierunek
{
    Up, Down, Idle
};

static const char *enum_string[] = { "Up", "Down", "Idle" };

class Winda
{
public:
    sf::Texture texture;
    sf::Sprite body;
    vector<Osoba*> pasazerowie;
    float nrPietra = 0;
    int maxWaga = 600;
    int aktualnaWaga = 0;
    sf::Clock timer;
    int speed = 0;
    Kierunek kierunek = Idle;
    float cel = 0;
    vector<int> oczekujacy;
    vector<int> drugorzedneOczekujace;
    sf::Vector2f offset = {5,55};


    Winda(int maxWag) : maxWaga(maxWag) {}
    Winda()
    {
        texture.loadFromFile("./el.png");
        body.setTexture(texture);
        body.setScale(0.625f, 0.385f);
        body.setPosition(0, 724);
        //724 548 373 200 23



    }

    void setKierunek(Kierunek kier)
    {
        kierunek = kier;
        cout << "kierunek set to " << enum_string[kier] << endl;
        if (kierunek == Idle)
            speed = 0;
        else if (kierunek == Up)
            speed = -1;
        else if (kierunek == Down)
            speed = 1;
    }
    void setPosition(int yPos)
    {
        body.setPosition(body.getPosition().x, yPos);
        //ludzie w windzie
    }
    void ustawieniaPasazerow()
    {
        int j = 0;
        int counter = 0;
        for(int i = 0; i < pasazerowie.size(); i++)
        {
            if (counter == 4)
            {
                counter = 0;
                j++;
            }
            pasazerowie[i]->setPosition(body.getPosition().x + offset.x + 25*counter + j*10, body.getPosition().y + offset.y + j*10);
            counter++;
        }
    }


};

class SystemWindy
{
public:
    vector<Pietro*> pietra;
    Winda winda;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture shaftTexture;
    sf::Sprite shaftSprite;
    sf::Texture boxTexture;
    sf::Sprite boxSprite;
    sf::Texture floorbackgroundTexture;
    sf::Sprite floorbackgroundSprite;
    vector<int> kolejkaPieter;
    sf::Vector2f maxMinPietro = {0,4};
    bool stop = false;
    sf::Clock stopTimer;
    sf::Clock endClock;
    sf::Font font;
    sf::Text WyswietlanieWagi;

    SystemWindy(int iloscPieter, sf::RenderWindow &window)
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



        for (int i = 725; i >= 0; i -= 175)
        {
            Pietro *tmp = new Pietro;
            tmp->body.setPosition(187, i);
            tmp->buttons.setPosition(670, i);
            pietra.emplace_back(tmp);
        }

        for(int i = 0; i < pietra.size(); i++)
        {
            pietra[i]->buttons.buttons[i].setFillColor(sf::Color::Black);
        }
    }

    void dodajDoKolejkiPieter(int pietro)
    {
        //cout << 0.1 << endl;
        if (winda.kierunek == Up || winda.kierunek == Idle)
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
        else if (winda.kierunek == Down)
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

    void events(sf::RenderWindow &window, sf::Event &event)
    {
        for(int i = 0; i < pietra.size(); i++)
        {
            for(int j = 0; j < 5; j++)
            {
                if (pietra[i]->buttons.buttons[j].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    if (i != j)
                    {
                        pietra[i]->add(j);
                        dodajDoKolejkiPieter(i);
                    }
                }
            }
        }

    }

    //    void dodajOsobe(int pietro, Osoba os)
    //    {
    //        if (pietro >= 0 && pietro < (int)pietra.size())
    //        {
    //            //pietra[pietro].push(os);
    //        }
    //        else
    //        {
    //            cout << "Pietro " << pietro << " nie istnieje" << endl;
    //        }
    //    }

    void moveWinda(bool czekac)
    {
        //cout << "czekac" << czekac << endl;
        //winda.setPosition(pietra[pietro]->getPosition().y);
        //winda.cel = pietro;
        //cout << winda.cel << " " << winda.nrPietra << endl;

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
        else winda.speed = 0;
    }
    bool czyCzekac()
    {
        //(int)(winda.nrPietra*10) % 10 == 0 &&)
        return false;
    }
    void test()
    {
        //cout << 1 << endl;

        //moveWinda(false);
        if (winda.nrPietra != winda.cel)
        {
            if (stopTimer.getElapsedTime().asMilliseconds() > 1000)
            {
                stop = false;
            }
            //cout << winda.cel << " " << winda.nrPietra << endl;
            moveWinda(false || stop);
            //cout << 2 << endl;
        }
        else
        {
            if (!stop)
            {
                stopTimer.restart();
                stop = true;
            }
            //cout << 3 << endl;

            moveWinda(true);
            //            //usuwa pietro z oczekujacych
            //            for(int i = 0; i < winda.pasazerowie.size(); i++)
            //            {
            //                if (winda.oczekujacy.size() != 0 && winda.oczekujacy[i] == winda.cel)
            //                {
            //                    cout << "jestem na celu " << winda.cel << endl;
            //                    winda.oczekujacy.erase(winda.oczekujacy.begin());
            //                }
            //            }
            //cout << 1 << endl;
            //sprawdzic czy ktos ma wyjsc
            //usunac osoby z windy
            //cout << 4 << endl;
            for(int i = 0; i < winda.pasazerowie.size(); i++)
            {
                if (winda.pasazerowie.size() != 0)
                {
                    if ((int)winda.nrPietra == winda.pasazerowie[i]->pietroDo) //sprawdzic czy pasazer w windzie jest na pietrze do ktorego chce isc
                    {
                        //cout << "pasaz size" << winda.pasazerowie.size() << " oczekujacy size" << winda.oczekujacy.size() << endl;
                        winda.aktualnaWaga -= winda.pasazerowie[i]->waga; //odjac wage od windy
                        pietra[(int)winda.nrPietra]->wychodzacy.emplace_back(winda.pasazerowie[i]); //dodac osobe do wychodzacych na pietrze
                        pietra[(int)winda.nrPietra]->wychodzacy[pietra[(int)winda.nrPietra]->wychodzacy.size()-1]->setPosition(pietra[(int)winda.nrPietra]->body.getPosition().x + rand() % 50, pietra[(int)winda.nrPietra]->body.getPosition().y+60); //ustawic pozycje osoby wychodzacej na pietrze
                        winda.pasazerowie.erase(winda.pasazerowie.begin()+i); //usunac osobe z windy
                        if (winda.pasazerowie.size() == 0) //sprawdza czy istnieja nadal pasazerowie w windzie aby rozpoczac czekanie 5 sekundowe i restart do pietra 0
                            endClock.restart(); //restart zegara koncowego
                        i--;
                    }
                }
            }

            for(int i = 0; i < winda.oczekujacy.size(); i++)
            {
                cout << winda.oczekujacy[i] << " ";
            }
            cout << endl;
            for(int i = 0; i < winda.drugorzedneOczekujace.size(); i++)
            {
                cout << winda.drugorzedneOczekujace[i] << " ";
            }
            cout << endl << "///" << endl;

            //cout << 2 << endl;
            //sprawdzic czy mozna wejsc
            //sprawdzic czy ktos chce wejsc
            //dodac te osoby do windy
            //cout << (int)winda.nrPietra << endl;
            //cout << "bobber" << endl;
            //cout << 5 << endl;
            for(int i = 0; i < pietra[(int)winda.nrPietra]->kolejka.size(); i++)
            {
                //cout << "bob" << endl;
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
            //cout << 6 << endl;
            pietra[(int)winda.nrPietra]->ustawieniaLudziPietro();
            winda.ustawieniaPasazerow();
            //cout << 7 << endl;
            if (winda.kierunek == Up || winda.kierunek == Idle) sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortGrowing);
            else if (winda.kierunek == Down) sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortShrinking);
            if (winda.kierunek == Up || winda.kierunek == Idle) sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortShrinking);
            else if (winda.kierunek == Down) sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortGrowing);
            //cout << 8 << endl;
        }
        //cout << 9 << endl;
        //cout << enum_string[winda.kierunek] << " " << winda.nrPietra << " " << winda.cel << " " << stop << endl;
        //usuwa z listy oczekujacej pietro na ktorym sie znajdujemy
        for(int i = 0; i < winda.oczekujacy.size(); i++)
        {
            if (winda.oczekujacy[i] == winda.nrPietra)
            {
                winda.oczekujacy.erase(winda.oczekujacy.begin()+i);
            }
        }
        if (!stop)
            stop = true;
        //ustawianie nastepnego celu windy
        if (winda.oczekujacy.size() == 0 && winda.drugorzedneOczekujace.size() == 0)
        {
            if (endClock.getElapsedTime().asMilliseconds() > 5000)
            {
                winda.cel = 0;
            }
            //cout << 1.1 << endl;
        }
        else if (winda.oczekujacy.size() == 0 && winda.drugorzedneOczekujace.size() != 0)
        {
            for(int i = 0; i < winda.drugorzedneOczekujace.size(); i++)
            {
                winda.oczekujacy.emplace_back(winda.drugorzedneOczekujace[i]);
            }
            winda.drugorzedneOczekujace.clear();
            winda.cel = winda.oczekujacy[0];
        }
        else
        {
            winda.cel = winda.oczekujacy[0];
        }

        //cout << 10 << endl;


        if (winda.body.getPosition().y > pietra[0]->body.getPosition().y)
        {
            winda.nrPietra = 0;
        }
        else
        {
            for(int i = 0; i < pietra.size(); i++)
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

    void windaMovement()
    {
        if(winda.timer.getElapsedTime().asMilliseconds() >= 5)
        {
            //cout << kier winda.speed << endl;
            winda.body.move(0,winda.speed);
            for(int i = 0; i < winda.pasazerowie.size(); i++)
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

    void drawScreen(sf::RenderWindow &window)
    {

        window.draw(backgroundSprite);
        window.draw(shaftSprite);
        window.draw(floorbackgroundSprite);

        window.draw(boxSprite);
        window.draw(WyswietlanieWagi);

        window.draw(winda.body);
        for(int i = 0; i < winda.pasazerowie.size(); i++)
        {
            winda.pasazerowie[i]->draw(window);
        }
        for(int i = 0; i < pietra.size(); i++)
        {
            pietra[i]->draw(window);
        }
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Elevator");
    SystemWindy systemWindy(5,window);
    srand(time(NULL));
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            systemWindy.events(window, event);
        }
        systemWindy.test();
        //cout << 11 << endl;
        systemWindy.windaMovement();
        //cout << 12 << endl;
        window.clear();
        systemWindy.drawScreen(window);
        window.display(); //wyświetlanie na ekranie - rzeczy narysowane w draw'ach

    }

    return 0;
}
