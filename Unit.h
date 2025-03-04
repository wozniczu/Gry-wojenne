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
    sf::Vector2f velocity;
    bool alive;
    bool team;

public:
    Unit(float x, float y, bool team, float health, float damage, float speed, float attackRange);
    virtual ~Unit() = default;

    virtual void update(const std::vector<Unit*>& enemies);
    void takeDamage(float dmg);

    float getDistance(sf::Vector2f otherPos) const;
    sf::Vector2f getPosition() const;

    bool isAlive() const;
    const sf::Sprite& getShape() const;

    bool getTeam() const { return team; };
    float getRange() const { return attackRange; };
    float getHealth() const { return health; };
};

