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
    sf::Texture floorbackgroundTexture;
    sf::Sprite floorbackgroundSprite;

    SystemWindy(int iloscPieter, sf::RenderWindow &window) : pietra(vector<Pietro>(iloscPieter))
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
        floorbackgroundSprite.setScale(1.0f, 1.0f);
        floorbackgroundSprite.setPosition(187, 0);
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

        window.draw(shaftSprite);
        window.draw(floorbackgroundSprite);
        window.draw(backgroundSprite);
        window.draw(winda.body);
        for(int i = 0; i < pietra.size(); i++)
        {
            pietra[i].draw(window);
        }
    }

};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Elevator");
    Pietro pietro1;
    SystemWindy systemWindy(5,window);

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
        systemWindy.drawScreen(window);
        window.display();
    }

    return 0;
}



