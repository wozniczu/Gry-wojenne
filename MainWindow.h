#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include "SliderSFML.h"
#include "ButtonSFML.h"
#include "Battle.h"

/**
 * @brief Stan gry określający aktualny etap rozgrywki
 */
enum class GameState {
    SETUP,  ///< Ekran konfiguracji jednostek
    BATTLE  ///< Trwająca bitwa
};

/**
 * @brief Główna klasa okna aplikacji
 * 
 * Klasa odpowiedzialna za zarządzanie oknem aplikacji, obsługę interfejsu użytkownika
 * oraz przejścia między stanami gry. Inicjalizuje i zarządza komponentami UI,
 * obsługuje zdarzenia oraz przejścia między stanami gry.
 */
class MainWindow {
private:
    sf::RenderWindow window;        ///< Okno aplikacji SFML
    sf::Font font;                  ///< Czcionka używana w interfejsie
    GameState currentState;         ///< Aktualny stan gry
    Battle* battle;                 ///< Wskaźnik do aktualnej bitwy
    
    // Suwaki dla drużyny A
    SliderSFML infantrySliderA;    ///< Suwak wyboru liczby piechoty dla drużyny A
    SliderSFML archerSliderA;      ///< Suwak wyboru liczby łuczników dla drużyny A
    SliderSFML cavalrySliderA;     ///< Suwak wyboru liczby kawalerii dla drużyny A
    
    // Suwaki dla drużyny B
    SliderSFML infantrySliderB;    ///< Suwak wyboru liczby piechoty dla drużyny B
    SliderSFML archerSliderB;      ///< Suwak wyboru liczby łuczników dla drużyny B
    SliderSFML cavalrySliderB;     ///< Suwak wyboru liczby kawalerii dla drużyny B
    
    // Przycisk startu
    ButtonSFML startButton;        ///< Przycisk rozpoczęcia bitwy
    
    // Teksty dla etykiet
    sf::Text teamATitle;           ///< Tytuł drużyny A
    sf::Text teamBTitle;           ///< Tytuł drużyny B
    sf::Text labelInfantryA;       ///< Etykieta piechoty drużyny A
    sf::Text labelArcherA;         ///< Etykieta łuczników drużyny A
    sf::Text labelCavalryA;        ///< Etykieta kawalerii drużyny A
    sf::Text labelInfantryB;       ///< Etykieta piechoty drużyny B
    sf::Text labelArcherB;         ///< Etykieta łuczników drużyny B
    sf::Text labelCavalryB;        ///< Etykieta kawalerii drużyny B
    
    bool mouseReleased;            ///< Flaga określająca czy przycisk myszy został zwolniony

    /**
     * @brief Obsługuje stan konfiguracji jednostek
     */
    void handleSetupState();

    /**
     * @brief Obsługuje stan trwającej bitwy
     */
    void handleBattleState();

    /**
     * @brief Rysuje ekran konfiguracji jednostek
     */
    void drawSetupScreen();

    /**
     * @brief Inicjalizuje komponenty interfejsu użytkownika
     */
    void initializeUI();

public:
    /**
     * @brief Konstruktor głównego okna
     */
    MainWindow();

    /**
     * @brief Destruktor głównego okna
     */
    ~MainWindow();

    /**
     * @brief Uruchamia główną pętlę aplikacji
     */
    void run();
}; 