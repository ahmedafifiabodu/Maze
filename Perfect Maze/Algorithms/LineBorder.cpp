#include "LineBorder.h"
#include "../src/CellDimension.h"

LineBorder::LineBorder(double x1, double y1, double x2, double y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

LineBorder::LineBorder(std::tuple<double, double, double, double> xy)
{
	std::tie(x1, y1, x2, y2) = xy;
}

std::string LineBorder::SVGPrint(const std::string& color) const
{
	return "<line x1=\"" + std::to_string(x1 * SQUARE_TILE_SIZE) + "\" x2=\"" +
		std::to_string(x2 * SQUARE_TILE_SIZE) + "\" y1=\"" + std::to_string(y1 * SQUARE_TILE_SIZE) +
		"\" y2=\"" + std::to_string(y2 * SQUARE_TILE_SIZE) + "\" stroke=\"" + color +
		"\" stroke-linecap=\"round\" stroke-width=\"3\"/>";
}

void LineBorder::Draw(sf::RenderWindow& window, sf::Color& color) const
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(SQUARE_TILE_SIZE / 2 + x1 * SQUARE_TILE_SIZE, SQUARE_TILE_SIZE / 2 + y1 * SQUARE_TILE_SIZE), color),
		sf::Vertex(sf::Vector2f(SQUARE_TILE_SIZE / 2 + x2 * SQUARE_TILE_SIZE, SQUARE_TILE_SIZE / 2 + y2 * SQUARE_TILE_SIZE), color)
	};

	window.draw(line, 2, sf::Lines);
}