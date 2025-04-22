#pragma once
#include "Unit.h"
#include <vector>
#include <cmath>

/**
 * @brief Klasa reprezentująca jednostki kawalerii
 * 
 * Klasa implementująca specyficzne zachowania jednostek kawalerii.
 * Charakteryzuje się największą prędkością poruszania się oraz
 * specjalnymi zdolnościami takimi jak szarża i okrążanie przeciwników.
 */
class Cavalry : public Unit {
private:
    // Parametry szarży
    bool isCharging;                ///< Flaga określająca czy jednostka wykonuje szarżę
    float chargeSpeed;              ///< Prędkość podczas szarży
    float chargeCooldown;           ///< Czas oczekiwania na następną szarżę
    float maxChargeCooldown;        ///< Maksymalny czas oczekiwania na szarżę
    sf::Vector2f chargeTarget;      ///< Cel szarży

    // Parametry okrążania
    float circlingRadius;           ///< Promień okrążania
    float circlingAngle;            ///< Aktualny kąt okrążania
    bool returningFromCharge;       ///< Flaga określająca czy jednostka wraca po szarży

    /**
     * @brief Rozpoczyna szarżę w kierunku celu
     * @param target Pozycja celu szarży
     */
    void startCharge(const sf::Vector2f& target);

    /**
     * @brief Aktualizuje stan szarży
     */
    void updateCharge();

public:
    /**
     * @brief Konstruktor kawalerzysty
     * @param x Pozycja X jednostki
     * @param y Pozycja Y jednostki
     * @param team Przynależność do drużyny
     */
    Cavalry(float x, float y, bool team);
    
    /**
     * @brief Aktualizuje stan kawalerzysty
     * @param units Lista wszystkich jednostek
     */
    void update(const std::vector<Unit*>& units) override;
};
