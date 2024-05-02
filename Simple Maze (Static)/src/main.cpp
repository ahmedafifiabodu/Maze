#include <SFML/Graphics.hpp>
#include "../CellDimensions.h"
#include "../Player.h"
#include "../DrawGrid.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "Maze !!");

	Player player(1, 0);
	//Coin coin(5, 5);

	DrawGrid drawGrid;

	sf::Clock clock;

	bool isIdeal = true;

	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		player.update(dt, isIdeal);
		//coin.update(dt);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				sf::Vector2f direction = { 0.f, 0.f };

				switch (event.key.code) {
				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					direction.y = -1;
					break;

				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					direction.y = 1;
					break;

				case sf::Keyboard::Left:
				case sf::Keyboard::A:
					direction.x = -1;
					break;

				case sf::Keyboard::Right:
				case sf::Keyboard::D:
					direction.x = 1;
					break;
				}

				player.move(direction, window);
				isIdeal = false;
			}
			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					break;

				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					break;

				case sf::Keyboard::Left:
				case sf::Keyboard::A:
					break;

				case sf::Keyboard::Right:
				case sf::Keyboard::D:
					break;
				}

				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					isIdeal = true;
					player.stopIdealAnimation();
				}
			}
		}

		window.clear();
		drawGrid.draw(window);
		player.draw(window);
		//coin.draw(window);
		window.display();
	}

	return 0;
}