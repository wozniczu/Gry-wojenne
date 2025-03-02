#include "Archer.h"
#include <iostream>
Archer::Archer(float x, float y, bool team)
    : Unit(x, y, team, 80.f, 10.f, 0.7f, 300.f) {
    shape = sf::CircleShape(10.f, 3);
    shape.setPosition({ x, y });
    shape.setFillColor(team ? sf::Color::Blue : sf::Color::Red);
}