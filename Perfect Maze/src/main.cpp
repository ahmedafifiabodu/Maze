#include <SFML\Graphics.hpp>
#include "CellDimension.h"
#include "../Headers/BaseMaze.h"
#include "../Headers/RectangularMaze.h"
#include <iostream>
constexpr auto PI = (22 / 7.f);

void CreateArrow(sf::ConvexShape& shape)
{
	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(15, 10));
	shape.setPoint(2, sf::Vector2f(0, 20));
	shape.setPoint(3, sf::Vector2f(5, 10));
	shape.setOrigin(sf::Vector2f(5, 10));
	shape.setPosition(sf::Vector2f(5, 10));
}

float GetMagnitude(sf::Vector2f vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

void Normalize(sf::Vector2f& vector)
{
	float mag = GetMagnitude(vector);
	if (mag == 0) return;
	vector = (1 / mag) * vector;
}

bool isCollision(const sf::ConvexShape& player, const LineBorder& wall)
{
	sf::FloatRect playerBounds = player.getGlobalBounds();

	sf::Vector2f wallStart(wall.getX1() * SQUARE_TILE_SIZE, wall.getY1() * SQUARE_TILE_SIZE);
	sf::Vector2f wallEnd(wall.getX2() * SQUARE_TILE_SIZE, wall.getY2() * SQUARE_TILE_SIZE);

	sf::FloatRect wallBounds = sf::FloatRect(std::min(wallStart.x, wallEnd.x),
		std::min(wallStart.y, wallEnd.y),
		std::abs(wallEnd.x - wallStart.x),
		std::abs(wallEnd.y - wallStart.y));

	return playerBounds.intersects(wallBounds);
}

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode::VideoMode(HORIZONTAL_CELLS * SQUARE_TILE_SIZE + SQUARE_TILE_SIZE,
		VERTICAL_CELLS * SQUARE_TILE_SIZE + SQUARE_TILE_SIZE), "Maze!");

	sf::CircleShape shape(12);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(window.getSize().x - shape.getRadius() * 2 - 10, window.getSize().y - shape.getRadius() * 2 - 7);

	sf::ConvexShape player(4);
	player.setFillColor(sf::Color::Blue);
	CreateArrow(player);

	//std::string outputprefix = "maze";

	BaseMaze* maze = new RectangularMaze(HORIZONTAL_CELLS, VERTICAL_CELLS);
	SpanningtreeAlgorithmBase* algorithm = new DepthFirstSearch; // DepthFirstSearch

	std::cout << "Initialising graph..." << std::endl;
	maze->InitialiseGraph();

	// Grey
	sf::Color rgba = sf::Color::Cyan;
	sf::Color playerColor = player.getOutlineColor();
	//rgba.r = 235;
	//rgba.g = 235;
	//rgba.b = 235;

	std::cout << "Generating maze..." << std::endl;
	maze->GenerateMaze(algorithm);

	/*sf::Color black = sf::Color::Black;
	maze->Draw(window, black);*/

	//std::cout << "Rendering maze to '" << outputprefix << ".svg'..." << std::endl;
	//maze->PrintMazeSVG(outputprefix);

	sf::Clock clock;
	float time = 0.0;
	float currentTime = 0.0;
	float deltaTime = 0.0;
	double horizontal = 0.0;
	double vertical = 0.0;
	float angle = 0;
	float speed = 100;
	sf::Vector2f direction;
	sf::Vector2f position = player.getPosition();

	while (window.isOpen())
	{
		currentTime = clock.getElapsedTime().asSeconds();
		deltaTime = currentTime - time;
		time = currentTime;

		// Handle key events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			horizontal = -1;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			horizontal = 1;
		}

		else
			horizontal = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			vertical = -1;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			vertical = 1;
		}
		else
			vertical = 0;

		if (horizontal != 0 || vertical != 0)
		{
			direction.x = horizontal;
			direction.y = vertical;

			Normalize(direction);

			angle = atan2(direction.y, direction.x);

			position += deltaTime * speed * direction;

			// Update player position without collisions
			sf::Vector2f newPosition = position + deltaTime * speed * direction;

			// Check for collisions with walls
			bool collision = false;
			for (int i = 0; i < maze->getVerticesNumber(); ++i)
			{
				for (const auto& edge : maze->getEdgesList()[i])
				{
					/*if (isCollision(player, maze->getEdgesList()))
					{
						collision = true;
						speed = 0;
						break;
					}*/
				}
				if (collision)
					break;
			}

			// If no collision, update player position
			if (!collision)
				position = newPosition;
		}
		player.setPosition(position);
		player.setRotation(angle * 180 / PI);

		// Redraw.
		window.clear(sf::Color::Black);

		window.draw(shape);
		maze->Draw(window, rgba);
		window.draw(player);

		window.display();
	}
	return 0;
}