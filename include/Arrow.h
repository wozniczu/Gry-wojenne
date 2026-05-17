#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Klasa reprezentująca strzałę wystrzeloną przez łucznika
 * 
 * Klasa odpowiedzialna za reprezentację strzały w grze.
 * Przechowuje informacje o pozycji, prędkości i stanie aktywności
 * strzały, odpowiada za jej ruch i interakcję z celami.
 */
class Arrow {
public:
    sf::Vector2f position;          ///< Aktualna pozycja strzały
    sf::Vector2f velocity;          ///< Wektor prędkości strzały
    float speed;                    ///< Prędkość strzały
    bool active;                    ///< Flaga określająca czy strzała jest aktywna
    sf::RectangleShape shape;       ///< Kształt wizualny strzały

    /**
     * @brief Konstruktor strzały
     * @param pos Pozycja początkowa strzały
     * @param vel Wektor prędkości strzały
     * @param spd Prędkość strzały
     */
    Arrow(sf::Vector2f pos, sf::Vector2f vel, float spd)
        : position(pos), velocity(vel), speed(spd), active(true) 
    {
        // Konfiguracja kształtu strzały
        shape.setSize(sf::Vector2f(10.f, 2.f));
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(position);

        // Obliczanie rotacji strzały
        float angle = std::atan2(velocity.y, velocity.x) * 180 / 3.14159f;
        shape.setRotation(sf::degrees(angle));
    }
}; 