#include "Unit.h"
#include <cmath>

Unit::Unit(float x, float y, bool team, float health, float damage, float speed, float attackRange)
    : health(health), damage(damage), speed(speed), attackRange(attackRange), attackSpeed(attackSpeed), alive(true), team(team) {
    shape.setRadius(5.f);
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(team ? sf::Color::Blue : sf::Color::Red);
}

void Unit::update(const std::vector<Unit*>& enemies) {
    if (!alive) return;

    float minDist = 1000000.f;
    sf::Vector2f targetPos;
    Unit* closestEnemy = nullptr;

    // Znalezienie najbli¿szego przeciwnika w zasiêgu
    for (auto& enemy : enemies) {
        if (!enemy->isAlive() || enemy->getTeam() == team) continue;

        float dist = getDistance(enemy->getPosition());
        if (dist < minDist) {
            minDist = dist;
            closestEnemy = enemy;
            targetPos = enemy->getPosition();
        }
    }

    // Poruszanie siê w kierunku przeciwnika
    if (closestEnemy) {
        sf::Vector2f direction = targetPos - shape.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0 && length > getRange()) {
            direction /= length;
            velocity = direction * speed;
            shape.move(velocity);
        }

        // Atak, jeœli w zasiêgu
        if (length <= getRange()) {
            closestEnemy->takeDamage(damage);
        }
    }
}

void Unit::takeDamage(float dmg) {
    health -= dmg;
    if (health <= 0) {
        alive = false;
    }
}

float Unit::getDistance(sf::Vector2f otherPos) const {
    sf::Vector2f diff = otherPos - shape.getPosition();
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

sf::Vector2f Unit::getPosition() const {
    return shape.getPosition();
}

bool Unit::isAlive() const {
    return alive;
}

const sf::CircleShape& Unit::getShape() const {
    return shape;
}