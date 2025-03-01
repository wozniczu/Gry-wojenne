#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Unit {
protected:
    sf::CircleShape shape;
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
    const sf::CircleShape& getShape() const;

    bool getTeam() const { return team; };
    float getRange() const { return health; };
    float getHealth() const { return health; };
};

