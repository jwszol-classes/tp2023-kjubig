#include "winda.hpp"


Osoba::Osoba(float doPietra) : pietroDo((int)doPietra) //konstruktor jedno elementowy, który tworzy osobę z daną pietra
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


void Osoba::setPosition(int x, int y) //funkcja ustwiająca pozycje osoby i oznacznia
{
    body.setPosition(x,y);
    OznaczenieOsoby.setPosition(x+42,y+40);
}
void Osoba::move(int x, int y) //przesunięcie o dane wartosci równolegle osoby i oznaczenia
{
    body.move(x,y);
    OznaczenieOsoby.move(x,y);
}

void Osoba::draw(sf::RenderWindow &window) //rsyowanie
{
    window.draw(body);
    window.draw(OznaczenieOsoby);
}


Pietro::Pietro()
{
    texture.loadFromFile("./pietro.jpg");
    body.setTexture(texture);
    body.setScale(0.29f, 0.25f);
}

Pietro::~Pietro()
{
    for(int i = 0; i < (int)kolejka.size(); i++)
    {
        delete kolejka[i];
    }
}


sf::Vector2f Pietro::getPosition() //pobieramy pozycje pieter
{
    return body.getPosition();
}
void Pietro::add(int nr) //dodawanie osob do pietra
{
    kolejka.emplace_back(new Osoba(nr)); //dodwanie osob do kolejki
    ustawieniaLudziPietro();
}
void Pietro::ustawieniaLudziPietro() //ustawianie/update pozycji osób na pietrze --- działa na wszytko przez zbiór osób
{
    for(int i = 0; i < (int)kolejka.size(); i++)
    {
        kolejka[i]->setPosition(225 + i*50, body.getPosition().y + 60);
    }
}
void Pietro::draw(sf::RenderWindow &window) //rysowanie
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




Winda::Winda(int maxWag) : maxWaga(maxWag) {}
Winda::Winda()
{
    texture.loadFromFile("./el.png");
    body.setTexture(texture);
    body.setScale(0.625f, 0.385f);
    body.setPosition(0, 724);
    //724 548 373 200 23



}
void Winda::setKierunek(Kierunek kier)
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
void Winda::setPosition(int yPos)
{
    body.setPosition(body.getPosition().x, yPos);
    //ludzie w windzie
}
void Winda::ustawieniaPasazerow()
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
