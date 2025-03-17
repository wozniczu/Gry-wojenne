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
    // Drużyny
    std::vector<Unit*> teamA;
    std::vector<Unit*> teamB;
    
    // Zasoby graficzne
    sf::Texture arenaTexture;
    sf::Sprite arenaSprite;
    
    // Stan bitwy
    bool finished;

public:
    // Konstruktory
    Battle();  // Konstruktor domyślny
    Battle(int infantryA, int archerA, int cavalryA,
           int infantryB, int archerB, int cavalryB);  // Konstruktor z parametrami
    ~Battle();

    // Główne metody
    void update();
    void draw(sf::RenderWindow& window);
    
    // Metody pomocnicze
    bool isFinished() const;
};