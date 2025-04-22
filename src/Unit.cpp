#include "Unit.h"

/**
 * @brief Konstruktor klasy Unit
 * 
 * Inicjalizuje jednostkę z podanymi parametrami i ładuje odpowiednią teksturę.
 * 
 * @param x Pozycja początkowa X jednostki
 * @param y Pozycja początkowa Y jednostki
 * @param team Przynależność do drużyny (true - niebieska, false - czerwona)
 * @param health Początkowa wartość zdrowia
 * @param damage Zadawane obrażenia
 * @param speed Prędkość poruszania
 * @param attackRange Zasięg ataku
 * @param attackSpeed Szybkość ataku
 * @param hitChance Szansa na trafienie
 * @param defense Wartość obrony
 */
Unit::Unit(float x, float y, bool team, float health, float damage, float speed, float attackRange, float attackSpeed, float hitChance, float defense)
    : health(health), damage(damage), speed(speed), attackRange(attackRange), attackSpeed(attackSpeed),
    attackCooldown(0.f), hitChance(hitChance), defense(defense), alive(true), team(team), unitSprite(unitTexture) {

    // Wybór ikony w zależności od drużyny
    std::string texturePath = team ? "textures/infantry_blue.png" : "textures/infantry_red.png";

    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie można załadować tekstury: " << texturePath << std::endl;
    }

    unitSprite.setTexture(unitTexture);
    unitSprite.setPosition({ x, y });

    // Skalowanie do odpowiedniego rozmiaru
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

/**
 * @brief Oblicza i aplikuje obrażenia do jednostki
 * 
 * Redukuje otrzymane obrażenia o wartość obrony i odejmuje od zdrowia.
 * Jeśli zdrowie spadnie do 0, oznacza jednostkę jako martwą.
 * 
 * @tparam T Typ wartości obrażeń (int, float)
 * @param dmg Wartość otrzymanych obrażeń
 */
template<typename T>
void Unit::takeDamage(T dmg) {
    float reducedDamage = static_cast<float>(dmg) * (1.0f - defense);
    health -= reducedDamage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

/**
 * @brief Specjalizacja metody takeDamage dla typu string
 * 
 * Próbuje przekonwertować string na float i zastosować obrażenia.
 * W przypadku błędu konwersji stosuje domyślne obrażenia (0).
 * 
 * @param dmgStr String zawierający wartość obrażeń
 */
template<>
void Unit::takeDamage<std::string>(std::string dmgStr) {
    try {
        float dmg = std::stof(dmgStr);
        takeDamage(dmg); // użycie wersji float
    } catch (...) {
        // Domyślne obrażenia jeśli konwersja się nie uda
        takeDamage(0.0f);
    }
}

/**
 * @brief Sprawdza czy atak trafił przeciwnika
 * 
 * Generuje losową wartość i porównuje z szansą na trafienie.
 * 
 * @return true jeśli atak trafił, false w przeciwnym wypadku
 */
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

/**
 * @brief Rozwiązuje kolizje jednostki z innymi obiektami
 * 
 * Oblicza końcową pozycję uwzględniając:
 * - Kolizje z innymi jednostkami (odpychanie)
 * - Granice mapy (1400x800)
 * 
 * @param units Lista wszystkich jednostek na mapie
 * @param proposedMove Proponowany wektor ruchu
 * @return Skorygowany wektor ruchu uwzględniający kolizje
 */
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

    // Sprawdź granice okna (1400x800)
    sf::FloatRect bounds = unitSprite.getGlobalBounds();
    
    // Lewa granica
    if (finalPosition.x < 0) {
        finalPosition.x = 0;
    }
    // Prawa granica
    if (finalPosition.x > 1400 - bounds.size.x) {
        finalPosition.x = 1400 - bounds.size.x;
    }
    // Górna granica
    if (finalPosition.y < 0) {
        finalPosition.y = 0;
    }
    // Dolna granica
    if (finalPosition.y > 800 - bounds.size.y) {
        finalPosition.y = 800 - bounds.size.y;
    }
    
    // Zwróć wektor przesunięcia
    return finalPosition - getPosition();
}
