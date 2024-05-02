#include "Player.h"

Player::Player(int x, int y) : x(x), y(y), position(x* tileSize, y* tileSize)
{
	constexpr int tileSizes = 120;
	constexpr int animationDelay = 125;

	constexpr int WalkingDownIndex = int(AnimationMovementIndex::WalkingDown);
	constexpr int WalkingUpIndex = int(AnimationMovementIndex::WalkingUp);
	constexpr int WalkingLeftIndex = int(AnimationMovementIndex::WalkingLeft);
	constexpr int WalkingRightIndex = int(AnimationMovementIndex::WalkingRight);

	animationsMovement[WalkingDownIndex] = PlayerAnimation(animationDelay, 780 /* 105 * 7 */, tileSizes, tileSizes);
	animationsMovement[WalkingUpIndex] = PlayerAnimation(animationDelay, 525 /* 105 * 5 */, tileSizes, tileSizes);
	animationsMovement[WalkingLeftIndex] = PlayerAnimation(animationDelay, 660 /* 105 * 6 */, tileSizes, tileSizes);
	animationsMovement[WalkingRightIndex] = PlayerAnimation(animationDelay, 920 /* 105 * 8 */, tileSizes, tileSizes);

	constexpr int IdealFrontIndex = int(AnimationIdealIndex::IdealFront);
	constexpr int IdealBackIndex = int(AnimationIdealIndex::IdealBack);
	constexpr int IdealLeftIndex = int(AnimationIdealIndex::IdealLeft);
	constexpr int IdealRightIndex = int(AnimationIdealIndex::IdealRight);

	animationsIdeal[IdealFrontIndex] = PlayerAnimation(animationDelay, 10, tileSizes, tileSizes);
	animationsIdeal[IdealBackIndex] = PlayerAnimation(animationDelay, 10, tileSizes, tileSizes);
	animationsIdeal[IdealLeftIndex] = PlayerAnimation(animationDelay, 140 /* 105 * 2 */, tileSizes, tileSizes);
	animationsIdeal[IdealRightIndex] = PlayerAnimation(animationDelay, 400 /* 105 * 4 */, tileSizes, tileSizes);

	sprite.setTextureRect({ 5, 15, tileSizes, tileSizes });
	sprite.setPosition(x * tileSize, y * tileSize);
	sprite.setScale(scale_factor_x, scale_factor_y);
}

void Player::drawing(sf::RenderTarget& rt) const
{
	rt.draw(sprite);
}

void Player::showMessage(sf::RenderTarget& window)
{
	sf::Font font;
	if (!font.loadFromFile("./Asset/Font/ariali.ttf")) {
		std::cerr << "Error loading font" << std::endl;
		return;
	}

	window.clear(sf::Color::Black);

	sf::Text text("Congratulations! You reached the end!", font);

	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setPosition(window.getSize().x / 5.f, window.getSize().y / 2.f);
	window.draw(text);
}

void Player::move(const sf::Vector2f& direction, sf::RenderWindow& window, std::vector<std::vector<Cell>>& maze)
{
	int dx = direction.x;
	int dy = direction.y;

	constexpr int GRID_WIN = 3;

	if (isWithinBounds(x + dx, y + dy) && isWalkableTile(maze[y + dy][x + dx].type))
	{
		if (maze[y + dy][x + dx].type == GRID_WIN)
		{
			std::cout << "You Won !!!" << std::endl;
			hasWon = true;
			sleep(sf::seconds(1));
			//showMessage(window);
			//window.close();
		}

		x += dx;
		y += dy;

		velocity = { direction.x * tileSize, direction.y * tileSize };
		sprite.setPosition(x * tileSize, y * tileSize);

		updateCurrentAnimation(direction);
	}
}

void Player::updateCurrentAnimation(const sf::Vector2f& direction)
{
	if (direction.x > 0.0f)
		currentAnimationMovement = AnimationMovementIndex::WalkingRight;
	else if (direction.x < 0.0f)
		currentAnimationMovement = AnimationMovementIndex::WalkingLeft;
	else if (direction.y > 0.0f)
		currentAnimationMovement = AnimationMovementIndex::WalkingUp;
	else if (direction.y < 0.0f)
		currentAnimationMovement = AnimationMovementIndex::WalkingDown;
}

void Player::update(float dt, bool isIdeal)
{
	position += velocity * dt;

	if (isIdeal == false)
	{
		animationsMovement[static_cast<int>(currentAnimationMovement)].updateAnimation(dt);
		animationsMovement[static_cast<int>(currentAnimationMovement)].applyToSpritePlayer(sprite, false);
		currentAnimationIdeal = AnimationIdealIndex::IdealFront;
	}
	else
	{
		animationsIdeal[static_cast<int>(currentAnimationIdeal)].updateAnimation(dt);
		animationsIdeal[static_cast<int>(currentAnimationIdeal)].applyToSpritePlayer(sprite, true);
	}
}

void Player::stopIdealAnimation()
{
	if (velocity.x > 0.0f)
		currentAnimationIdeal = AnimationIdealIndex::IdealRight;
	else if (velocity.x < 0.0f)
		currentAnimationIdeal = AnimationIdealIndex::IdealLeft;
	else if (velocity.y > 0.0f)
		currentAnimationIdeal = AnimationIdealIndex::IdealBack;
	else if (velocity.y < 0.0f)
		currentAnimationIdeal = AnimationIdealIndex::IdealFront;
}

bool Player::isWithinBounds(int x, int y)
{
	return x >= 0 && x < cols && y >= 0 && y < rows;
}

bool Player::isWalkableTile(int tileType)
{
	return tileType == GRID_WIN || tileType == GRID_Move || tileType == GRID_Move2 || tileType == GRID_Move3;
}