#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <thread>
#include <memory>
#include <iostream>
#include "Unit.h"
#include "Infantry.h"
#include "Archer.h"
#include "Cavalry.h"

/**
 * @brief Klasa zarządzająca przebiegiem bitwy
 * 
 * Klasa odpowiedzialna za zarządzanie przebiegiem bitwy, tworzenie
 * i aktualizację jednostek obu drużyn, sprawdzanie warunków
 * zakończenia bitwy oraz zarządzanie stanem areny.
 */
class Battle {
private:
    // Drużyny
    std::vector<Unit*> teamA;       ///< Wektor jednostek drużyny A
    std::vector<Unit*> teamB;       ///< Wektor jednostek drużyny B
    
    // Zasoby graficzne
    sf::Texture arenaTexture;       ///< Tekstura areny
    sf::Sprite arenaSprite;         ///< Sprite areny
    
    // Stan bitwy
    bool finished;                  ///< Flaga określająca czy bitwa się zakończyła

public:
    /**
     * @brief Konstruktor domyślny
     */
    Battle();  // Konstruktor domyślny

    /**
     * @brief Konstruktor z określoną liczbą jednostek
     * @param infantryA Liczba piechoty drużyny A
     * @param archerA Liczba łuczników drużyny A
     * @param cavalryA Liczba kawalerii drużyny A
     * @param infantryB Liczba piechoty drużyny B
     * @param archerB Liczba łuczników drużyny B
     * @param cavalryB Liczba kawalerii drużyny B
     */
    Battle(int infantryA, int archerA, int cavalryA,
           int infantryB, int archerB, int cavalryB);

    /**
     * @brief Destruktor
     */
    ~Battle();

    // Główne metody
    /**
     * @brief Aktualizuje stan bitwy
     */
    void update();

    /**
     * @brief Rysuje bitwę w oknie
     * @param window Okno do narysowania
     */
    void draw(sf::RenderWindow& window);
    
    // Metody pomocnicze
    /**
     * @brief Sprawdza czy bitwa się zakończyła
     * @return true jeśli bitwa się zakończyła
     */
    bool isFinished() const;
};