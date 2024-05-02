#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int rows = 10;
const int cols = 10;
const int cellSize = 30;

enum CellType {
    PATH = 0,
    WALL = 1,
    START = 2,
    END = 3
};

struct Cell {
    CellType type;
    sf::RectangleShape* shape;
};

void generateMaze(std::vector<std::vector<Cell>>& maze) {
    // Initialize the maze with walls
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maze[i][j].type = WALL;
            maze[i][j].shape = new sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
            maze[i][j].shape->setPosition(j * cellSize, i * cellSize);
        }
    }

    // Set start and end points
    int startRow = 0;
    int startCol = 0;
    int endRow = rows - 1;
    int endCol = cols - 1;

    maze[startRow][startCol].type = START;
    maze[endRow][endCol].type = END;

    // Generate a random path
    srand(time(nullptr));

    int currentRow = startRow;
    int currentCol = startCol;

    while (currentRow != endRow || currentCol != endCol) {
        maze[currentRow][currentCol].type = PATH;

        // Move in a random valid direction (up, down, left, right)
        int direction = rand() % 4;

        if (direction == 0 && currentRow > 0 && maze[currentRow - 1][currentCol].type == WALL) {
            currentRow--;  // Move up
        }
        else if (direction == 1 && currentRow < rows - 1 && maze[currentRow + 1][currentCol].type == WALL) {
            currentRow++;  // Move down
        }
        else if (direction == 2 && currentCol > 0 && maze[currentRow][currentCol - 1].type == WALL) {
            currentCol--;  // Move left
        }
        else if (direction == 3 && currentCol < cols - 1 && maze[currentRow][currentCol + 1].type == WALL) {
            currentCol++;  // Move right
        }
    }
}

void drawMaze(sf::RenderWindow& window, const std::vector<std::vector<Cell>>& maze) {
    // Draw maze
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            switch (maze[i][j].type) {
            case WALL:
                maze[i][j].shape->setFillColor(sf::Color::Black);
                break;
            case START:
                maze[i][j].shape->setFillColor(sf::Color::Green);
                break;
            case END:
                maze[i][j].shape->setFillColor(sf::Color::Red);
                break;
            case PATH:
                maze[i][j].shape->setFillColor(sf::Color::White);
                break;
            }
            window.draw(*maze[i][j].shape);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize), "Maze Generator");

    std::vector<std::vector<Cell>> maze(rows, std::vector<Cell>(cols));

    generateMaze(maze);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        drawMaze(window, maze);

        window.display();
    }

    return 0;
}
