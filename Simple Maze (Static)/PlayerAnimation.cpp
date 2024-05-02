#include "PlayerAnimation.h"

void PlayerAnimation::advance()
{
	if (++iFrameMovement >= nFramesMovement)
		iFrameMovement = 0;

	if (++iFrameIdeal >= nFramesIdeal)
		iFrameIdeal = 0;
}

PlayerAnimation::PlayerAnimation(int x, int y, int width, int height) : time(0.0f), iFrameMovement(0), iFrameIdeal(0)
{
	if (!playerTexture.loadFromFile("./Asset/Character/Main Character.png")) {
		// handle error
	}

	for (int i = 0; i < nFramesMovement; ++i)
		framesMovement[i] = { x + i * width, y, width, height };

	for (int i = 0; i < nFramesIdeal; ++i)
		framesIdeal[i] = { x + i * width, y, width, height };
}

void PlayerAnimation::applyToSpritePlayer(sf::Sprite& s, bool isIdeal) const
{
	s.setTexture(playerTexture);

	if (isIdeal)
		s.setTextureRect(framesIdeal[iFrameIdeal]);  // Use framesIdeal for ideal animation
	else
		s.setTextureRect(framesMovement[iFrameMovement]);  // Use framesMovement for movement animation
}

void PlayerAnimation::updateAnimation(float dt)
{
	time += dt;

	while (time >= holdTime)
	{
		time -= holdTime;
		advance();
	}
}