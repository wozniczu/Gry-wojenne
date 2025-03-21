#pragma once
#include "Unit.h"
#include "Arrow.h"
#include <iostream>
#include <list>

/**
 * @brief Klasa reprezentująca jednostki łuczników
 * 
 * Klasa implementująca specyficzne zachowania jednostek łuczników.
 * Charakteryzuje się atakami dystansowymi poprzez wystrzeliwanie strzał,
 * jest jednak słaba w walce wręcz.
 */
class Archer : public Unit {
private:
    std::list<Arrow> arrows;        ///< Lista aktywnych strzał
    float arrowSpeed;               ///< Prędkość strzał

public:
    /**
     * @brief Konstruktor łucznika
     * @param x Pozycja X jednostki
     * @param y Pozycja Y jednostki
     * @param team Przynależność do drużyny
     */
    Archer(float x, float y, bool team);
    
    /**
     * @brief Aktualizuje stan łucznika
     * @param units Lista wszystkich jednostek
     */
    void update(const std::vector<Unit*>& units) override;
    
    /**
     * @brief Rysuje strzały w oknie
     * @param window Okno do narysowania
     */
    void drawArrows(sf::RenderWindow& window);

    /**
     * @brief Wystrzeliwuje strzałę w kierunku celu
     * @param targetPos Pozycja celu
     */
    void shoot(const sf::Vector2f& targetPos);
};
