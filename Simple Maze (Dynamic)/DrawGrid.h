#pragma once
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include "CellDimensions.h"

class DrawGrid
{
	sf::Texture textureGrass;
	sf::Texture textureStone;
	sf::Texture textureWin;
	sf::Texture texturePath;

	std::unordered_map<CellType, sf::Texture*> textureMap;

public:
	DrawGrid();
	void draw(sf::RenderWindow& window, std::vector<std::vector<Cell>>& maze);
};
