#pragma once
#include <SFML/Graphics.hpp>

constexpr int rows = 30;
constexpr int cols = 30;
constexpr int tileSize = 30;

enum CellType {
	EMPTY,
	OBSTACLE,
	START,
	END,
	PATH
};

static struct Cell {
	CellType type;
	sf::RectangleShape shape;
};
