#pragma once
#include <SFML/Graphics.hpp>

class CoinAnimation

{
	float time = 0.0f;
	static constexpr float holdTime = 0.1f;

	static constexpr int nFramesCoin = 5;
	sf::IntRect framesCoin[nFramesCoin];
	int iFrameCoin = 0;

	sf::Texture coinTexture;

public:

	CoinAnimation() = default;
	CoinAnimation(int x, int y, int width, int height);
	void advance();
	void applyToSpriteCoin(sf::Sprite& s)const;
	void updateAnimation(float dt);
};
