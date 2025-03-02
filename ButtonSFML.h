#pragma once
#include <SFML/Graphics.hpp>

class ButtonSFML {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    bool isHovered;

public:
    ButtonSFML(float x, float y, float width, float height, const std::string& buttonText, const sf::Font& font);
    bool isMouseOver(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window);
};

