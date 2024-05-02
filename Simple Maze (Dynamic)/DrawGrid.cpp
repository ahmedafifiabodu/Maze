#include "DrawGrid.h"

DrawGrid::DrawGrid() {
	const std::string grassTexturePath = "./Asset/Grass/Grass.PNG";
	const std::string stoneTexturePath = "./Asset/Grass/Wall.PNG";
	const std::string winTexturePath = "./Asset/Grass/Start.PNG";
	const std::string pathTexturePath = "./Asset/Grass/End.PNG";

	if (!textureGrass.loadFromFile(grassTexturePath) ||
		!textureStone.loadFromFile(stoneTexturePath) ||
		!textureWin.loadFromFile(winTexturePath) ||
		!texturePath.loadFromFile(pathTexturePath)) {
		// handle error
	}

	textureMap[CellType::EMPTY] = &textureGrass;
	textureMap[CellType::OBSTACLE] = &textureStone;
	textureMap[CellType::START] = &textureWin;
	textureMap[CellType::END] = &textureWin;
	textureMap[CellType::PATH] = &texturePath;
}

void DrawGrid::draw(sf::RenderWindow& window, std::vector<std::vector<Cell>>& maze) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			maze[i][j].shape.setTexture(textureMap[maze[i][j].type]);
			window.draw(maze[i][j].shape);
		}
	}
}