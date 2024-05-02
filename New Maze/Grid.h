#pragma once
#include <vector>
#include "Cell.h"
#include <functional>
#include <SFML\Graphics.hpp>

class Grid {
public:
	int rows, columns;
	std::vector<std::vector<Cell>> grid;

	Grid(int rows, int columns) : rows(rows), columns(columns) {
		grid = prepareGrid();
		configureCells();
	}

	std::vector<std::vector<Cell>> prepareGrid() const {
		std::vector<std::vector<Cell>> result(rows, std::vector<Cell>(columns, Cell(-1, -1)));
		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < columns; ++col) {
				result[row][col] = Cell(row, col);
			}
		}
		return result;
	}

	void configureCells() {
		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < columns; ++col) {
				Cell& cell = grid[row][col];
				cell.north = getCell(row - 1, col);
				cell.south = getCell(row + 1, col);
				cell.west = getCell(row, col - 1);
				cell.east = getCell(row, col + 1);
			}
		}
	}

	Cell* getCell(int row, int col) {
		if (row < 0 || row >= rows || col < 0 || col >= columns) {
			return nullptr;
		}
		return &grid[row][col];
	}

	Cell* randomCell() {
		int randomRow = rand() % rows;
		int randomCol = rand() % columns;
		return getCell(randomRow, randomCol);
	}

	int size() const {
		return rows * columns;
	}

	void eachRow(std::function<void(std::vector<Cell>&)> callback) {
		for (auto& row : grid) {
			callback(row);
		}
	}

	void eachCell(std::function<void(Cell&)> callback) {
		eachRow([&](std::vector<Cell>& row) {
			for (Cell& cell : row) {
				callback(cell);
			}
			});
	}

	// ... (rest of the Grid class remains unchanged)

	sf::Color background_color_for(const Cell& cell) {
		// Example: Color dead-end cells in red
		if (cell.links.size() == 1) {
			return sf::Color::Red;
		}

		// Default color for other cells
		return sf::Color::White;
	}

	void draw(sf::RenderWindow& window, int cellSize) {
		// Implement the SFML drawing logic here
		// ...
		sf::RectangleShape wall(sf::Vector2f(cellSize, 2)); // Horizontal wall
		sf::RectangleShape verticalWall(sf::Vector2f(2, cellSize)); // Vertical wall
		sf::RectangleShape background(sf::Vector2f(cellSize, cellSize)); // Cell background

		wall.setFillColor(sf::Color::Black);
		verticalWall.setFillColor(sf::Color::Black);

		// Draw regular cells and horizontal walls
		for (float row = 0.5; row < rows; ++row) {
			for (float col = 0.5; col < columns; ++col) {
				int x = col * cellSize;
				int y = row * cellSize;

				Cell& cell = grid[row][col];

				// Draw cell background
				background.setPosition(x, y);
				//background.setFillColor(background_color_for(cell)); // Adjust as needed
				/*background.setOutlineColor(sf::Color::Black);
				background.setOutlineThickness(2.f);*/
				window.draw(background);

				// Draw horizontal walls
				if (!cell.linked(cell.south)) {
					wall.setPosition(x, y + cellSize);
					window.draw(wall);
				}
			}
		}

		// Draw vertical walls for the entire row (outside the loop to avoid overlap)
		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < columns; ++col) {
				int x = col * cellSize;
				int y = row * cellSize;

				Cell& cell = grid[row][col];

				// Draw vertical walls
				if (!cell.linked(cell.east)) {
					verticalWall.setPosition(x + cellSize, y);
					window.draw(verticalWall);
				}

				else if (!cell.linked(cell.west)) {
					wall.setPosition(x, y+ cellSize);
					window.draw(wall);
				}
			}
		}
	}
};