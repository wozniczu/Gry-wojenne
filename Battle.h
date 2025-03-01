#pragma once
#include "Unit.h"
#include "Infantry.h"
#include "Archer.h"
#include "Cavalry.h"
#include <vector>
#include <random>

class Battle {
private:
    std::vector<Unit*> team;
    std::vector<Unit*> teamB;
    std::mt19937 rng;

public:
    Battle();
    ~Battle();
    void update();
    void draw(sf::RenderWindow& window);
    void removeDeadUnits();
    void displayUnitsHealth();
    bool isFinished();
};
