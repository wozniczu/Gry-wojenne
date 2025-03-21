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
	int minValue;                   ///< Minimalna wartość suwaka
	int maxValue;                   ///< Maksymalna wartość suwaka
	int xCord;                      ///< Pozycja X suwaka
	int yCord;                      ///< Pozycja Y suwaka
	int axisWidth;                  ///< Szerokość osi suwaka
	int axisHeight;                 ///< Wysokość osi suwaka
	int sliderWidth;                ///< Szerokość suwaka
	int sliderHeight;               ///< Wysokość suwaka
	float sliderValue;              ///< Aktualna wartość suwaka
	bool isDragging;                ///< Flaga określająca czy suwak jest przeciągany
	sf::Vector2f position;          ///< Aktualna pozycja suwaka

	/**
	 * @brief Aktualizuje pozycję uchwytu suwaka
	 */
	void updateKnobPosition();

public:
	/**
	 * @brief Konstruktor suwaka
	 * @param x Pozycja X suwaka
	 * @param y Pozycja Y suwaka
	 */
	SliderSFML(int x, int y);

	/**
	 * @brief Tworzy tekst dla suwaka
	 * @param x Pozycja X tekstu
	 * @param y Pozycja Y tekstu
	 * @param z Treść tekstu
	 * @param fontSize Rozmiar czcionki
	 * @return Utworzony obiekt tekstu
	 */
	sf::Text returnText(int x, int y, std::string z, int fontSize);

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
	void setSliderValue(float newValue);

	/**
	 * @brief Ustawia wartość suwaka jako procent zakresu
	 * @param newPercentValue Nowa wartość procentowa
	 */
	void setSliderPercentValue(float newPercentValue);

	/**
	 * @brief Rysuje suwak w oknie
	 * @param window Okno do narysowania
	 */
	void draw(sf::RenderWindow & window);

	/**
	 * @brief Obsługuje zdarzenia myszy dla suwaka
	 * @param event Zdarzenie do obsługi
	 * @param window Okno, w którym wystąpiło zdarzenie
	 */
	void handleEvent(const sf::Event& event, sf::RenderWindow& window);
};

