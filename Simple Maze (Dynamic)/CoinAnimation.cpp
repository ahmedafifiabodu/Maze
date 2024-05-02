#include "CoinAnimation.h"

void CoinAnimation::advance()
{
	if (++iFrameCoin >= nFramesCoin)
		iFrameCoin = 0;
}

CoinAnimation::CoinAnimation(int x, int y, int width, int height)
{
	if (!coinTexture.loadFromFile("./Asset/Coin/MonedaD.png")) {
		//handle error
	}
	for (int i = 0; i < nFramesCoin; i++)
		framesCoin[i] = { x + i * width, y,  width,  height };
}

void CoinAnimation::applyToSpriteCoin(sf::Sprite& s) const
{
	s.setTexture(coinTexture);
	s.setTextureRect(framesCoin[iFrameCoin]);
}

void CoinAnimation::updateAnimation(float dt)
{
	time += dt;

	while (time >= holdTime)
	{
		time -= holdTime;
		advance();
	}
}