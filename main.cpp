#include "systemwindy.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Elevator");
    SystemWindy systemWindy;
    srand(time(NULL));
    cout<< "SYMULATOR WINDY" << endl;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            systemWindy.events(window, event);
        }
        systemWindy.timerLogic();
        //cout << 11 << endl;
        systemWindy.windaMovement();
        //cout << 12 << endl;
        window.clear();
        systemWindy.drawScreen(window);
        window.display(); //wyświetlanie na ekranie - rzeczy narysowane w draw'ach

    }

    return 0;
}
