#include "Archer.h"

Archer::Archer(float x, float y, bool team)
    : Unit(x, y, team, 80.f, 10.f, 0.7f, 200.f) {
    shape = sf::CircleShape(10.f, 3);
    shape.setPosition({ x, y });
    shape.setFillColor(team ? sf::Color::Blue : sf::Color::Red);
}

void Archer::update(const std::vector<Unit*>& enemies) {
    if (!alive) return;

    for (const auto& enemy : enemies) {
        if (enemy->getTeam() != team && getDistance(enemy->getPosition()) < 50.f) {
            enemy->takeDamage(damage);
            return;
        }
    }
    Unit::update(enemies);
}