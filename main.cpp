#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
using namespace std;

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
        body.setScale(0.1,0.1);
    }
    Osoba(float doPietra, int wag) : pietroDo((int)doPietra), waga(wag)
    {
        texture.loadFromFile("./stick.png");
        body.setTexture(texture);
        body.setScale(0.1,0.1);
    }
};

class Pietro
{
public:
    sf::Texture texture;
    sf::Sprite body;
    vector<Osoba*> kolejka;
    Pietro()
    {
        texture.loadFromFile("./pietro.jpg");
        body.setTexture(texture);
        body.setScale(0.25f, 0.25f);
        body.setPosition(188, 100);
//        body.setSize(sf::Vector2f(500, 8));
//        body.setFillColor(sf::Color::Black);
//        body.setPosition(725, 100);
    }

    ~Pietro()
    {
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            delete kolejka[i];
        }
    }
    void add()
    {
        kolejka.emplace_back(new Osoba(1));
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            kolejka[i]->body.setPosition(i*200, 0);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(body);
        for(int i = 0; i < (int)kolejka.size(); i++)
        {
            window.draw(kolejka[i]->body);
        }
    }
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

    Winda(int maxWag) : maxWaga(maxWag) {}
    Winda()
    {
        texture.loadFromFile("./el.png");
        body.setTexture(texture);
        body.setScale(0.625f, 0.5f);
        body.setPosition(0, 0);

    }
};

class SystemWindy
{
public:
    vector<Pietro> pietra;
    Winda winda;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture shaftTexture;
    sf::Sprite shaftSprite;

    SystemWindy(int iloscPieter, sf::RenderWindow &window) : pietra(vector<Pietro>(iloscPieter))
    {

        backgroundTexture.loadFromFile("./background.png");

        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(window.getSize().x/backgroundSprite.getGlobalBounds().width, window.getSize().y/backgroundSprite.getGlobalBounds().height);

        shaftTexture.loadFromFile("./shaft2.png");

        shaftSprite.setTexture(shaftTexture);
        shaftSprite.setScale(0.5f, 1.5f);
        shaftSprite.setPosition(0, 0);
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

    void drawScreen(sf::RenderWindow &window)
    {
        //rysujesz wszystko co ma byc na ekranie
        window.draw(backgroundSprite);
        window.draw(shaftSprite);
        window.draw(winda.body);
        for(int i = 0; i < pietra.size(); i++)
        {
            pietra[i].draw(window);
        }
    }

};

//class MainScreen
//{
//public:
//    //wszystkie elementy / zmienne wazne do ekranu


//    MainScreen(sf::RenderWindow &window)
//    {
//        //wartosci poczatkowe, ustawianie pozycji itp itd

//    }


//    void drawScreen(sf::RenderWindow &window)
//    {
//        //rysujesz wszystko co ma byc na ekranie

//    }
//};



int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Elevator");
    Pietro pietro1;
    SystemWindy systemWindy(5,window);
//    sf::Texture background;
//    background.loadFromFile("./background.png");

//    sf::Sprite backgroundSprite(background);
//    backgroundSprite.setScale(window.getSize().x/backgroundSprite.getGlobalBounds().width, window.getSize().y/backgroundSprite.getGlobalBounds().height);

//    sf::Texture shaft;
//    shaft.loadFromFile("./shaft2.png");


//    sf::Sprite shaftSprite(shaft);

//    shaftSprite.setScale(0.5f, 1.5f);
//    shaftSprite.setPosition(0, 0);

//    sf::Texture elevator;
//    elevator.loadFromFile("./el.png");

//    sf::Sprite elevatorSprite(elevator);

//    elevatorSprite.setScale(0.625f, 0.5f);
//    elevatorSprite.setPosition(0, 0);

//    sf::Texture pietro;
//    pietro.loadFromFile("./pietro.jpg");

//    sf::Sprite pietroSprite(pietro);

//    pietroSprite.setScale(0.25f, 0.25f);
//    pietroSprite.setPosition(188, 100);

//    sf::Texture czlowiek;
//    czlowiek.loadFromFile("./stick.png");

//    sf::Sprite czlowiekSprite(czlowiek);

//    czlowiekSprite.setScale(0.25f, 0.25f);
//    czlowiekSprite.setPosition(575, 159);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                               std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y<<std::endl;
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                pietro1.add();
            }
        }

        window.clear();
        //pietro1.draw(window);
//window.draw(backgroundSprite);
//        window.draw(shaftSprite);
//       window.draw(elevatorSprite);
//        window.draw(pietroSprite);
//        window.draw(czlowiekSprite);
        systemWindy.drawScreen(window);
        window.display();
    }

    return 0;
}



