#include <SFML\Graphics.hpp>
#include "../Grid.h"
#include "../BinaryTree.h"
#include <iostream>

int main()
{
	/*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/

	// Example usage:
	 // Example usage:
	const int rows = 20;
	const int columns = 20;

	Grid grid(rows, columns);
	BinaryTree::on(grid);

	// Use the modified grid as needed
	// ...

	// Create an SFML window and draw the grid
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Grid");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::White);
		grid.draw(window, 40); // Adjust cellSize as needed
		window.display();
	}

	return 0;
}