#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CellDimensions.h"
#include "PlayerAnimation.h"

enum class AnimationMovementIndex
{
	WalkingUp,		//0
	WalkingDown,	//1
	WalkingLeft,	//2
	WalkingRight,	//3
	Count			//4
};

enum class AnimationIdealIndex
{
	IdealFront,		//0
	IdealBack,		//1
	IdealLeft,		//2
	IdealRight,		//3
	Count			//4
};

class Player {
	int x, y;

	const float scale_factor_x = 0.3f;
	const float scale_factor_y = 0.25f;

	const int GRID_Move = 0;
	const int GRID_Move2 = 2;
	const int GRID_Move3 = 4;
	const int GRID_NoMove = 1;
	const int GRID_WIN = 3;

	sf::Texture texture;
	sf::Sprite sprite;

	PlayerAnimation animationsMovement[int(AnimationMovementIndex::Count)];
	AnimationMovementIndex currentAnimationMovement = AnimationMovementIndex::WalkingUp;

	PlayerAnimation animationsIdeal[int(AnimationIdealIndex::Count)];
	AnimationIdealIndex currentAnimationIdeal = AnimationIdealIndex::IdealFront;

	sf::Vector2f position;
	sf::Vector2f velocity = { 0.f, 0.f };

	void updateCurrentAnimation(const sf::Vector2f& direction);
	bool isWithinBounds(int x, int y);
	bool isWalkableTile(int tileType);

public:
	bool hasWon = false;
	Player(int x, int y);
	void drawing(sf::RenderTarget& rt) const;
	void move(const sf::Vector2f& direction, sf::RenderWindow& window, std::vector<std::vector<Cell>>& maze);
	void stopIdealAnimation();
	void update(float dt, bool isIdeal);
	void showMessage(sf::RenderTarget& window);
};
