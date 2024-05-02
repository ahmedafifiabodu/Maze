#ifndef PLAYER_ANIMATION_H
#define PLAYER_ANIMATION_H
#include <SFML/Graphics.hpp>

class PlayerAnimation
{
	static constexpr float holdTime = 0.1f;
	static constexpr int nFramesMovement = 9;
	static constexpr int nFramesIdeal = 2;

	sf::Texture playerTexture;

	sf::IntRect framesMovement[nFramesMovement];
	sf::IntRect framesIdeal[nFramesIdeal];

	float time = 0.0f;
	int iFrameMovement = 0;
	int iFrameIdeal = 0;

	void advance();

public:
	PlayerAnimation() = default;
	PlayerAnimation(int x, int y, int width, int height);

	void applyToSpritePlayer(sf::Sprite& s, bool isIdeal) const;
	void updateAnimation(float dt);
};

#endif // PLAYER_ANIMATION_H