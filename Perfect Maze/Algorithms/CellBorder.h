#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class CellBorder
{
public:
	virtual std::string SVGPrint(const std::string& color) const = 0;

	virtual void Draw(sf::RenderWindow& window, sf::Color& color) const = 0;
};
