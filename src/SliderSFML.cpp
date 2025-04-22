#include "SliderSFML.h"

/**
 * @brief Konstruktor klasy SliderSFML
 * 
 * Inicjalizuje suwak z podanymi współrzędnymi i domyślnymi parametrami.
 * Ładuje czcionkę, konfiguruje kształt osi i suwaka.
 * 
 * @param x Pozycja X lewego krańca suwaka
 * @param y Pozycja Y środka suwaka
 */
SliderSFML::SliderSFML(float x, float y) : text(font)
{
	xCord = x;
	yCord = y;
	axisHeight = 10.f;
	axisWidth = 200.f;
	sliderWidth = 20.f;
	sliderHeight = 30.f;

	if (!font.openFromFile("fonts/Arial.ttf"))
		std::cerr << "Błąd podczas ładowania fonts/Arial.ttf.\n";

	text.setFont(font);
	text.setFillColor(sf::Color::White);

	axis.setPosition({ x, y });
    axis.setOrigin({ 0.0f, axisHeight / 2.0f });
	axis.setSize(sf::Vector2f(axisWidth, axisHeight));
	axis.setFillColor(sf::Color(63,63,63));
	slider.setPosition({ x, y });
    slider.setOrigin(sf::Vector2f(sliderWidth / 2.0f, sliderHeight / 2.0f));
	slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(sf::Color(192,192,192));
}

/**
 * @brief Tworzy obiekt tekstu dla suwaka
 * 
 * @param x Pozycja X tekstu
 * @param y Pozycja Y tekstu
 * @param z Treść tekstu
 * @param fontSize Rozmiar czcionki
 * @return sf::Text Gotowy obiekt tekstu
 */
sf::Text SliderSFML::returnText(float x, float y, std::string z, float fontSize)
{
	text.setCharacterSize(fontSize);
	text.setPosition({ x, y });
	text.setString(z);
	return text;
}

/**
 * @brief Inicjalizuje zakres wartości suwaka
 * 
 * @param min Minimalna wartość suwaka
 * @param max Maksymalna wartość suwaka
 */
void SliderSFML::create(int min, int max)
{
	sliderValue = min;
	minValue = min;
	maxValue = max;
}

/**
 * @brief Obsługuje logikę przeciągania suwaka
 * 
 * Metoda odpowiedzialna za:
 * - Wykrywanie kliknięcia na suwak
 * - Przeciąganie suwaka myszą
 * - Obliczanie aktualnej wartości na podstawie pozycji
 * 
 * @param window Okno, w którym znajduje się suwak
 */
void SliderSFML::logic(sf::RenderWindow& window)
{
	if (slider.getGlobalBounds().contains({ static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y) })
		&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		isDragging = true;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		isDragging = false;
	}

	if (isDragging)
	{
		float mouseX = sf::Mouse::getPosition(window).x;

		// Ograniczenie pozycji do zakresu slidera
		if (mouseX < xCord)
			mouseX = xCord;
		else if (mouseX > xCord + axisWidth)
			mouseX = xCord + axisWidth;

		slider.setPosition({ mouseX, yCord });
		sliderValue = (minValue + ((slider.getPosition().x - xCord) /
			axisWidth * (maxValue - minValue)));
	}
}

/**
 * @brief Pobiera aktualną wartość suwaka
 * 
 * @return float Aktualna wartość suwaka
 */
float SliderSFML::getSliderValue()
{
	return sliderValue;
}

/**
 * @brief Ustawia wartość suwaka
 * 
 * @param newValue Nowa wartość (musi być w zakresie min-max)
 */
void SliderSFML::setSliderValue(int newValue)
{
	if (newValue >= minValue && newValue <= maxValue)
	{
		sliderValue = newValue;
		float diff = maxValue - minValue;
		float diff2 = newValue - minValue;
		float zzz = axisWidth / diff;
		float posX = zzz * diff2;
		posX += xCord;
		slider.setPosition({ posX, yCord });
	}
}

/**
 * @brief Ustawia wartość suwaka jako procent zakresu
 * 
 * @param newPercentValue Nowa wartość procentowa (0-100)
 */
void SliderSFML::setSliderPercentValue(int newPercentValue)
{
	if (newPercentValue >= 0 && newPercentValue <= 100)
	{
		sliderValue = newPercentValue / 100 * maxValue;
		slider.setPosition({ xCord + (axisWidth * newPercentValue / 100), yCord });
	}
}

/**
 * @brief Rysuje suwak w oknie
 * 
 * Metoda odpowiedzialna za:
 * - Aktualizację logiki suwaka
 * - Rysowanie osi i suwaka
 * - Wyświetlanie etykiet wartości
 * 
 * @param window Okno, w którym rysowany jest suwak
 */
void SliderSFML::draw(sf::RenderWindow &window)
{
	logic(window);
	sf::Text minValueText = returnText(xCord - 10, yCord + 5, std::to_string(minValue), 20);
	minValueText.setFillColor(sf::Color::White);
	minValueText.setOutlineColor(sf::Color::Black);
	minValueText.setOutlineThickness(1);

	sf::Text maxValueText = returnText(xCord + axisWidth - 10, yCord + 5, std::to_string(maxValue), 20);
	maxValueText.setFillColor(sf::Color::White);
	maxValueText.setOutlineColor(sf::Color::Black);
	maxValueText.setOutlineThickness(1);

	window.draw(minValueText);
	window.draw(axis);
	window.draw(maxValueText);
	window.draw(slider);

	sf::Text sliderValueText = returnText(slider.getPosition().x - sliderWidth, slider.getPosition().y - sliderHeight, std::to_string((int)sliderValue), 15);
	sliderValueText.setFillColor(sf::Color::White);
	sliderValueText.setOutlineColor(sf::Color::Black);
	sliderValueText.setOutlineThickness(1);

	window.draw(sliderValueText);
}
