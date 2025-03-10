#pragma once
#include "Unit.h"
#include <iostream>

class Infantry : public Unit {
private:
    // Stałe konfiguracyjne
    static constexpr float FORMATION_RADIUS = 50.0f;  // Promień w jakim jednostki otrzymują bonus do obrony
    static constexpr float MAX_DEFENSE_BONUS = 0.15f;  // Maksymalny bonus do obrony (15%)
    float baseDefense;  // Bazowa wartość obrony

public:
    // Konstruktor
    Infantry(float x, float y, bool team);
    
    // Nadpisana metoda z klasy bazowej
    void update(const std::vector<Unit*>& units) override;
    
private:
    // Metody pomocnicze
    float calculateDefenseBonus(const std::vector<Unit*>& units);
    sf::Vector2f calculateFormationMove(const std::vector<Unit*>& units, const sf::Vector2f& currentMove);
};
