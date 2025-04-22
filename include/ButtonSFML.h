#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Klasa reprezentująca przycisk w interfejsie SFML
 * 
 * Klasa odpowiedzialna za tworzenie i obsługę przycisku w interfejsie użytkownika.
 * Obsługuje interakcje kliknięcia oraz efekt najechania myszką, zawiera logikę
 * rysowania przycisku i wizualnego feedbacku dla użytkownika.
 */
class ButtonSFML {
private:
    sf::RectangleShape shape;      ///< Kształt przycisku
    sf::Text text;                  ///< Tekst przycisku
    sf::Font font;                  ///< Czcionka używana w tekście
    bool isHovered;                 ///< Flaga określająca czy mysz jest nad przyciskiem

public:
    /**
     * @brief Konstruktor przycisku
     * @param x Pozycja X przycisku
     * @param y Pozycja Y przycisku
     * @param width Szerokość przycisku
     * @param height Wysokość przycisku
     * @param text Tekst przycisku
     * @param font Czcionka do użycia
     */
    ButtonSFML(float x, float y, float width, float height, const wchar_t* text, const sf::Font& font);

    /**
     * @brief Rysuje przycisk w oknie
     * @param window Okno do narysowania
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Sprawdza czy przycisk został kliknięty
     * @param window Okno, w którym sprawdzane jest kliknięcie
     * @return true jeśli przycisk został kliknięty
     */
    bool isClicked(sf::RenderWindow& window);

    /**
     * @brief Sprawdza czy mysz znajduje się nad przyciskiem
     * @param window Okno, w którym sprawdzana jest pozycja myszy
     * @return true jeśli mysz jest nad przyciskiem
     */
    bool isMouseOver(sf::RenderWindow& window);

    /**
     * @brief Aktualizuje stan przycisku
     * @param window Okno, w którym znajduje się przycisk
     */
    void update(sf::RenderWindow& window);
};

