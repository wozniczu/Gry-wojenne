#include "Archer.h"

/**
 * @brief Konstruktor klasy Archer
 * 
 * Inicjalizuje łucznika z podanymi parametrami i ładuje odpowiednią teksturę.
 * 
 * @param x Pozycja początkowa X łucznika
 * @param y Pozycja początkowa Y łucznika 
 * @param team Przynależność do drużyny (true - niebieska, false - czerwona)
 */
Archer::Archer(float x, float y, bool team)
    : Unit(x, y, team, 
          50.0f,      // health
          10.0f,      // damage
          0.7f,       // speed
          300.0f,     // attackRange
          1.0f,       // attackSpeed
          0.95f,      // hitChance
          0.1f),      // defense
    arrowSpeed(20.f) {
    std::string texturePath = team ? "textures/archer_blue.png" : "textures/archer_red.png";

    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie można załadować tekstury łucznika!" << std::endl;
    }
    unitSprite.setTexture(unitTexture, true);
    unitSprite.setScale({ 0.05f, 0.05f });
}

/**
 * @brief Aktualizuje stan łucznika w każdej klatce gry
 * 
 * Metoda odpowiedzialna za:
 * - Znajdowanie najbliższego przeciwnika
 * - Podejmowanie decyzji o ruchu (zbliżanie/oddalanie)
 * - Strzelanie do przeciwników w zasięgu
 * - Obsługę obracania sprite'a w kierunku przeciwnika
 * - Aktualizację pozycji strzał
 * 
 * @param units Vector zawierający wszystkie jednostki na mapie
 */
void Archer::update(const std::vector<Unit*>& units) {
    if (!isAlive()) return;

    // Aktualizacja cooldownu ataku
    updateAttackCooldown(1.0f / 60.0f);

    sf::Vector2f targetPos;
    float minDistance = std::numeric_limits<float>::max();
    Unit* closestEnemy = nullptr;

    // Znalezienie najbliższego przeciwnika
    for (auto& unit : units) {
        if (!unit->isAlive() || unit->getTeam() == team) continue;

        float dist = getDistance(unit->getPosition());
        if (dist < minDistance) {
            minDistance = dist;
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
        velocity = actualMove;
        setPosition(getPosition() + actualMove);
        
        // Ustaw kierunek sprite'a w zależności od kierunku ataku
        float scale_sign = ((closestEnemy->getPosition().x - getPosition().x) >= 0) ? 1.f : -1.f;
        if (unitSprite.getScale().x * scale_sign < 0)
        {
            unitSprite.setScale({ -unitSprite.getScale().x, unitSprite.getScale().y});
        }
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

/**
 * @brief Wystrzeliwuje strzałę w kierunku celu
 * 
 * Tworzy nową strzałę z obliczonym wektorem kierunku i dodaje ją do listy aktywnych strzał.
 * Strzała będzie poruszać się w kierunku celu z zadaną prędkością (arrowSpeed).
 * 
 * @param targetPos Docelowa pozycja strzały (pozycja przeciwnika)
 */
void Archer::shoot(const sf::Vector2f& targetPos) {
    sf::Vector2f direction = targetPos - getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0) {
        direction /= length;
        arrows.emplace_back(getPosition(), direction, arrowSpeed);
    }
}

/**
 * @brief Rysuje wszystkie aktywne strzały w oknie gry
 * 
 * Iteruje przez listę strzał i rysuje tylko te, które są aktywne.
 * Strzały są usuwane z listy po trafieniu w cel lub wyjściu poza mapę.
 * 
 * @param window Referencja do okna renderowania SFML
 */
void Archer::drawArrows(sf::RenderWindow& window) {
    for (const auto& arrow : arrows) {
        if (arrow.active) {
            window.draw(arrow.shape);
        }
    }
}
