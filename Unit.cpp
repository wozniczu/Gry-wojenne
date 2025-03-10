#include "Unit.h"
#include <random>

Unit::Unit(float x, float y, bool team, float health, float damage, float speed, float attackRange, float attackSpeed, float hitChance, float defense)
    : health(health), damage(damage), speed(speed), attackRange(attackRange), attackSpeed(attackSpeed),
    attackCooldown(0.f), hitChance(hitChance), defense(defense), alive(true), team(team), unitSprite(unitTexture) {

    // Wybór ikony w zależności od drużyny
    std::string texturePath = team ? "infantry_blue.png" : "infantry_red.png";

    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie można załadować tekstury: " << texturePath << std::endl;
    }

    unitSprite.setTexture(unitTexture);
    unitSprite.setPosition({ x, y });

    // Skalowanie do odpowiedniego rozmiaru (opcjonalnie)
    unitSprite.setScale({ 0.5f, 0.5f });

    velocity = sf::Vector2f(0.f, 0.f);
}

bool Unit::canAttack() const {
    return attackCooldown <= 0.f;
}

void Unit::resetAttackCooldown() {
    attackCooldown = 1.0f / attackSpeed;
}

void Unit::updateAttackCooldown(float deltaTime) {
    if (attackCooldown > 0) {
        attackCooldown -= deltaTime;
    }
}

void Unit::takeDamage(float dmg) {
    float reducedDamage = dmg * (1.0f - defense);
    health -= reducedDamage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

bool Unit::tryHit() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    
    return dis(gen) <= hitChance;
}

float Unit::getDistance(sf::Vector2f otherPos) const {
    sf::Vector2f diff = otherPos - unitSprite.getPosition();
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

sf::Vector2f Unit::getPosition() const {
    return unitSprite.getPosition();
}

void Unit::setPosition(const sf::Vector2f& pos) {
    unitSprite.setPosition(pos);
}

bool Unit::checkCollision(const Unit* other) const {
    if (other == this) return false;
    
    float distance = getDistance(other->getPosition());
    return distance < (COLLISION_RADIUS + other->getCollisionRadius());
}

sf::Vector2f Unit::resolveCollision(const std::vector<Unit*>& units, const sf::Vector2f& proposedMove) {
    sf::Vector2f finalPosition = getPosition() + proposedMove;
    
    // Sprawdź kolizje z innymi jednostkami
    for (const Unit* other : units) {
        if (other == this || !other->isAlive()) continue;

        // Oblicz odległość między proponowaną pozycją a inną jednostką
        sf::Vector2f otherPos = other->getPosition();
        sf::Vector2f diff = finalPosition - otherPos;
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        
        // Jeśli jest kolizja
        float minDistance = COLLISION_RADIUS + other->getCollisionRadius();
        if (distance < minDistance) {
            // Oblicz wektor odpychania
            if (distance > 0) {
                diff = diff / distance; // Normalizacja
                finalPosition = otherPos + diff * minDistance;
            } else {
                // Jeśli jednostki są dokładnie w tym samym miejscu, przesuń w losowym kierunku
                float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f;
                finalPosition = otherPos + sf::Vector2f(cos(angle), sin(angle)) * minDistance;
            }
        }
    }
    
    // Zwróć wektor przesunięcia
    return finalPosition - getPosition();
}