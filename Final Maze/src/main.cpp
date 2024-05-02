#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int mazeSize = 20;  // Adjust the maze size as needed
const int tileSize = 30;  // Adjust the tile size as needed

class Maze {
public:
	Maze() {
		// Generate a random maze
		maze.resize(mazeSize, std::vector<int>(mazeSize, 0));
		for (int i = 0; i < mazeSize * mazeSize / 3; ++i) {
			int x = rand() % mazeSize;
			int y = rand() % mazeSize;
			maze[x][y] = 1;
		}
	}

	bool isMoveValid(int x, int y) const {
		// Check if the move is within bounds and not blocked by a wall
		return x >= 0 && x < mazeSize && y >= 0 && y < mazeSize && maze[x][y] == 0;
	}

	void draws(sf::RenderWindow& window) const {
		// Draw the maze
		for (int i = 0; i < mazeSize; ++i) {
			for (int j = 0; j < mazeSize; ++j) {
				sf::RectangleShape cell(sf::Vector2f(tileSize, tileSize));
				cell.setPosition(i * tileSize, j * tileSize);
				cell.setOutlineThickness(1);
				cell.setOutlineColor(sf::Color::Black);
				cell.setFillColor(maze[i][j] == 1 ? sf::Color::Black : sf::Color::White);
				window.draw(cell);
			}
		}
	}

private:
	std::vector<std::vector<int>> maze;
};

class Player {
public:
	Player(int startX, int startY) : x(startX), y(startY) {}

	void move(int dx, int dy) {
		x += dx;
		y += dy;
	}

	sf::Vector2i getPosition() const {
		return sf::Vector2i(x, y);
	}

	void draws(sf::RenderWindow& window) const {
		// Draw the player
		sf::CircleShape playerShape(15);
		playerShape.setFillColor(sf::Color::Green);
		playerShape.setPosition(x * tileSize, y * tileSize);
		window.draw(playerShape);
	}

private:
	int x;
	int y;
};

int main() {
	srand(static_cast<unsigned>(time(nullptr)));

	sf::RenderWindow window(sf::VideoMode(mazeSize * tileSize, mazeSize * tileSize), "SFML Maze");

	Maze maze;
	Player player(0, 0);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				int dx = 0, dy = 0;
				if (event.key.code == sf::Keyboard::Up && maze.isMoveValid(player.getPosition().x, player.getPosition().y - 1))
					dy = -1;
				else if (event.key.code == sf::Keyboard::Down && maze.isMoveValid(player.getPosition().x, player.getPosition().y + 1))
					dy = 1;
				else if (event.key.code == sf::Keyboard::Left && maze.isMoveValid(player.getPosition().x - 1, player.getPosition().y))
					dx = -1;
				else if (event.key.code == sf::Keyboard::Right && maze.isMoveValid(player.getPosition().x + 1, player.getPosition().y))
					dx = 1;

				player.move(dx, dy);
			}
		}

		window.clear();
		maze.draws(window);
		player.draws(window);
		window.display();
	}

	return 0;
}