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
    vector<sf::RectangleShape> buttons; //ustaw jeszcze prawidlowe rozmiary i pozycje zeby pasowaly do pietra

    ButtonGroup()
    {
        for(int i=0; i<5;i++)
        {
            sf::RectangleShape tmp;
            tmp.setSize({25,25});
            tmp.setFillColor(sf::Color::Yellow);
            buttons.emplace_back(tmp);
        }
    }

    //    void pressEvent(sf::RenderWindow &window, sf::Event &event)
    //    {
    //        for(int i=0; i<5;i++)
    //        {
    //            if (buttons[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    //            {
    //                cout << "KLIK " << i << endl;
    //            }
    //        }
    //    }

    void setPosition(int x, int y)
    {
        for(int i=4; i>=0;i--)
        {
            buttons[i].setPosition(x,y+ (4-i)*30);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        for(int i=0; i<5;i++)
        {
            window.draw(buttons[i]);
        }
    }
};

class Osoba //wszystko co jest w sf sprite jest w osoba teraz. tzn ze osoba to inna nazwa na sf sprite. osoba jest teraz sf sprite ktora tworzymy z elementami ponizej
{
public:
    float pietroDo;
    int waga = 70;
    sf::Texture texture;
    sf::Sprite body;
    sf::Text OznaczenieOsoby;
    sf::Font font;
    //sf font sf text



    Osoba(float doPietra) : pietroDo((int)doPietra)
    {
        texture.loadFromFile("./corpo.png");
        body.setTexture(texture);
        body.setScale(0.2,0.2);
        //ustawiasz font i text pamietaj o pozycji tez wzgledem osoby na pietrze

        font.loadFromFile("Oswald.ttf");

        OznaczenieOsoby.setFont(font);
        OznaczenieOsoby.setCharacterSize(24);
        OznaczenieOsoby.setFillColor(sf::Color::Black);
        OznaczenieOsoby.setOutlineThickness(3);
        OznaczenieOsoby.setOutlineColor(sf::Color::Yellow);
        OznaczenieOsoby.setString(to_string((int)doPietra));

    }


    void setPosition(int x, int y)
    {
        body.setPosition(x,y);
        OznaczenieOsoby.setPosition(x+42,y+40);
    }

    void move(int x, int y)
    {
        body.move(x,y);
        OznaczenieOsoby.move(x,y);
    }
    //    Osoba(float doPietra, int wag) : pietroDo((int)doPietra), waga(wag)
    //    {
    //        texture.loadFromFile("./stick.png");
    //        body.setTexture(texture);
    //        body.setScale(0.1,0.1);
    //    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(body);
        window.draw(OznaczenieOsoby);
    }
};

class Pietro
{
public:
    sf::Texture texture;
    sf::Sprite body;
    vector<Osoba*> kolejka;
    ButtonGroup buttons;


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

    sf::Vector2f getPosition()
    {
        return body.getPosition();
    }

    void add(int nr) //dodawanie osob do pietra
    {
        kolejka.emplace_back(new Osoba(nr));
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            kolejka[i]->setPosition(225 + i*50, body.getPosition().y + 60); //dopasuj przesuniecie na x, przesuniecie na y oraz odstepy na x miedzy ludzmi
        }
    }


    void draw(sf::RenderWindow &window)
    {
        window.draw(body);
        buttons.draw(window);
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            kolejka[i]->draw(window);
        }
    }
};

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
    sf::Vector2f offset = {5,5};

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
        //cout << "kierunek set to " << enum_string[kier] << endl;
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

//    void ustawianiePasazerow()
//    {
//        int j = 0;
//        int counter = 0;
//        for(int i = 0; i < pasazerowie.size(); i++)
//        {
//            if (counter == 4)
//            {
//                counter = 0;
//                j++;
//            }
//            else counter++;
//            pasazerowie[i]->setPosition(body.getPosition().x + offset.x + j*10, body.getPosition().y + offset.y + j*10);
//        }
//    }
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
    sf::Texture floorbackgroundTexture;
    sf::Sprite floorbackgroundSprite;
    vector<int> kolejkaPieter;
    sf::Vector2f maxMinPietro = {0,4};

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

        for (int i = 725; i >= 0; i -= 175)
        {
            Pietro *tmp = new Pietro;
            tmp->body.setPosition(187, i);
            tmp->buttons.setPosition(670, i);
            pietra.emplace_back(tmp);
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
            }
            else
            {
                winda.drugorzedneOczekujace.emplace_back(pietro);
            }
            sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortGrowing);
            sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortShrinking);
        }
        else if (winda.kierunek == Down)
        {
            if (pietro < winda.nrPietra)
            {
                winda.oczekujacy.emplace_back(pietro);
            }
            else
            {
                winda.drugorzedneOczekujace.emplace_back(pietro);
            }
            sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortShrinking);
            sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortGrowing);
        }
//        for(int i = 0; i < winda.oczekujacy.size(); i++)
//        {
//            cout << winda.oczekujacy[i] << " ";
//        }
//        cout << endl;
//        for(int i = 0; i < winda.drugorzedneOczekujace.size(); i++)
//        {
//            cout << winda.drugorzedneOczekujace[i] << " ";
//        }
//        cout << endl;
        //cout << 0.2 << endl;
        //cout << "size oczekujacych: " << winda.oczekujacy.size() << endl;
        //winda.cel = winda.oczekujacy[0];
        //cout << 0.3 << endl;
    }

    void events(sf::RenderWindow &window, sf::Event &event)
    {
        //eventy do guzikow pieter:
        for(int i = 0; i < pietra.size(); i++)
        {
            for(int j = 0; j < 5; j++)
            {
                if (pietra[i]->buttons.buttons[j].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    if (i != j) pietra[i]->add(j);
                    //moveWinda(j);
                    dodajDoKolejkiPieter(i);
                }
            }
        }
//        if (event.type == sf::Event::MouseMoved)
//        {
//            if (sf::Mouse::getPosition(window).y < winda.body.getPosition().y)
//            {
//                winda.setKierunek(Up);
//            }
//            else if (sf::Mouse::getPosition(window).y > winda.body.getPosition().y)
//            {
//                winda.setKierunek(Down);
//            }
//            else winda.setKierunek(Idle);
//        }

        //inne eventy
    }

    void dodajOsobe(int pietro, Osoba os)
    {
        if (pietro >= 0 && pietro < (int)pietra.size())
        {
            //pietra[pietro].push(os);
        }
        else
        {
            cout << "Pietro " << pietro << " nie istnieje" << endl;
        }
    }

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
                winda.setKierunek(Kierunek::Down);
            }
            else if (winda.cel > winda.nrPietra )
            {
                winda.setKierunek(Kierunek::Up);
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
        //cout << winda.oczekujacy.size() << " " << winda.drugorzedneOczekujace.size() << endl;
        //cout << winda.nrPietra << endl;
        if (winda.oczekujacy.size() == 0 && winda.drugorzedneOczekujace.size() == 0)
        {
            winda.cel = 0;
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
        //cout << winda.oczekujacy.size() << " " << winda.drugorzedneOczekujace.size() << endl;

        //moveWinda(false);
        if (winda.nrPietra != winda.cel)
        {
            moveWinda(false);
        }
        else
        {
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
            cout << 1 << endl;
            //sprawdzic czy ktos ma wyjsc
            //usunac osoby z windy
            for(int i = 0; i < winda.pasazerowie.size(); i++)
            {
                if (winda.nrPietra == winda.pasazerowie[i]->pietroDo)
                {
                    cout << "pasaz size" << winda.pasazerowie.size() << " oczekujacy size" << winda.oczekujacy.size() << endl;
                    winda.aktualnaWaga -= winda.pasazerowie[i]->waga;
                    winda.pasazerowie.erase(winda.pasazerowie.begin()+i);
                    winda.oczekujacy.erase(winda.oczekujacy.begin());
                    i--;
                }
            }
cout << 2 << endl;
            //sprawdzic czy mozna wejsc
            //sprawdzic czy ktos chce wejsc
            //dodac te osoby do windy
            for(int i = 0; i < pietra[winda.cel]->kolejka.size(); i++)
            {
                if (winda.aktualnaWaga+pietra[winda.cel]->kolejka[i]->waga <= winda.maxWaga)
                {
                    winda.oczekujacy.emplace_back(pietra[winda.cel]->kolejka[i]->pietroDo);
                    winda.pasazerowie.emplace_back(new Osoba(pietra[winda.cel]->kolejka[i]->pietroDo));
                    winda.aktualnaWaga += pietra[winda.cel]->kolejka[i]->waga;
                    pietra[winda.cel]->kolejka.erase(pietra[winda.cel]->kolejka.begin()+i);
                    i--;
                }
                else
                {
                    winda.drugorzedneOczekujace.emplace_back(pietra[winda.cel]->kolejka[i]->pietroDo);
                }
            }
            cout << 3 << endl;
            //cout << winda.pasazerowie.size() << endl;
            winda.ustawieniaPasazerow();

            if (winda.kierunek == Up || winda.kierunek == Idle) sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortGrowing);
            else if (winda.kierunek == Down) sort(winda.oczekujacy.begin(), winda.oczekujacy.end(), sortShrinking);
            if (winda.kierunek == Up || winda.kierunek == Idle) sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortShrinking);
            else if (winda.kierunek == Down) sort(winda.drugorzedneOczekujace.begin(), winda.drugorzedneOczekujace.end(), sortGrowing);
cout << 4 << endl;
        }
        //cout << 3 << endl;

//        for(int i = 0; i < winda.oczekujacy.size(); i++)
//        {
//            cout << winda.oczekujacy[i] << " ";
//        }
//        cout << endl;
        //cout << "nr " << winda.nrPietra << " " << "cel " << winda.cel << endl;


        //update current pietra na ktorym jestesmy wobec pozycji xy windy wzgledem pieterr (oraz ich niewidzialnych prostokatow)
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
    //cout << 4 << endl;
        //moveWinda(czyCzekac()); //operator a == b
        //powyzsza funkcja zatrzymuj na pietrze poniewaz jest na pietrze
        //dlatego bedzie potrzebny drugi warunek ktory np bedzie sprawdzal czy sa osoby na pietrze
    }

    void windaMovement()
    {
        if(winda.timer.getElapsedTime().asMilliseconds() >= 5)
        {
            winda.body.move(0,winda.speed);
            for(int i = 0; i < winda.pasazerowie.size(); i++)
            {
                winda.pasazerowie[i]->move(0,winda.speed);
            }
            winda.timer.restart();
        }
    }

    void drawScreen(sf::RenderWindow &window)
    {
        //rysujesz wszystko co ma byc na ekranie
        window.draw(backgroundSprite);
        window.draw(shaftSprite);
        window.draw(floorbackgroundSprite);

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
    Pietro pietro1;
    SystemWindy systemWindy(5,window);
    srand(time(NULL));
    while (window.isOpen())
    {
        //cout << 0 << endl;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            systemWindy.events(window, event);
        }
        systemWindy.test();
        systemWindy.windaMovement();
        //cout << 5 << endl;
        window.clear();
        systemWindy.drawScreen(window);
        window.display();
        //cout << 6 << endl;
    }

    return 0;
}
