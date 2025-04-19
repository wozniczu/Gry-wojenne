#include "ButtonSFML.h"
#include <iostream>
ButtonSFML::ButtonSFML(float x, float y, float width, float height, const std::string& buttonText, const sf::Font& font)
    : text(font), isHovered(false) {

    // Konfiguracja kszta�tu przycisku
    shape.setSize({ width, height });
    shape.setOrigin({ width / 2, height / 2 });
    shape.setPosition({ x, y });
    shape.setFillColor(sf::Color(100, 100, 100));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);

    // Konfiguracja tekstu przycisku
    text.setFont(font);
    text.setString(std::wstring(buttonText.begin(), buttonText.end()).c_str());
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOrigin({ 35, text.getLocalBounds().position.y/2});
    text.setPosition({ x, y });
    sf::FloatRect textBounds = text.getLocalBounds();
}

bool ButtonSFML::isMouseOver(sf::RenderWindow& window) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = shape.getPosition().x;
    float btnPosY = shape.getPosition().y;
    float btnWidth = shape.getSize().x/2;
    float btnHeight = shape.getSize().y/2;

    return (mouseX >= btnPosX - btnWidth && mouseX <= btnPosX + btnWidth &&
        mouseY >= btnPosY - btnHeight && mouseY <= btnPosY + btnHeight);
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

