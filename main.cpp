#include <SFML/Graphics.hpp>
#include "Battle.h"
#include "SliderSFML.h"
#include "ButtonSFML.h"
#include <iostream>
#include <sstream>
#include <thread>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1400, 800 }), "Symulacja Wojny");
    window.setFramerateLimit(60);

    // Stany aplikacji
    enum AppState { SETUP, BATTLE };
    AppState currentState = SETUP;

    // £adowanie czcionki
    sf::Font font;
    if (!font.openFromFile("Arial.ttf")) {
        std::cerr << "Nie mo¿na za³adowaæ czcionki!" << std::endl;
        return -1;
    }

    // Tytu³y dla dru¿yn
    sf::Text teamATitle(font, "");
    teamATitle.setFont(font);
    teamATitle.setString("Niebiescy");
    teamATitle.setCharacterSize(30);
    teamATitle.setPosition({ 150, 50 });
    teamATitle.setFillColor(sf::Color::Blue);

    sf::Text teamBTitle(font, "");
    teamBTitle.setFont(font);
    teamBTitle.setString("Czerwoni");
    teamBTitle.setCharacterSize(30);
    teamBTitle.setPosition({ 900, 50 });
    teamBTitle.setFillColor(sf::Color::Red);

    // Etykiety dla jednostek
    sf::Text labelInfantryA(font, "");
    labelInfantryA.setFont(font);
    labelInfantryA.setString("Piechota:");
    labelInfantryA.setCharacterSize(24);
    labelInfantryA.setPosition({ 100, 150 });
    labelInfantryA.setFillColor(sf::Color::Black);

    sf::Text labelArcherA(font, "");
    labelArcherA.setFont(font);
    labelArcherA.setString(L"£ucznicy:");
    labelArcherA.setCharacterSize(24);
    labelArcherA.setPosition({ 100, 250 });
    labelArcherA.setFillColor(sf::Color::Black);

    sf::Text labelCavalryA(font, "");
    labelCavalryA.setFont(font);
    labelCavalryA.setString("Kawaleria:");
    labelCavalryA.setCharacterSize(24);
    labelCavalryA.setPosition({ 100, 350 });
    labelCavalryA.setFillColor(sf::Color::Black);

    sf::Text labelInfantryB(font, "");
    labelInfantryB.setFont(font);
    labelInfantryB.setString("Piechota:");
    labelInfantryB.setCharacterSize(24);
    labelInfantryB.setPosition({ 850, 150 });
    labelInfantryB.setFillColor(sf::Color::Black);

    sf::Text labelArcherB(font, "");
    labelArcherB.setFont(font);
    labelArcherB.setString(L"£ucznicy:");
    labelArcherB.setCharacterSize(24);
    labelArcherB.setPosition({ 850, 250 });
    labelArcherB.setFillColor(sf::Color::Black);

    sf::Text labelCavalryB(font, "");
    labelCavalryB.setFont(font);
    labelCavalryB.setString("Kawaleria:");
    labelCavalryB.setCharacterSize(24);
    labelCavalryB.setPosition({ 850, 350 });
    labelCavalryB.setFillColor(sf::Color::Black);

    // Tworzenie suwaków dla dru¿yny A
    SliderSFML infantrySliderA(250, 170);
    infantrySliderA.create(0, 50);
    infantrySliderA.setSliderValue(10);

    SliderSFML archerSliderA(250, 270);
    archerSliderA.create(0, 50);
    archerSliderA.setSliderValue(10);

    SliderSFML cavalrySliderA(250, 370);
    cavalrySliderA.create(0, 50);
    cavalrySliderA.setSliderValue(10);

    // Tworzenie suwaków dla dru¿yny B
    SliderSFML infantrySliderB(1000, 170);
    infantrySliderB.create(0, 50);
    infantrySliderB.setSliderValue(10);

    SliderSFML archerSliderB(1000, 270);
    archerSliderB.create(0, 50);
    archerSliderB.setSliderValue(10);

    SliderSFML cavalrySliderB(1000, 370);
    cavalrySliderB.create(0, 50);
    cavalrySliderB.setSliderValue(10);

    // Przycisk Start
    ButtonSFML startButton(600, 600, 200, 80, "START", font);

    // Przygotowanie symulatora bitwy
    Battle* battle = nullptr;

    // G³ówna pêtla
    bool mouseReleased = true;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Sprawdzenie, czy przycisk myszy zosta³ zwolniony
            if (event->is<sf::Event::MouseButtonReleased>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    mouseReleased = true;
                }
            }
        }

        window.clear(sf::Color(240, 240, 240));

        if (currentState == SETUP) {
            // Rysowanie tytu³ów
            window.draw(teamATitle);
            window.draw(teamBTitle);

            // Rysowanie etykiet
            window.draw(labelInfantryA);
            window.draw(labelArcherA);
            window.draw(labelCavalryA);
            window.draw(labelInfantryB);
            window.draw(labelArcherB);
            window.draw(labelCavalryB);

            // Rysowanie suwaków
            infantrySliderA.draw(window);
            archerSliderA.draw(window);
            cavalrySliderA.draw(window);
            infantrySliderB.draw(window);
            archerSliderB.draw(window);
            cavalrySliderB.draw(window);

            // Aktualizacja i rysowanie przycisku Start
            startButton.update(window);
            startButton.draw(window);

            // Obs³uga klikniêcia przycisku Start
            if (startButton.isClicked(window) && mouseReleased) {
                mouseReleased = false;

                // Tworzenie bitwy z wybranymi jednostkami
                if (battle != nullptr) {
                    delete battle;
                }

                battle = new Battle(
                    static_cast<int>(infantrySliderA.getSliderValue()),
                    static_cast<int>(archerSliderA.getSliderValue()),
                    static_cast<int>(cavalrySliderA.getSliderValue()),
                    static_cast<int>(infantrySliderB.getSliderValue()),
                    static_cast<int>(archerSliderB.getSliderValue()),
                    static_cast<int>(cavalrySliderB.getSliderValue())
                );

                currentState = BATTLE;
            }
        }
        else if (currentState == BATTLE) {
            // Aktualizacja i rysowanie bitwy
            if (battle && !battle->isFinished()) {
                battle->update();
                battle->draw(window);
                battle->displayUnitsHealth();
            }

            else if (battle && battle->isFinished()) {
                // Gdy bitwa siê zakoñczy³a, automatycznie wróæ do ekranu wyboru
                battle->draw(window);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                currentState = SETUP;
                if (battle) {
                    delete battle;
                    battle = nullptr;
                }
                mouseReleased = true;
            }
        }

        window.display();
    }

    // Zwolnienie pamiêci
    if (battle) {
        delete battle;
    }

    return 0;
}