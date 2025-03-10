#pragma once
#include "Unit.h"
#include <iostream>
#include <list>

// Struktura pomocnicza reprezentująca strzałę
struct Arrow {
    // Właściwości strzały
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    bool active;
    sf::RectangleShape shape;

    // Konstruktor
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

class Archer : public Unit {
private:
    // Zmienne członkowskie
    std::list<Arrow> arrows;
    float arrowSpeed;

public:
    // Konstruktor
    Archer(float x, float y, bool team);
    
    // Nadpisana metoda z klasy bazowej
    void update(const std::vector<Unit*>& units) override;
    
    // Metody specyficzne dla łucznika
    void drawArrows(sf::RenderWindow& window);
    void shoot(const sf::Vector2f& targetPos);
};
