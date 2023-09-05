#pragma once
#include "winda.hpp"

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
    bool sortingType = true;

    SystemWindy();
    void dodajDoKolejkiPieter(int pietro);
    void events(sf::RenderWindow &window, sf::Event &event);
    void moveWinda(bool czekac);
    void checkPietro();
    void debugCheckVectors();
    void timerLogic();
    void logikaWindy();
    void windaMovement();
    void drawScreen(sf::RenderWindow &window);

};
