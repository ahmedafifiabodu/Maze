#pragma once
#include <SFML/Graphics.hpp>
#include "CellDimensions.h"

class DrawGrid
{
	std::vector<sf::Texture> textures;
public:
	DrawGrid();
	void draw(sf::RenderWindow& window);
};
