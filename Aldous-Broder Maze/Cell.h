#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Cell {
public:
	int row, col;
	bool visited;
	std::vector<Cell*> neighbors;

	Cell(int r, int c) : row(r), col(c), visited(false) {}

	void draw(sf::RenderWindow& window, float cellSize) const {
		sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
		rect.setPosition(col * cellSize, row * cellSize);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(1);

		if (visited) {
			rect.setFillColor(sf::Color::White);
		}
		else {
			rect.setFillColor(sf::Color::Black);
		}

		window.draw(rect);
	}
};