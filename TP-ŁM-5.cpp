#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;

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
            tmp.setFillColor(sf::Color::Cyan);
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


    Osoba(float doPietra) : pietroDo((int)doPietra)
    {
        texture.loadFromFile("./stick.png");
        body.setTexture(texture);
        body.setScale(0.2,0.2);
    }
    //    Osoba(float doPietra, int wag) : pietroDo((int)doPietra), waga(wag)
    //    {
    //        texture.loadFromFile("./stick.png");
    //        body.setTexture(texture);
    //        body.setScale(0.1,0.1);
    //    }
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

        //        button.setFillColor(sf::Color::Green);
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

    void add(int nr)
    {
        kolejka.emplace_back(new Osoba(nr));
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            kolejka[i]->body.setPosition(175 + i*200, 100);
        }
    }


    void draw(sf::RenderWindow &window)
    {
        window.draw(body);
        buttons.draw(window);
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            window.draw(kolejka[i]->body);
        }
    }
};

enum Kierunek
{
    Up, Down, Idle
};

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
    int cel = 0;

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
        if (kierunek == Idle)
            speed = 0;
        else if (kierunek == Up)
            speed = -1;
        else
            speed = 1;
    }
    void setPosition(int yPos)
    {
        body.setPosition(body.getPosition().x, yPos);
        //ludzie w windzie
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
    sf::Texture floorbackgroundTexture;
    sf::Sprite floorbackgroundSprite;

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
                    moveWinda(j);
                }
            }
        }

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

//    void moveWinda(int pietro)
//    {
//        winda.setPosition(pietra[pietro]->getPosition().y);
//        winda.nrPietra = pietro;
//        cout << "winda ruszyla sie na pietro: " << pietro << endl;
//    }

    void moveWinda(int pietro)
    {

        //winda.setPosition(pietra[pietro]->getPosition().y);
        winda.cel = pietro;
        if (winda.cel == winda.nrPietra)
        {
            winda.setKierunek(Kierunek::Idle);
        }
        else if (winda.cel < winda.nrPietra )
        {
            winda.setKierunek(Kierunek::Down);
        }
        else if (winda.cel > winda.nrPietra )
        {
            winda.setKierunek(Kierunek::Up);
        }
        cout << winda.cel << " " << winda.kierunek << endl;
        //cout << "winda ruszyla sie na pietro: " << pietro << endl;
        //if()
    }

    void test()
    {
        if (winda.nrPietra == winda.cel)
        {
            winda.setKierunek(Idle);
        }
        for(int i = 0; i < pietra.size(); i++)
        {
            if (winda.body.getPosition().y > pietra[pietra.size()-1-i]->body.getPosition().y - 5 && winda.body.getPosition().y < pietra[pietra.size()-1-i]->body.getPosition().y + 5)
            {
                //cout << "Winda jest na pietrze: " << pietra.size()-1-i << endl;
                winda.nrPietra = pietra.size()-1-i;
                break;
            }
            else if (winda.body.getPosition().y < pietra[pietra.size()-1-i]->body.getPosition().y + pietra[i]->body.getGlobalBounds().height)
            {
                //cout << "Winda jest na pol pietrze: " << pietra.size()-2-i + 0.5 << endl;
                winda.nrPietra = pietra.size()-2-i + 0.5;
                break;
            }
        }
    }

    void windaMovement()
    {
        if(winda.timer.getElapsedTime().asMilliseconds() >= 5)
        {
            winda.body.move(0,winda.speed);
            winda.timer.restart();
        }

        //                {
//        for(int i = 0; i < pietra.size(); i++)
//        {
//            if (!pietra[i]->kolejka.empty())
//            {
//                if (winda.kierunek == Kierunek::Idle)
//                {
//                    int tmp = abs(winda.nrPietra - i);
//                    if (tmp == 0)
//                        winda.setKierunek(Kierunek::Idle);
//                    else if (tmp > 0)
//                        winda.setKierunek(Kierunek::Down);
//                    else if (tmp < 0)
//                        winda.setKierunek(Kierunek::Up);
//                }
//            }
//        }

//                for(int i = 0; i < pietra.size(); i++)
//                {
//                    if (!pietra[i]->kolejka.empty())
//                    {
//                        if (winda.nrPietra != i) moveWinda(i);
//                        while(!pietra[i]->kolejka.empty())
//                        {
//                            winda.pasazerowie.emplace_back(pietra[i]->kolejka[0]);
//                            pietra[i]->kolejka.erase(pietra[i]->kolejka.begin());
//                        }
//                    }
//                }

//                while(!winda.pasazerowie.empty())
//                {
//                    if (winda.nrPietra != winda.pasazerowie[0]->pietroDo) moveWinda(winda.pasazerowie[0]->pietroDo);
//                    winda.pasazerowie.erase(winda.pasazerowie.begin());
//                }
    }

    void drawScreen(sf::RenderWindow &window)
    {
        //rysujesz wszystko co ma byc na ekranie
        window.draw(backgroundSprite);
        window.draw(shaftSprite);
        window.draw(floorbackgroundSprite);

        window.draw(winda.body);
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            //            if (event.type == sf::Event::MouseButtonPressed)
            //                std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y<<std::endl;
            if (event.type == sf::Event::Closed)
                window.close();
            systemWindy.events(window, event);
//            if (event.type == sf::Event::MouseMoved)
//            {
//                systemWindy.winda.setPosition(sf::Mouse::getPosition(window).y);
//            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                for(int i = 0; i < systemWindy.pietra.size(); i++)
                {
                    //                    if (systemWindy.pietra[i]->button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    //                    {
                    //                        int nr = rand() % 5;
                    //                        cout << nr << endl;
                    //                        systemWindy.pietra[i]->add(nr);
                    //                        nr = rand() % 5;
                    //                        cout << nr << endl;
                    //                        systemWindy.pietra[i]->add(nr);
                    //                        //systemWindy.moveWinda(i);
                    //                    }
                    //cout << systemWindy.pietra[i]->kolejka.size() << endl;
                }
                //cout << endl;
            }
        }
        systemWindy.test();
        systemWindy.windaMovement();
        window.clear();
        systemWindy.drawScreen(window);
        window.display();
    }

    return 0;
}


int main1()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Elevator");
    sf::RectangleShape rect({50,50});
    window.setFramerateLimit(60);
    rect.setPosition(300,300);
    sf::Clock timer;
    int kierunek = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Up)
                kierunek = -1;
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down)
                kierunek = 1;
            else
                kierunek = 0;
        }
        if(timer.getElapsedTime().asMilliseconds() >= 1)
        {
            rect.move(0,kierunek);
            timer.restart();
        }
        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}
