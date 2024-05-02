#include <SFML\Graphics.hpp>
#include <stack>

#include "Coordinate.h"
using namespace std;

//Direction of the start cells
const int cellPathToTheNorth = 0x01;
const int cellPathToTheEast = 0x02;
const int cellPathToTheSouth = 0x04;
const int cellPathToTheWest = 0x08;
const int Cellvisited = 0x10;

// Maze with the same length and wdith of the current screen
const int verticalCells =20;
const int horizontalCells = 20;
int visitedCells = 1;
int currentCell = 0;

// Object Sizes
const int squareTileSize = 26;
const int squareWallSize = 2;
const int squareCellSize = 28;

void drawMaze(sf::RenderWindow& window, vector<vector<int>>& maze_cells)
{
	sf::Color rgba = sf::Color::Black;
	rgba.r = 235;
	rgba.g = 235;
	rgba.b = 235;

	sf::RectangleShape verticalSpace(sf::Vector2f(squareWallSize, squareTileSize + 2));
	verticalSpace.setFillColor(rgba);

	sf::RectangleShape horizontalSpace(sf::Vector2f(squareTileSize + 2, squareWallSize));
	horizontalSpace.setFillColor(rgba);

	sf::RectangleShape verticalWall(sf::Vector2f(squareWallSize, squareTileSize));
	verticalWall.setFillColor(sf::Color::Black);

	sf::RectangleShape horizontalWall(sf::Vector2f(squareTileSize, squareWallSize));
	horizontalWall.setFillColor(sf::Color::Black);

	sf::RectangleShape tile;// (sf::Vector2f(SQUARE_TILE_SIZE, SQUARE_TILE_SIZE));
	tile.setSize(sf::Vector2f(squareTileSize, squareTileSize));
	tile.setPosition(sf::Vector2f(squareWallSize, squareWallSize));
	tile.setFillColor(sf::Color::White);

	int cur = 0;
	for (int i = 0; i < horizontalCells - 1; i++)
	{
		for (int j = 0; j < verticalCells - 1; j++)
		{
			if (maze_cells[i][j] & Cellvisited)
			{
				tile.setPosition(sf::Vector2f(squareWallSize + i * (squareWallSize + squareTileSize),
					squareWallSize + j * (squareWallSize + squareTileSize)));

				window.draw(tile);
			}

			if ((maze_cells[i][j] & cellPathToTheSouth) == 0)
			{
				horizontalWall.setPosition(sf::Vector2f(i * (squareWallSize + squareTileSize), j * (squareWallSize + squareTileSize)));
				window.draw(horizontalWall);
			}
			else
			{
				horizontalSpace.setPosition(sf::Vector2f(i * (squareWallSize + squareTileSize), j * (squareWallSize + squareTileSize)));
				window.draw(horizontalSpace);
			}

			if ((maze_cells[i][j] & cellPathToTheEast) == 0)
			{
				verticalWall.setPosition(sf::Vector2f(i * (squareWallSize + squareTileSize), j * (squareWallSize + squareTileSize)));
				window.draw(verticalWall);
			}
			else
			{
				verticalSpace.setPosition(sf::Vector2f(i * (squareWallSize + squareTileSize), j * (squareWallSize + squareTileSize)));
				window.draw(verticalSpace);
			}
		}
	}
}

auto offset_x(int n, stack<Coordinate> my_stack)
{
	return my_stack.top().x + n;
}

auto offset_y(int n, stack<Coordinate> my_stack)
{
	return my_stack.top().y + n;
}

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(20 * 28, 20 * 28), "SFML works!");

	// Create the maze while set its first position to visited cell
	vector<vector<int>> maze_cells;
	maze_cells.assign(horizontalCells * squareCellSize, vector<int>(verticalCells * squareCellSize, 0));
	maze_cells[0][0] = Cellvisited;

	// Using Depth First Search (DFS) Stack to traverse
	stack<Coordinate> my_stack;

	// Starting from very first cell
	my_stack.push(Coordinate(0, 0));

	while (window.isOpen())
	{
		// We keep visit every single grid and push its all neighbor into the stack.
		if (visitedCells < horizontalCells * verticalCells)
		{
			// Create an array of neighbour cells that were not yet visited (from North, East, South and West).
			vector<int> neighbours;

			// North visited?
			if (my_stack.top().y > 0 && //Check if it in bounds or not
				(maze_cells[offset_x(0, my_stack)][offset_y(-1, my_stack)] & Cellvisited) == 0) // North
			{
				neighbours.push_back(0);
			}

			// East visited?
			if (my_stack.top().x < horizontalCells - 1 && //Check if it in bounds or not
				(maze_cells[offset_x(1, my_stack)][offset_y(0, my_stack)] & Cellvisited) == 0) // East
			{
				neighbours.push_back(1);
			}

			// Sout visited?
			if (my_stack.top().y < verticalCells - 1 &&  //Check if it in bounds or not
				(maze_cells[offset_x(0, my_stack)][offset_y(1, my_stack)] & Cellvisited) == 0) // South
			{
				neighbours.push_back(2);
			}

			// West visited?
			if (my_stack.top().x > 0 && //Check if it in bounds or not
				(maze_cells[offset_x(-1, my_stack)][offset_y(0, my_stack)] & Cellvisited) == 0) // West
			{
				neighbours.push_back(3);
			}

			// If there is ANY!! neighbours left
			if (!neighbours.empty())
			{
				// Choose random cell to set it available
				int next_cell_dir = neighbours[currentCell % neighbours.size()]; //rand() % neighbours.size()];
				currentCell = (currentCell + 1) % neighbours.size();

				// Create a path between the neighbour and the current cell
				switch (next_cell_dir)
				{
				case 0: // North
					maze_cells[offset_x(0, my_stack)][offset_y(-1, my_stack)] |= Cellvisited | cellPathToTheSouth;
					maze_cells[offset_x(0, my_stack)][offset_y(0, my_stack)] |= cellPathToTheNorth;
					my_stack.push(Coordinate(offset_x(0, my_stack), offset_y(-1, my_stack)));
					break;

				case 1: // East
					maze_cells[offset_x(1, my_stack)][offset_y(0, my_stack)] |= Cellvisited | cellPathToTheWest;
					maze_cells[offset_x(0, my_stack)][offset_y(0, my_stack)] |= cellPathToTheEast;
					my_stack.push(Coordinate(offset_x(1, my_stack), offset_y(0, my_stack)));
					break;

				case 2: // South
					maze_cells[offset_x(0, my_stack)][offset_y(1, my_stack)] |= Cellvisited | cellPathToTheNorth;
					maze_cells[offset_x(0, my_stack)][offset_y(0, my_stack)] |= cellPathToTheSouth;
					my_stack.push(Coordinate(offset_x(0, my_stack), offset_y(1, my_stack)));
					break;

				case 3: // West
					maze_cells[offset_x(-1, my_stack)][offset_y(0, my_stack)] |= Cellvisited | cellPathToTheEast;
					maze_cells[offset_x(0, my_stack)][offset_y(0, my_stack)] |= cellPathToTheWest;
					my_stack.push(Coordinate(offset_x(-1, my_stack), offset_y(0, my_stack)));
					break;
				}
				visitedCells++;
			}

			else
			{
				my_stack.pop();
			}
		}

		else
		{

		}

		window.clear();
		//window.draw(shape);
		drawMaze(window, maze_cells);
		window.display();
	}

	return 0;
}