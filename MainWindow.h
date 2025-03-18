#pragma once
#include <SFML/Graphics.hpp>
#include "Battle.h"
#include "SliderSFML.h"
#include "ButtonSFML.h"
#include <thread>

enum class GameState {
    SETUP,
    BATTLE
};

class MainWindow {
private:
    sf::RenderWindow window;
    sf::Font font;
    GameState currentState;
    Battle* battle;
    
    // Suwaki dla drużyny A
    SliderSFML infantrySliderA;
    SliderSFML archerSliderA;
    SliderSFML cavalrySliderA;
    
    // Suwaki dla drużyny B
    SliderSFML infantrySliderB;
    SliderSFML archerSliderB;
    SliderSFML cavalrySliderB;
    
    // Przycisk startu
    ButtonSFML startButton;
    
    // Teksty dla etykiet
    sf::Text teamATitle;
    sf::Text teamBTitle;
    sf::Text labelInfantryA;
    sf::Text labelArcherA;
    sf::Text labelCavalryA;
    sf::Text labelInfantryB;
    sf::Text labelArcherB;
    sf::Text labelCavalryB;
    
    bool mouseReleased;

    // Metody pomocnicze
    void handleSetupState();
    void handleBattleState();
    void drawSetupScreen();
    void initializeUI();

public:
    MainWindow();
    ~MainWindow();
    
    void run();
}; 