#include "Player.h"

Player::Player(int x, int y) : x(x), y(y), position(x* tileSize, y* tileSize)
{
	constexpr int WalkingDownIndex = int(AnimationMovementIndex::WalkingDown);
	constexpr int WalkingUpIndex = int(AnimationMovementIndex::WalkingUp);
	constexpr int WalkingLeftIndex = int(AnimationMovementIndex::WalkingLeft);
	constexpr int WalkingRightIndex = int(AnimationMovementIndex::WalkingRight);

	animationsMovement[WalkingDownIndex] = PlayerAnimation(125, 780 /* 105 * 7 */, 120, 120);
	animationsMovement[WalkingUpIndex] = PlayerAnimation(125, 525 /* 105 * 5 */, 120, 120);
	animationsMovement[WalkingLeftIndex] = PlayerAnimation(125, 660 /* 105 * 6 */, 120, 120);
	animationsMovement[WalkingRightIndex] = PlayerAnimation(125, 920 /* 105 * 8 */, 120, 120);

	constexpr int IdealFrontIndex = int(AnimationIdealIndex::IdealFront);
	constexpr int IdealBackIndex = int(AnimationIdealIndex::IdealBack);
	constexpr int IdealLeftIndex = int(AnimationIdealIndex::IdealLeft);
	constexpr int IdealRightIndex = int(AnimationIdealIndex::IdealRight);

	animationsIdeal[IdealFrontIndex] = PlayerAnimation(125, 10, 120, 120);
	animationsIdeal[IdealBackIndex] = PlayerAnimation(125, 10, 120, 120);
	animationsIdeal[IdealLeftIndex] = PlayerAnimation(125, 140 /* 105 * 2 */, 120, 120);
	animationsIdeal[IdealRightIndex] = PlayerAnimation(125, 400 /* 105 * 4 */, 120, 120);

	sprite.setTextureRect({ 5, 15, 120, 120 });
	sprite.setPosition(x * tileSize, y * tileSize);
	sprite.setScale(scale_factor_x, scale_factor_y);

	//shape.setRadius(15);
	//shape.setFillColor(sf::Color::Red);
	//shape.setPosition(x * tileSize, y * tileSize);
}

void Player::draw(sf::RenderTarget& rt) const
{
	rt.draw(sprite);
}

void Player::move(const sf::Vector2f& direction, sf::RenderWindow& window) {
	int dx = direction.x;
	int dy = direction.y;

	if (x + dx >= 0 && x + dx < cols && y + dy >= 0 && y + dy < rows) {
		if (grid[y + dy][x + dx] == 2) {
			std::cout << "You Won !!!" << std::endl;
			window.close();
		}

		else if (grid[y + dy][x + dx] == 0 || grid[y + dy][x + dx] == 2) {
			x += dx;
			y += dy;

			velocity = { direction.x * tileSize, direction.y * tileSize };
			sprite.setPosition(x * tileSize, y * tileSize);

			if (direction.x > 0.0f)
				currentAnimationMovement = AnimationMovementIndex::WalkingRight;

			else if (direction.x < 0.0f)
				currentAnimationMovement = AnimationMovementIndex::WalkingLeft;

			else if (direction.y > 0.0f)
				currentAnimationMovement = AnimationMovementIndex::WalkingUp;

			else if (direction.y < 0.0f)
				currentAnimationMovement = AnimationMovementIndex::WalkingDown;
		}
	}
}

void Player::update(float dt, bool isIdeal)
{
	position += velocity * dt;

	if (isIdeal == false) {
		// Player is moving
		animationsMovement[int(currentAnimationMovement)].updateAnimation(dt);
		animationsMovement[int(currentAnimationMovement)].applyToSpritePlayer(sprite, false);

		// Reset the ideal animation index when moving
		currentAnimationIdeal = AnimationIdealIndex::IdealFront;
	}
	else {
		// Player is not moving
		animationsIdeal[int(currentAnimationIdeal)].updateAnimation(dt);
		animationsIdeal[int(currentAnimationIdeal)].applyToSpritePlayer(sprite, true);
	}
}

void Player::stopIdealAnimation()
{
	// Set the appropriate ideal animation based on the last movement direction
	if (velocity.x > 0.0f)
		currentAnimationIdeal = AnimationIdealIndex::IdealRight;
	else if (velocity.x < 0.0f)
		currentAnimationIdeal = AnimationIdealIndex::IdealLeft;
	else if (velocity.y > 0.0f)
		currentAnimationIdeal = AnimationIdealIndex::IdealBack;
	else if (velocity.y < 0.0f)
		currentAnimationIdeal = AnimationIdealIndex::IdealFront;
}