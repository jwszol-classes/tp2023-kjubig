#pragma once
#include "winda.hpp"

class SystemWindy
{
public:
    vector<Pietro*> pietra; //zbiór pojednyncych pieter
    Winda winda; // oczek. durgocze.
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture shaftTexture;
    sf::Sprite shaftSprite;
    sf::Texture boxTexture;
    sf::Sprite boxSprite;
    sf::Texture floorbackgroundTexture;
    sf::Sprite floorbackgroundSprite;
    bool stop = false; //artefakt
    sf::Clock stopTimer; //objekt konrolujący czas zatrzymania windy
    sf::Clock endClock; //artefakt
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
