#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <memory>
#include <iostream>

class Unit;

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
    std::vector<std::unique_ptr<Unit>> teamA;       ///< Jednostki drużyny A
    std::vector<std::unique_ptr<Unit>> teamB;       ///< Jednostki drużyny B
    
    // Zasoby graficzne
    sf::Texture arenaTexture;       ///< Tekstura areny
    sf::Sprite arenaSprite;         ///< Sprite areny
    sf::Font bannerFont;            ///< Czcionka komunikatu końcowego
    bool bannerFontOk = false;      ///< Czy załadowano czcionkę baneru
    
    // Stan bitwy
    bool finished;                  ///< Flaga określająca czy bitwa się zakończyła

public:
    /**
     * @brief Konstruktor domyślny
     */
    Battle();

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
     * @brief Destruktor (definicja w .cpp — pełny typ Unit)
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
