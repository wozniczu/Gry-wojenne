#include <SFML/Graphics.hpp>
#include "Battle.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1400, 800)), "Symulacja Wojny");
    window.setFramerateLimit(60);

    Battle battle;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (!battle.isFinished()) {
            battle.update();
            battle.displayUnitsHealth();
        }

        window.clear(sf::Color::White);
        battle.draw(window);
        window.display();
    }

    return 0;
}
