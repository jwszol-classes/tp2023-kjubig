#include "UI.hpp"

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

ButtonGroup::ButtonGroup() //konsturkot tworzacy przyciski i tekst - podstawowe wartosci
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

ButtonGroup::~ButtonGroup() //destruktor dynamicznych elementów - napisów na przyciskach (na końcu progarmu)
{
    for(int i=0; i<5;i++)
    {
        delete text[i];
    }
}

void ButtonGroup::setPosition(int x, int y) //funkcja ustwiająca pozycje przycisków i tesktów
{
    for(int i=4; i>=0;i--)
    {
        buttons[i].setPosition(x,y+ (4-i)*30);
        text[i]->setPosition(x+7,y+ (4-i)*30+2);
    }
}

void ButtonGroup::draw(sf::RenderWindow &window) //funkcja rysująca przysciki i teksty
{
    for(int i=0; i<5;i++)
    {
        window.draw(buttons[i]);
        window.draw(*text[i]);
    }
}
