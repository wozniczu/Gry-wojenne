#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <thread>
#include "Unit.h"
#include "Infantry.h"
#include "Archer.h"
#include "Cavalry.h"

class Battle {
private:
    std::vector<Unit*> teamA;
    std::vector<Unit*> teamB;
    sf::Texture arenaTexture;
    sf::Sprite arenaSprite;
    bool finished;

public:
    Battle(); // Konstruktor domyœlny
    Battle(int infantryA, int archerA, int cavalryA, int infantryB, int archerB, int cavalryB); // Nowy konstruktor z parametrami
    ~Battle();

    void update();
    void draw(sf::RenderWindow& window);
    bool isFinished() const;
    void displayUnitsHealth() const;
};