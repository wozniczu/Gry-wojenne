// ButtonSFML.cpp
#include "ButtonSFML.h"

ButtonSFML::ButtonSFML(float x, float y, float width, float height, const std::string& buttonText, const sf::Font& font)
    : text(font), isHovered(false) {

    // Konfiguracja kszta³tu przycisku
    shape.setSize({ width, height });
    shape.setPosition({ x, y });
    shape.setFillColor(sf::Color(100, 100, 100));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);

    // Konfiguracja tekstu przycisku
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // Wyœrodkowanie tekstu na przycisku
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition({ x + width / 2.0f - 35, y + height / 2.0f - 10 });
}

bool ButtonSFML::isMouseOver(sf::RenderWindow& window) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = shape.getPosition().x;
    float btnPosY = shape.getPosition().y;
    float btnWidth = shape.getSize().x;
    float btnHeight = shape.getSize().y;

    return (mouseX >= btnPosX && mouseX <= btnPosX + btnWidth &&
        mouseY >= btnPosY && mouseY <= btnPosY + btnHeight);
}

void ButtonSFML::update(sf::RenderWindow& window) {
    isHovered = isMouseOver(window);

    if (isHovered) {
        shape.setFillColor(sf::Color(150, 150, 150));
    }
    else {
        shape.setFillColor(sf::Color(100, 100, 100));
    }
}

void ButtonSFML::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool ButtonSFML::isClicked(sf::RenderWindow& window) {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

