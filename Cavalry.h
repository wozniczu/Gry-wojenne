#pragma once
#include "Unit.h"
#include <iostream>

class Cavalry : public Unit {
private:
    // Parametry szarży
    bool isCharging;           // Czy jednostka wykonuje szarżę
    float chargeSpeed;         // Prędkość podczas szarży
    float chargeCooldown;      // Czas odnowienia szarży
    float maxChargeCooldown;   // Maksymalny czas odnowienia szarży
    sf::Vector2f chargeTarget; // Punkt docelowy szarży
    
    // Parametry okrążania
    float circlingRadius;      // Promień okrążania przeciwnika
    float circlingAngle;       // Aktualny kąt okrążania
    bool returningFromCharge;  // Czy jednostka wraca po szarży

public:
    // Konstruktor
    Cavalry(float x, float y, bool team);
    
    // Nadpisana metoda z klasy bazowej
    void update(const std::vector<Unit*>& units) override;
    
    // Metody specyficzne dla kawalerii
    void startCharge(const sf::Vector2f& target);
    void updateCharge();
};
