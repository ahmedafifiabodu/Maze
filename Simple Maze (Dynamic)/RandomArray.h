#pragma once

#include "CellDimensions.h"
#include <SFML/Graphics.hpp>

class RandomArray
{
public:
	void generateMaze(std::vector<std::vector<Cell>>& maze);
};
