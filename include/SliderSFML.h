#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @brief Klasa reprezentująca suwak w interfejsie SFML
 * 
 * Klasa odpowiedzialna za tworzenie i obsługę suwaka w interfejsie użytkownika.
 * Umożliwia wybór wartości poprzez interakcję z myszką, zawiera logikę rysowania
 * suwaka oraz aktualizacji jego wartości.
 */
class SliderSFML
{
private:
	sf::RectangleShape slider;      ///< Kształt suwaka
	sf::RectangleShape axis;        ///< Kształt osi suwaka
	sf::Font font;                  ///< Czcionka używana w tekście
	sf::Text text;                  ///< Tekst wyświetlany przy suwaku
	int minValue;                 ///< Minimalna wartość suwaka
	int maxValue;                 ///< Maksymalna wartość suwaka
	float xCord;                    ///< Pozycja X suwaka
	float yCord;                    ///< Pozycja Y suwaka
	float axisWidth;                ///< Szerokość osi suwaka
	float axisHeight;               ///< Wysokość osi suwaka
	float sliderWidth;              ///< Szerokość suwaka
	float sliderHeight;             ///< Wysokość suwaka
	int sliderValue;              ///< Aktualna wartość suwaka
	bool isDragging;                ///< Flaga określająca czy suwak jest przeciągany
	sf::Vector2f position;          ///< Aktualna pozycja suwaka

public:
	/**
	 * @brief Konstruktor suwaka
	 * @param x Pozycja X suwaka
	 * @param y Pozycja Y suwaka
	 */
	SliderSFML(float x, float y);

	/**
	 * @brief Tworzy tekst dla suwaka
	 * @param x Pozycja X tekstu
	 * @param y Pozycja Y tekstu
	 * @param z Treść tekstu
	 * @param fontSize Rozmiar czcionki
	 * @return Utworzony obiekt tekstu
	 */
	sf::Text returnText(float x, float y, std::string z, float fontSize);

	/**
	 * @brief Inicjalizuje suwak z określonym zakresem wartości
	 * @param min Minimalna wartość
	 * @param max Maksymalna wartość
	 */
	void create(int min, int max);

	/**
	 * @brief Aktualizuje logikę suwaka
	 * @param window Okno, w którym znajduje się suwak
	 */
	void logic(sf::RenderWindow &window);

	/**
	 * @brief Pobiera aktualną wartość suwaka
	 * @return Aktualna wartość
	 */
	float getSliderValue();

	/**
	 * @brief Ustawia wartość suwaka
	 * @param newValue Nowa wartość
	 */
	void setSliderValue(int newValue);

	/**
	 * @brief Ustawia wartość suwaka jako procent zakresu
	 * @param newPercentValue Nowa wartość procentowa
	 */
	void setSliderPercentValue(int newPercentValue);

	/**
	 * @brief Rysuje suwak w oknie
	 * @param window Okno do narysowania
	 */
	void draw(sf::RenderWindow & window);
};