#pragma once
#include <SFML/Graphics.hpp>
#include "SliderSFML.h"
#include "ButtonSFML.h"

class BattleSetupUI {
private:
    // Elementy interfejsu
    sf::Font font;
    sf::Text teamATitle;
    sf::Text teamBTitle;
    sf::Text labelInfantryA;
    sf::Text labelArcherA;
    sf::Text labelCavalryA;
    sf::Text labelInfantryB;
    sf::Text labelArcherB;
    sf::Text labelCavalryB;
    
    // Suwaki dla drużyny A
    SliderSFML infantrySliderA;
    SliderSFML archerSliderA;
    SliderSFML cavalrySliderA;
    
    // Suwaki dla drużyny B
    SliderSFML infantrySliderB;
    SliderSFML archerSliderB;
    SliderSFML cavalrySliderB;
    
    // Przycisk Start
    ButtonSFML startButton;

public:
    BattleSetupUI();
    
    // Metody do aktualizacji i rysowania
    void update(sf::RenderWindow& window, bool& mouseReleased);
    void draw(sf::RenderWindow& window);
    
    // Metody do pobierania wartości
    bool isStartClicked(sf::RenderWindow& window, bool& mouseReleased) const;
    int getInfantryA() const;
    int getArcherA() const;
    int getCavalryA() const;
    int getInfantryB() const;
    int getArcherB() const;
    int getCavalryB() const;
}; 