#include "ButtonSFML.h"

/**
 * @brief Konstruktor klasy ButtonSFML
 * 
 * Inicjalizuje przycisk z podanymi parametrami i konfiguruje jego wygląd.
 * Ustawia kształt, pozycję, kolory oraz tekst przycisku.
 * 
 * @param x Pozycja X środka przycisku
 * @param y Pozycja Y środka przycisku
 * @param width Szerokość przycisku
 * @param height Wysokość przycisku
 * @param buttonText Tekst wyświetlany na przycisku
 * @param font Czcionka używana do wyświetlania tekstu
 */
ButtonSFML::ButtonSFML(float x, float y, float width, float height, const wchar_t* buttonText, const sf::Font& font)
    : text(font), isHovered(false) {

    // Konfiguracja kształtu przycisku
    shape.setSize({ width, height });
    shape.setOrigin({ width / 2, height / 2 });
    shape.setPosition({ x, y });
    shape.setFillColor(sf::Color(100, 100, 100));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);

    // Konfiguracja tekstu przycisku
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOrigin({ 35, text.getLocalBounds().position.y/2});
    text.setPosition({ x, y });
    sf::FloatRect textBounds = text.getLocalBounds();
}

/**
 * @brief Sprawdza czy mysz znajduje się nad przyciskiem
 * 
 * Metoda oblicza pozycję myszy względem prostokąta przycisku
 * i zwraca true jeśli mysz znajduje się w jego obrębie.
 * 
 * @param window Okno, w którym sprawdzana jest pozycja myszy
 * @return true jeśli mysz jest nad przyciskiem, false w przeciwnym wypadku
 */
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

/**
 * @brief Aktualizuje stan przycisku
 * 
 * Sprawdza czy mysz znajduje się nad przyciskiem i zmienia jego kolor
 * w zależności od stanu (najechanie myszką/brak najechania).
 * 
 * @param window Okno, w którym znajduje się przycisk
 */
void ButtonSFML::update(sf::RenderWindow& window) {
    isHovered = isMouseOver(window);

    if (isHovered) {
        shape.setFillColor(sf::Color(150, 150, 150));
    }
    else {
        shape.setFillColor(sf::Color(100, 100, 100));
    }
}

/**
 * @brief Rysuje przycisk w oknie
 * 
 * Metoda odpowiedzialna za renderowanie kształtu przycisku
 * i tekstu na nim w podanym oknie.
 * 
 * @param window Okno, w którym rysowany jest przycisk
 */
void ButtonSFML::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

/**
 * @brief Sprawdza czy przycisk został kliknięty
 * 
 * Metoda sprawdza czy mysz znajduje się nad przyciskiem
 * i czy został wciśnięty lewy przycisk myszy.
 * 
 * @param window Okno, w którym sprawdzane jest kliknięcie
 * @return true jeśli przycisk został kliknięty, false w przeciwnym wypadku
 */
bool ButtonSFML::isClicked(sf::RenderWindow& window) {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}
