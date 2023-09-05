#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;

bool sortGrowing(int a, int b);

bool sortShrinking(int a, int b);

class ButtonGroup
{
public:
    vector<sf::RectangleShape> buttons; //wizualny fizyczny zbior prostokatow buttonow
    vector<sf::Text*> text; //zbior textow - numery
    sf::Font font;

    ButtonGroup(); //konsturkot tworzacy przyciski i tekst - podstawowe wartosci
    ~ButtonGroup(); //destruktor dynamicznych elementów - napisów na przyciskach (na końcu progarmu)
    void setPosition(int x, int y); //funkcja ustwiająca pozycje przycisków i tesktów
    void draw(sf::RenderWindow &window); //funkcja rysująca przysciki i teksty
};
