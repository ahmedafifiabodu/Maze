#pragma once
#include <SFML/Graphics.hpp>
#include "CellDimensions.h"
#include "PlayerAnimation.h"
#include <iostream>

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

	sf::Texture texture;
	sf::Sprite sprite;

	PlayerAnimation animationsMovement[int(AnimationMovementIndex::Count)];
	AnimationMovementIndex currentAnimationMovement = AnimationMovementIndex::WalkingUp;

	PlayerAnimation animationsIdeal[int(AnimationIdealIndex::Count)];
	AnimationIdealIndex currentAnimationIdeal = AnimationIdealIndex::IdealFront;

	sf::Vector2f position;
	sf::Vector2f velocity = { 0.f, 0.f };

public:
	Player(int x, int y);

	void draw(sf::RenderTarget& rt) const;
	void move(const sf::Vector2f& direction, sf::RenderWindow& window);
	void update(float dt, bool isIdeal);
	void stopIdealAnimation();
};
