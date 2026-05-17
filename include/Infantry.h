#pragma once
#include "Unit.h"
#include <iostream>

/**
 * @brief Klasa reprezentująca jednostki piechoty
 * 
 * Klasa implementująca specyficzne zachowania jednostek piechoty.
 * Charakteryzuje się zwiększoną obroną w formacji oraz wolniejszym
 * poruszaniem się w porównaniu do kawalerii.
 */
class Infantry : public Unit {
private:
    // Stałe konfiguracyjne
    static constexpr float FORMATION_RADIUS = 20.0f;    ///< Promień formacji
    static constexpr float MAX_DEFENSE_BONUS = 0.3f;    ///< Maksymalny bonus do obrony
    float baseDefense;                                  ///< Bazowa wartość obrony

    /**
     * @brief Oblicza bonus do obrony w zależności od formacji
     * @param units Lista wszystkich jednostek
     * @return Bonus do obrony
     */
    float calculateDefenseBonus(const std::vector<Unit*>& units);

    /**
     * @brief Oblicza ruch w formacji
     * @param units Lista wszystkich jednostek
     * @param currentMove Aktualny ruch
     * @return Zmodyfikowany ruch
     */
    sf::Vector2f calculateFormationMove(const std::vector<Unit*>& units, const sf::Vector2f& currentMove);

public:
    /**
     * @brief Konstruktor piechura
     * @param x Pozycja X jednostki
     * @param y Pozycja Y jednostki
     * @param team Przynależność do drużyny
     */
    Infantry(float x, float y, bool team);
    
    /**
     * @brief Aktualizuje stan piechura
     * @param units Lista wszystkich jednostek
     */
    void update(const std::vector<Unit*>& units) override;
};
