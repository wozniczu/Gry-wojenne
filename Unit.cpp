#include "Unit.h"

Unit::Unit(float x, float y, bool team, float health, float damage, float speed, float attackRange)
    : health(health), damage(damage), speed(speed), attackRange(attackRange), alive(true), team(team), unitSprite(unitTexture) {

    // Wybór ikony w zale¿noœci od dru¿yny
    std::string texturePath = team ? "infantry_blue.png" : "infantry_red.png";

    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury: " << texturePath << std::endl;
    }

    unitSprite.setTexture(unitTexture);
    unitSprite.setPosition({ x, y });

    // Skalowanie do odpowiedniego rozmiaru (opcjonalnie)
    unitSprite.setScale({ 0.5f, 0.5f });
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
        sf::Vector2f direction = targetPos - unitSprite.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0 && length > getRange()) {
            direction /= length;
            velocity = direction * speed;
            unitSprite.move(velocity);
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
    sf::Vector2f diff = otherPos - unitSprite.getPosition();
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

sf::Vector2f Unit::getPosition() const {
    return unitSprite.getPosition();
}

bool Unit::isAlive() const {
    return alive;
}

const sf::Sprite& Unit::getShape() const {
    return unitSprite;
}