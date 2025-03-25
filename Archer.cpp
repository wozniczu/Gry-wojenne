#include "Archer.h"

Archer::Archer(float x, float y, bool team)
    : Unit(x, y, team, 
          80.0f,      // health
          10.0f,      // damage
          0.7f,       // speed
          300.0f,     // attackRange
          0.4f,       // attackSpeed
          0.95f,      // hitChance
          0.1f),      // defense
    arrowSpeed(20.f) {
    std::string texturePath = team ? "textures/archer_blue.png" : "textures/archer_red.png";

    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie można załadować tekstury łucznika!" << std::endl;
    }
    unitSprite.setTexture(unitTexture, true);
    unitSprite.setScale({ 1.f, 1.f });
}

void Archer::update(const std::vector<Unit*>& units) {
    if (!isAlive()) return;

    // Aktualizacja cooldownu ataku
    updateAttackCooldown(0.016f);

    float minDist = 1000000.f;
    sf::Vector2f targetPos;
    Unit* closestEnemy = nullptr;

    // Znalezienie najbliższego przeciwnika
    for (auto& unit : units) {
        if (!unit->isAlive() || unit->getTeam() == team) continue;

        float dist = getDistance(unit->getPosition());
        if (dist < minDist) {
            minDist = dist;
            closestEnemy = unit;
            targetPos = unit->getPosition();
        }
    }

    // Poruszanie się i strzelanie
    if (closestEnemy) {
        sf::Vector2f proposedMove(0, 0);
        sf::Vector2f direction = targetPos - getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0) {
            direction /= length;
            
            // Jeśli wróg jest za blisko, oddal się
            if (length < getRange() * 0.5f) {
                proposedMove = -direction * speed;
            }
            // Jeśli wróg jest za daleko, zbliż się
            else if (length > getRange() * 0.8f) {
                proposedMove = direction * speed;
            }

            // Strzelanie
            if (length <= getRange() && canAttack()) {
                if (tryHit()) {
                    shoot(targetPos);
                }
                resetAttackCooldown();
            }
        }

        // Zastosuj system kolizji do proponowanego ruchu, uwzględniając wszystkie jednostki
        sf::Vector2f actualMove = resolveCollision(units, proposedMove);
        setPosition(getPosition() + actualMove);
    }

    // Aktualizacja strzał
    for (auto it = arrows.begin(); it != arrows.end();) {
        if (!it->active) {
            it = arrows.erase(it);
            continue;
        }

        // Aktualizacja pozycji strzały
        it->position += it->velocity * it->speed;
        it->shape.setPosition(it->position);

        // Sprawdzenie kolizji ze wszystkimi wrogami
        for (auto& unit : units) {
            if (!unit->isAlive() || unit->getTeam() == team) continue;

            sf::Vector2f enemyPos = unit->getPosition();
            sf::Vector2f arrowPos = it->position;

            // Prosta detekcja kolizji - jeśli strzała jest wystarczająco blisko wroga
            float dist = std::sqrt(
                (enemyPos.x - arrowPos.x) * (enemyPos.x - arrowPos.x) +
                (enemyPos.y - arrowPos.y) * (enemyPos.y - arrowPos.y)
            );

            if (dist < 20.f) { // Promień kolizji
                unit->takeDamage(damage);
                it->active = false;
                break;
            }
        }

        if (it->active) {
            ++it;
        }
        else {
            it = arrows.erase(it);
        }
    }
}

void Archer::shoot(const sf::Vector2f& targetPos) {
    sf::Vector2f direction = targetPos - getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0) {
        direction /= length;
        arrows.emplace_back(getPosition(), direction, arrowSpeed);
    }
}

void Archer::drawArrows(sf::RenderWindow& window) {
    for (const auto& arrow : arrows) {
        if (arrow.active) {
            window.draw(arrow.shape);
        }
    }
}