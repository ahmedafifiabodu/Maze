#include "DrawGrid.h"

DrawGrid::DrawGrid()
{
	const std::string grassTexturePath = "./Asset/Grass/HEDGE_1A.PNG";
	const std::string stoneTexturePath = "./Asset/Grass/BRICK_1A.PNG";
	const std::string winTexturePath = "./Asset/Grass/BRICK_6D.PNG";

	sf::Texture textureGrass;
	sf::Texture textureStone;
	sf::Texture textureWin;

	if (!textureGrass.loadFromFile(grassTexturePath) ||
		!textureStone.loadFromFile(stoneTexturePath) ||
		!textureWin.loadFromFile(winTexturePath)) {
		// handle error
	}

	textures.push_back(std::move(textureGrass));
	textures.push_back(std::move(textureStone));
	textures.push_back(std::move(textureWin));
}

void DrawGrid::draw(sf::RenderWindow& window)
{
	// Draw the grid
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
			tile.setPosition(j * tileSize, i * tileSize);

			int textureIndex = grid[i][j];
			if (textureIndex >= 0 && textureIndex < textures.size()) {
				tile.setTexture(&textures[textureIndex]);
			}

			window.draw(tile);
		}
	}
}