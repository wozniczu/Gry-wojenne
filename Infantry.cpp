#include "Infantry.h"

Infantry::Infantry(float x, float y, bool team)
    : Unit(x, y, team, 
          100.0f,     // health
          15.0f,      // damage
          1.4f,       // speed
          25.0f,      // attackRange
          1.0f,       // attackSpeed
          0.85f,      // hitChance
          0.2f),      // defense - bazowa wartość obrony
    baseDefense(defense) // zapisujemy bazową wartość obrony
{
    std::string texturePath = team ? "textures/infantry_blue.png" : "textures/infantry_red.png";
    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie można załadować tekstury: " << texturePath << std::endl;
    }
    unitSprite.setTexture(unitTexture, true);
    unitSprite.setScale({0.7f, 0.7f});
}

float Infantry::calculateDefenseBonus(const std::vector<Unit*>& units) {
    int nearbyInfantry = 0;

    // Zliczamy pobliskie jednostki piechoty z tej samej drużyny
    for (const auto& unit : units) {
        if (!unit->isAlive() || unit == this || unit->getTeam() != team) continue;
        
        // Sprawdzamy czy jednostka jest typu Infantry
        if (dynamic_cast<Infantry*>(unit) != nullptr) {
            float distance = getDistance(unit->getPosition());
            if (distance <= FORMATION_RADIUS) {
                nearbyInfantry++;
            }
        }
    }

    // Obliczamy bonus do obrony (każda pobliska jednostka daje 5% bonusu, max 15%)
    float bonus = std::min(nearbyInfantry * 0.05f, MAX_DEFENSE_BONUS);
    
    // Zwracamy bazową obronę + bonus
    return bonus;
}

sf::Vector2f Infantry::calculateFormationMove(const std::vector<Unit*>& units, const sf::Vector2f& currentMove) {
    sf::Vector2f formationMove = currentMove;
    sf::Vector2f averagePos(0, 0);
    int nearbyAllies = 0;

    // Obliczamy średnią pozycję pobliskich sojuszniczych jednostek piechoty
    for (const auto& unit : units) {
        if (!unit->isAlive() || unit == this || unit->getTeam() != team) continue;
        
        if (dynamic_cast<Infantry*>(unit) != nullptr) {
            float distance = getDistance(unit->getPosition());
            if (distance <= FORMATION_RADIUS * 2) { // Większy promień dla formacji
                averagePos += unit->getPosition();
                nearbyAllies++;
            }
        }
    }

    if (nearbyAllies > 0) {
        averagePos /= static_cast<float>(nearbyAllies);
        
        // Jeśli jesteśmy zbyt daleko od formacji, próbujemy do niej dołączyć
        float distanceToFormation = std::sqrt(
            (averagePos.x - getPosition().x) * (averagePos.x - getPosition().x) +
            (averagePos.y - getPosition().y) * (averagePos.y - getPosition().y)
        );

        if (distanceToFormation > FORMATION_RADIUS) {
            sf::Vector2f toFormation = averagePos - getPosition();
            float length = std::sqrt(toFormation.x * toFormation.x + toFormation.y * toFormation.y);
            if (length > 0) {
                toFormation /= length;
                // Mieszamy ruch w kierunku wroga z ruchem w kierunku formacji
                formationMove = (formationMove + toFormation) * 0.5f * speed;
            }
        }
    }

    return formationMove;
}

void Infantry::update(const std::vector<Unit*>& units) {
    if (!isAlive()) return;

    updateAttackCooldown(1.0f / 60.0f);

    // Aktualizacja bonusu do obrony
    setDefense(baseDefense + calculateDefenseBonus(units));

    // Znajdź najbliższego wroga
    Unit* closestEnemy = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (auto& unit : units) {
        if (!unit->isAlive() || unit->getTeam() == team) continue;

        float distance = getDistance(unit->getPosition());
        if (distance < minDistance) {
            minDistance = distance;
            closestEnemy = unit;
        }
    }

    if (closestEnemy) {
        sf::Vector2f proposedMove(0, 0);

        // Jeśli wróg jest w zasięgu ataku
        if (minDistance <= attackRange) {
            if (canAttack()) {
                if (tryHit()) {
                    closestEnemy->takeDamage(damage);
                }
                resetAttackCooldown();
            }
        }
        // Jeśli wróg jest poza zasięgiem, podążaj za nim
        else {
            sf::Vector2f direction = closestEnemy->getPosition() - getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0) {
                direction /= length;
                proposedMove = direction * speed;
            }
        }

        // Modyfikuj ruch aby trzymać się formacji
        proposedMove = calculateFormationMove(units, proposedMove);

        // Zastosuj system kolizji do proponowanego ruchu
        sf::Vector2f actualMove = resolveCollision(units, proposedMove);
        setPosition(getPosition() + actualMove);
        
        // Ustaw kierunek sprite'a w zależności od kierunku ruchu
        float scale_sign = ((closestEnemy->getPosition().x - getPosition().x) > 0) ? 1.f : -1.f;
        if (unitSprite.getScale().x * scale_sign < 0)
        {
            unitSprite.setScale({ unitSprite.getScale().x * scale_sign, unitSprite.getScale().y });
        } 
    }
}
