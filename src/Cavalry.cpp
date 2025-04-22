#include "Cavalry.h"

/**
 * @brief Konstruktor klasy Cavalry
 * 
 * Inicjalizuje kawalerzystę z podanymi parametrami i ładuje odpowiednią teksturę.
 * Kawaleria ma największą prędkość i specjalne zdolności (szarża, okrążanie).
 * 
 * @param x Pozycja początkowa X jednostki
 * @param y Pozycja początkowa Y jednostki 
 * @param team Przynależność do drużyny (true - niebieska, false - czerwona)
 */
Cavalry::Cavalry(float x, float y, bool team)
    : Unit(x, y, team,
        120.0f,     // health
        30.0f,      // damage
        2.0f,       // speed
        35.0f,      // attackRange
        0.7f,       // attackSpeed
        0.95f,      // hitChance
        0.1f),     // defense
    isCharging(false),
    chargeSpeed(3.0f),
    chargeCooldown(0.0f),
    maxChargeCooldown(3.0f),     // 3 sekundy cooldownu na szarżę
    circlingRadius(150.0f),      // promień okrążania
    circlingAngle(0.0f) {        // Początkowy kąt okrążania
    std::string texturePath = team ? "textures/cavalry_blue.png" : "textures/cavalry_red.png";
    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie można załadować tekstury: " << texturePath << std::endl;
    }
    unitSprite.setTexture(unitTexture, true);
    unitSprite.setScale({ 0.07f, 0.07f });
}

/**
 * @brief Rozpoczyna szarżę w kierunku celu
 * 
 * Ustawia flagę isCharging na true i oblicza punkt docelowy szarży,
 * uwzględniając granice pola bitwy. Szarża może być wykonana tylko
 * gdy chargeCooldown <= 0.
 * 
 * @param target Pozycja celu szarży
 */
void Cavalry::startCharge(const sf::Vector2f& target) {
    if (chargeCooldown <= 0 && !isCharging) {
        isCharging = true;
        chargeTarget = target;
        // Wydłuż dystans szarży w kierunku celu
        sf::Vector2f direction = target - getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction /= length;
            chargeTarget = target + direction * 300.0f;

            // Sprawdź czy punkt docelowy szarży nie wychodzi poza granice pola
            sf::FloatRect bounds = unitSprite.getGlobalBounds();
            if (chargeTarget.x < 0) chargeTarget.x = 0;
            if (chargeTarget.x > 1400 - bounds.size.x) chargeTarget.x = 1400 - bounds.size.x;
            if (chargeTarget.y < 0) chargeTarget.y = 0;
            if (chargeTarget.y > 800 - bounds.size.y) chargeTarget.y = 800 - bounds.size.y;
        }
    }
}

/**
 * @brief Aktualizuje stan szarży
 * 
 * Metoda odpowiedzialna za:
 * - Zmniejszanie czasu cooldownu szarży
 * - Poruszanie jednostką podczas szarży
 * - Kończenie szarży po dotarciu do celu
 */
void Cavalry::updateCharge() {
    if (chargeCooldown > 0) {
        chargeCooldown -= 1.0f / 60.0f;
    }

    if (isCharging) {
        sf::Vector2f direction = chargeTarget - getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 5.0f) {
            direction /= length;
            velocity = direction * chargeSpeed;
        }
        else {
            isCharging = false;
            chargeCooldown = maxChargeCooldown;
        }
    }
}

/**
 * @brief Aktualizuje stan kawalerzysty w każdej klatce gry
 * 
 * Metoda odpowiedzialna za:
 * - Aktualizację stanu szarży
 * - Znajdowanie i atakowanie najbliższego wroga
 * - Okrążanie przeciwników
 * - Rozpoczynanie szarży gdy wróg jest w zasięgu
 * - Obsługę obracania sprite'a
 * 
 * @param units Lista wszystkich jednostek na mapie
 */
void Cavalry::update(const std::vector<Unit*>& units) {
    if (!isAlive()) return;

    updateAttackCooldown(1.0f / 60.0f);
    updateCharge();

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
        sf::Vector2f direction;

        if (isCharging) {
            direction = chargeTarget - getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0) {
                direction /= length;
                proposedMove = direction * chargeSpeed;
            }
        }
        else {
            direction = closestEnemy->getPosition() - getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (length > 0) {
                direction /= length;

                if (minDistance <= attackRange) {
                    if (canAttack()) {
                        if (tryHit()) {
                            closestEnemy->takeDamage(damage);
                        }
                        resetAttackCooldown();
                    }

                    // Okrążanie przeciwnika
                    circlingAngle += 0.02f;
                    float circleX = closestEnemy->getPosition().x + cos(circlingAngle) * circlingRadius;
                    float circleY = closestEnemy->getPosition().y + sin(circlingAngle) * circlingRadius;

                    // Sprawdź czy punkt okrążania nie wychodzi poza granice pola
                    sf::FloatRect bounds = unitSprite.getGlobalBounds();
                    if (circleX < 0) circleX = 0;
                    if (circleX > 1400 - bounds.size.x) circleX = 1400 - bounds.size.x;
                    if (circleY < 0) circleY = 0;
                    if (circleY > 800 - bounds.size.y) circleY = 800 - bounds.size.y;

                    sf::Vector2f circlePoint(circleX, circleY);

                    direction = circlePoint - getPosition();
                    length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    if (length > 0) {
                        direction /= length;
                        proposedMove = direction * speed;
                    }
                }
                else if (minDistance <= 200.0f && chargeCooldown <= 0) {
                    startCharge(closestEnemy->getPosition());
                }
                else {
                    proposedMove = direction * speed;
                }
            }
        }

        // Zastosuj system kolizji do proponowanego ruchu, uwzględniając wszystkie jednostki
        sf::Vector2f actualMove = resolveCollision(units, proposedMove);
        setPosition(getPosition() + actualMove);

        // Ustaw kierunek sprite'a w zależności od kierunku ruchu
        if (actualMove.x != 0) {
            float scale_sign = (actualMove.x > 0) ? 1.f : -1.f;
            if (unitSprite.getScale().x * scale_sign < 0) {
                unitSprite.setScale({ -unitSprite.getScale().x, unitSprite.getScale().y });
            }
        }
    }
}
