#include "RandomArray.h"

//bool isValid(int x, int y) {
//	return x >= 0 && x < rows && y >= 0 && y < cols;
//}
//
//void generateMazes(std::vector<std::vector<Cell>>& maze, int x, int y) {
//	const int directions[4][2] = { {0, 2}, {2, 0}, {0, -2}, {-2, 0} };
//
//	maze[x][y].type = OBSTACLE;
//
//	for (int i = 0; i < 4; ++i) {
//		int nx = x + directions[i][0];
//		int ny = y + directions[i][1];
//
//		if (isValid(nx, ny) && maze[nx][ny].type == EMPTY) {
//			int mx = x + directions[i][0] / 2;
//			int my = y + directions[i][1] / 2;
//
//			maze[mx][my].type = OBSTACLE;
//
//			generateMazes(maze, nx, ny);
//		}
//	}
//}

void RandomArray::generateMaze(std::vector<std::vector<Cell>>& maze) {
	// Initialize the maze with empty cells
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			maze[i][j].type = EMPTY;
			maze[i][j].shape.setSize(sf::Vector2f(tileSize, tileSize));
			maze[i][j].shape.setPosition(j * tileSize, i * tileSize);
		}
	}

	// Generate obstacles on the border
	for (int i = 0; i < rows; ++i) {
		maze[i][0].type = OBSTACLE;         // Left border
		maze[i][cols - 1].type = OBSTACLE;  // Right border
	}

	for (int j = 0; j < cols; ++j) {
		maze[0][j].type = OBSTACLE;         // Top border
		maze[rows - 1][j].type = OBSTACLE;  // Bottom border
	}

	// Set start and end points
	int startRow = 0;
	int startCol = 1;
	int endRow = rows - 2;
	int endCol = cols - 2;

	maze[startRow][startCol].type = START;

	// Generate additional random obstacles and '1's
	srand(time(nullptr));
	for (int i = 0; i < rows * cols / 4; ++i) {
		int obstacleRow = rand() % (rows - 2) + 1; // Avoid placing obstacles on the borders
		int obstacleCol = rand() % (cols - 2) + 1;
		maze[obstacleRow][obstacleCol].type = OBSTACLE;
	}

	// Generate random '1's
	for (int i = 0; i < rows * cols / 4; ++i) {
		int oneRow = rand() % (rows - 2) + 1; // Avoid placing '1's on the borders
		int oneCol = rand() % (cols - 2) + 1;
		maze[oneRow][oneCol].type = OBSTACLE;
	}

	// Generate random '1's
	for (int i = 0; i < rows * cols / 4; ++i) {
		int oneRow = rand() % (rows - 2) + 1; // Avoid placing '1's on the borders
		int oneCol = rand() % (cols - 2) + 1;
		maze[oneRow][oneCol].type = OBSTACLE;
	}
	/*generateMazes(maze, startRow, startCol);*/

	maze[endRow][endCol].type = END;

	// Generate a random path from start to end
	int currentRow = startRow + 1;
	int currentCol = startCol;

	while (currentRow != endRow || currentCol != endCol)
	{
		maze[currentRow][currentCol].type = EMPTY;

		// Move toward the end (randomly choosing between horizontal and vertical movement)

		if (currentRow < endRow && rand() % 2 == 0) {
			currentRow++;
		}
		else if (currentCol < endCol) {
			currentCol++;
		}

		else {
			currentCol--;
		}
	}
}