#include "Cavalry.h"

Cavalry::Cavalry(float x, float y, bool team)
    : Unit(x, y, team, 100.f, 25.f, 2.0f, 1.2f) {
    shape = sf::CircleShape(10.f, 4);
    shape.setPosition({ x, y });
    shape.setFillColor(team ? sf::Color::Blue : sf::Color::Red);
}