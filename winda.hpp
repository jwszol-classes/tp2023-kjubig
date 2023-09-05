#pragma once
#include "UI.hpp"

class Osoba //jednostki(osoby) na piętrach
{
public:
    float pietroDo; //oznaczenie numery piętra, do którego jedzie dana osboa - wykorzsytanie floata przez pólpiętra
    int waga = 70;
    sf::Texture texture;
    sf::Sprite body;
    sf::Text OznaczenieOsoby;
    sf::Font font;

    Osoba(float doPietra); //konstruktor jedno elementowy, który tworzy osobę z daną pietra
    void setPosition(int x, int y); //funkcja ustwiająca pozycje osoby i oznacznia
    void move(int x, int y); //przesunięcie o dane wartosci równolegle osoby i oznaczenia
    void draw(sf::RenderWindow &window); //rsyowanie
};

class Pietro // jednostka pietra
{
public:
    sf::Texture texture;
    sf::Sprite body;
    vector<Osoba*> kolejka; //zbiór osób oczekujących na winde na pietree
    vector<Osoba*> wychodzacy; // zbiór osób wyschdozacych z windy
    ButtonGroup buttons; // intrakcja uzytkowanika na przyciskach

    Pietro();
    ~Pietro();
    sf::Vector2f getPosition(); //pobieramy pozycje pieter
    void add(int nr); //dodawanie osob do pietra
    void ustawieniaLudziPietro(); //ustawianie/update pozycji osób na pietrze --- działa na wszytko przez zbiór osób
    void draw(sf::RenderWindow &window); //rysowanie
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

    Winda(int maxWag);
    Winda();
    void setKierunek(Kierunek kier);
    void setPosition(int yPos);
    void ustawieniaPasazerow();
};


