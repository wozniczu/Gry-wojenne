#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

class Unit {
protected:
    sf::Texture unitTexture;
    sf::Sprite unitSprite;
    float health;
    float damage;
    float speed;
    float attackRange;
    float attackSpeed;
    float attackCooldown;
    float hitChance;      // Prawdopodobieństwo trafienia (0.0 - 1.0)
    float defense;        // Wartość obrony (0.0 - 1.0)
    sf::Vector2f velocity;
    bool alive;
    bool team;
    static constexpr float COLLISION_RADIUS = 5.0f; // Promień kolizji jednostki

public:
    Unit(float x, float y, bool team, float health, float damage, float speed, float attackRange, float attackSpeed, float hitChance, float defense);
    virtual ~Unit() = default;

    virtual void update(const std::vector<Unit*>& units) = 0;
    void takeDamage(float dmg);
    bool canAttack() const;
    bool tryHit() const;
    void resetAttackCooldown();
    void updateAttackCooldown(float deltaTime);

    float getDistance(sf::Vector2f otherPos) const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);

    bool checkCollision(const Unit* other) const;
    sf::Vector2f resolveCollision(const std::vector<Unit*>& units, const sf::Vector2f& proposedMove);
    float getCollisionRadius() const { return COLLISION_RADIUS; }

    bool isAlive() const { return alive; }
    bool getTeam() const { return team; }
    float getRange() const { return attackRange; }
    float getHealth() const { return health; }
    float getHitChance() const { return hitChance; }
    float getDefense() const { return defense; }
    void setDefense(float newDefense) { defense = newDefense; }
    float getAttackSpeed() const { return attackSpeed; }
    const sf::Sprite& getShape() const { return unitSprite; }
};

