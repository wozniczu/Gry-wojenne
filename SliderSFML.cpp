#include "SliderSFML.h"

SliderSFML::SliderSFML(int x, int y) : text(font)
{
	xCord = x;
	yCord = y;
	axisHeight = 10;
	axisWidth = 200;
	sliderWidth = 20;
	sliderHeight = 30;

	if (!font.openFromFile("fonts/Arial.ttf"))
		std::cout << "Error loading font\n";

	text.setFont(font);
	text.setFillColor(sf::Color::White);

	axis.setPosition({ static_cast<float>(x), static_cast<float>(y) });
    axis.setOrigin({ 0.0f, static_cast<float>(axisHeight) / 2.0f });
	axis.setSize(sf::Vector2f(axisWidth, axisHeight));
	axis.setFillColor(sf::Color(63,63,63));
	slider.setPosition({ static_cast<float>(x), static_cast<float>(y) });
    slider.setOrigin(sf::Vector2f(static_cast<float>(sliderWidth) / 2.0f, static_cast<float>(sliderHeight) / 2.0f));
	slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(sf::Color(192,192,192));
}

sf::Text SliderSFML::returnText(int x, int y, std::string z, int fontSize)
{
	text.setCharacterSize(fontSize);
	text.setPosition({ static_cast<float>(x), static_cast<float>(y) });
	text.setString(z);
	return text;
}

void SliderSFML::create(int min, int max)
{
	sliderValue = min;
	minValue = min;
	maxValue = max;
}

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
		float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);

		// Ograniczenie pozycji do zakresu slidera
		if (mouseX < static_cast<float>(xCord))
			mouseX = static_cast<float>(xCord);
		else if (mouseX > static_cast<float>(xCord + axisWidth))
			mouseX = static_cast<float>(xCord + axisWidth);

		slider.setPosition({ mouseX, static_cast<float>(yCord) });
		sliderValue = (static_cast<float>(minValue) + ((slider.getPosition().x - static_cast<float>(xCord)) /
			static_cast<float>(axisWidth) * static_cast<float>(maxValue - minValue)));
	}
}

float SliderSFML::getSliderValue()
{
	return sliderValue;
}

void SliderSFML::setSliderValue(float newValue)
{
	if (newValue >= minValue && newValue <= maxValue)
	{
		sliderValue = newValue;
		float diff = maxValue - minValue;
		float diff2 = newValue - minValue;
		float zzz = axisWidth / diff;
		float posX = zzz * diff2;
		posX += xCord;
		slider.setPosition({ posX, static_cast<float>(yCord) });
	}
}

void SliderSFML::setSliderPercentValue(float newPercentValue)
{
	if (newPercentValue >= 0 && newPercentValue <= 100)
	{
		sliderValue = newPercentValue / 100 * maxValue;
		slider.setPosition({ xCord + (axisWidth * newPercentValue / 100), static_cast<float>(yCord) });
	}
}

void SliderSFML::draw(sf::RenderWindow &window)
{
	logic(window);
	sf::Text minValueText = returnText(xCord - 10, yCord + 5, std::to_string(minValue), 20);
	minValueText.setFillColor(sf::Color::Black);

	sf::Text maxValueText = returnText(xCord + axisWidth - 10, yCord + 5, std::to_string(maxValue), 20);
	maxValueText.setFillColor(sf::Color::Black);

	window.draw(minValueText);
	window.draw(axis);
	window.draw(maxValueText);
	window.draw(slider);

	sf::Text sliderValueText = returnText(slider.getPosition().x - sliderWidth, slider.getPosition().y - sliderHeight, std::to_string((int)sliderValue), 15);
	sliderValueText.setFillColor(sf::Color::Black);

	window.draw(sliderValueText);
}
