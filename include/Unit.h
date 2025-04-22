#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <iostream>

/**
 * @brief Bazowa klasa abstrakcyjna dla wszystkich jednostek w grze
 * 
 * Klasa definiująca podstawowe atrybuty i zachowania wspólne dla wszystkich
 * typów jednostek. Zawiera mechanizmy kolizji, ataku i obrony.
 */
class Unit {
public:
    float health;                   ///< Aktualne zdrowie jednostki
    float damage;                   ///< Obrażenia zadawane przez jednostkę
    float speed;                    ///< Prędkość poruszania się jednostki
    float attackRange;              ///< Zasięg ataku jednostki
    float attackSpeed;              ///< Szybkość ataku jednostki
    float attackCooldown;           ///< Czas oczekiwania między atakami
    float hitChance;                ///< Szansa na trafienie przeciwnika
    float defense;                  ///< Wartość obrony jednostki
    sf::Vector2f velocity;          ///< Wektor prędkości jednostki
    bool alive;                     ///< Flaga określająca czy jednostka żyje
    bool team;                      ///< Flaga określająca przynależność do drużyny
    sf::Texture unitTexture;        ///< Tekstura jednostki
    sf::Sprite unitSprite;          ///< Sprite jednostki
    static constexpr float COLLISION_RADIUS = 10.0f; // Promień kolizji jednostki

public:
    /**
     * @brief Konstruktor jednostki
     * @param x Pozycja X jednostki
     * @param y Pozycja Y jednostki
     * @param team Przynależność do drużyny
     * @param health Zdrowie jednostki
     * @param damage Obrażenia jednostki
     * @param speed Prędkość jednostki
     * @param attackRange Zasięg ataku
     * @param attackSpeed Szybkość ataku
     * @param hitChance Szansa na trafienie
     * @param defense Wartość obrony
     */
    Unit(float x, float y, bool team, float health, float damage, float speed,
         float attackRange, float attackSpeed, float hitChance, float defense);

    /**
     * @brief Wirtualny destruktor
     */
    virtual ~Unit() = default;

    /**
     * @brief Aktualizuje stan jednostki
     * @param units Lista wszystkich jednostek na polu bitwy
     */
    virtual void update(const std::vector<Unit*>& units) = 0;

    /**
     * @brief Obsługuje otrzymanie obrażeń
     * @tparam T Typ wartości obrażeń (int, float, string)
     * @param dmg Wartość otrzymanych obrażeń
     */
    template<typename T>
    void takeDamage(T dmg);

    /**
     * @brief Specjalizacja dla obsługi string jako obrażeń
     * @param dmgStr String zawierający wartość obrażeń
     */
    template<>
    void takeDamage<std::string>(std::string dmgStr);

    /**
     * @brief Sprawdza czy jednostka może atakować
     * @return true jeśli jednostka może atakować
     */
    bool canAttack() const;

    /**
     * @brief Sprawdza czy atak trafił przeciwnika
     * @return true jeśli atak trafił
     */
    bool tryHit() const;

    /**
     * @brief Resetuje cooldown ataku
     */
    void resetAttackCooldown();

    /**
     * @brief Aktualizuje cooldown ataku
     * @param deltaTime Czas od ostatniej aktualizacji
     */
    void updateAttackCooldown(float deltaTime);

    /**
     * @brief Oblicza odległość do innej pozycji
     * @param otherPos Pozycja do obliczenia odległości
     * @return Odległość do podanej pozycji
     */
    float getDistance(sf::Vector2f otherPos) const;

    /**
     * @brief Pobiera aktualną pozycję jednostki
     * @return Aktualna pozycja
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Ustawia pozycję jednostki
     * @param pos Nowa pozycja
     */
    void setPosition(const sf::Vector2f& pos);

    /**
     * @brief Rozwiązuje kolizję z innymi jednostkami
     * @param units Lista wszystkich jednostek
     * @param proposedMove Proponowany ruch
     * @return Końcowa pozycja po rozwiązaniu kolizji
     */
    sf::Vector2f resolveCollision(const std::vector<Unit*>& units, const sf::Vector2f& proposedMove);

    /**
     * @brief Pobiera promień kolizji jednostki
     * @return Promień kolizji
     */
    float getCollisionRadius() const { return COLLISION_RADIUS; }

    /**
     * @brief Sprawdza czy jednostka żyje
     * @return true jeśli jednostka żyje
     */
    bool isAlive() const { return alive; }

    /**
     * @brief Pobiera przynależność do drużyny
     * @return true jeśli jednostka należy do drużyny
     */
    bool getTeam() const { return team; }

    /**
     * @brief Pobiera zasięg ataku
     * @return Zasięg ataku
     */
    float getRange() const { return attackRange; }

    /**
     * @brief Pobiera aktualne zdrowie
     * @return Aktualne zdrowie
     */
    float getHealth() const { return health; }

    /**
     * @brief Pobiera szansę na trafienie
     * @return Szansa na trafienie
     */
    float getHitChance() const { return hitChance; }

    /**
     * @brief Pobiera wartość obrony
     * @return Wartość obrony
     */
    float getDefense() const { return defense; }

    /**
     * @brief Ustawia wartość obrony
     * @param newDefense Nowa wartość obrony
     */
    void setDefense(float newDefense) { defense = newDefense; }

    /**
     * @brief Pobiera szybkość ataku
     * @return Szybkość ataku
     */
    float getAttackSpeed() const { return attackSpeed; }

    /**
     * @brief Pobiera sprite jednostki
     * @return Sprite jednostki
     */
    const sf::Sprite& getShape() const { return unitSprite; }

    /**
     * @brief Pobiera wektor prędkości jednostki
     * @return Wektor prędkości
     */
    const sf::Vector2f& getVelocity() const { return velocity; }
};
