#pragma once
#include <vector>
#include "Cell.h"
#include <ctime>

class AldousBroder {
public:
	static void on(std::vector<std::vector<Cell>>& grid, float cellSize) {
		std::srand(std::time(0));

		sf::RenderWindow window(sf::VideoMode(grid[0].size() * cellSize, grid.size() * cellSize), "Aldous-Broder Maze");
		window.setFramerateLimit(60);

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			window.clear();

			if (!gridEmpty(grid)) {
				Cell& startCell = getRandomUnvisitedNeighbor(grid[rand() % grid.size()][rand() % grid[0].size()], grid);
				startCell.visited = true;
				int unvisited = grid.size() * grid[0].size() - 1;

				while (unvisited > 0) {
					Cell& currentCell = getRandomUnvisitedNeighbor(startCell, grid);
					currentCell.visited = true;
					unvisited--;

					// Draw the cells and paths in each iteration
					for (const auto& row : grid) {
						for (const auto& cell : row) {
							cell.draw(window, cellSize);
							for (const auto& neighbor : cell.neighbors) {
								if (neighbor != nullptr && cell.visited && neighbor->visited) {
									drawPath(cell, *neighbor, window, cellSize);
								}
							}
						}
					}

					window.display();
				}
			}
		}
	}

private:
	static void drawPath(const Cell& cell1, const Cell& cell2, sf::RenderWindow& window, float cellSize) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f((cell1.col + 0.5) * cellSize, (cell1.row + 0.5) * cellSize)),
			sf::Vertex(sf::Vector2f((cell2.col + 0.5) * cellSize, (cell2.row + 0.5) * cellSize))
		};

		line[0].color = sf::Color::Red;
		line[1].color = sf::Color::Red;

		window.draw(line, 2, sf::Lines);
	}

	static bool gridEmpty(const std::vector<std::vector<Cell>>& grid) {
		for (const auto& row : grid) {
			for (const auto& cell : row) {
				if (!cell.visited) {
					return false;
				}
			}
		}
		return true;
	}

	static Cell& getRandomUnvisitedNeighbor(const Cell& cell, std::vector<std::vector<Cell>>& grid) {
		auto& neighbors = const_cast<std::vector<Cell*>&>(cell.neighbors);
		Cell* neighbor = nullptr;

		while (neighbors.empty()) {
			int direction = rand() % 4;

			if (direction == 0 && cell.row > 0) {
				neighbor = &grid[cell.row - 1][cell.col];
			}
			else if (direction == 1 && cell.row < grid.size() - 1) {
				neighbor = &grid[cell.row + 1][cell.col];
			}
			else if (direction == 2 && cell.col > 0) {
				neighbor = &grid[cell.row][cell.col - 1];
			}
			else if (direction == 3 && cell.col < grid[0].size() - 1) {
				neighbor = &grid[cell.row][cell.col + 1];
			}

			if (neighbor != nullptr && !neighbor->visited) {
				neighbors.push_back(neighbor);
			}
		}

		return *neighbors[rand() % neighbors.size()];
	}
};