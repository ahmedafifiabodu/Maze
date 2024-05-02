#pragma once
#include <SFML/Graphics.hpp>
#include "CellDimensions.h"
#include "CoinAnimation.h"

class Coin
{
	enum class AnimationCoinIndex
	{
		Front,				//0
		SemiHalfFront,		//1
		Half,				//2
		SemiHalfBack,		//3
		Back,				//4
		Count				//5
	};

	int x, y;

	CoinAnimation animationsCoin[int(AnimationCoinIndex::Count)];
	AnimationCoinIndex currentAnimationIdeal = AnimationCoinIndex::Front;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	Coin(int x, int y);

	void update(float dt);

	void draw(sf::RenderTarget& rt) const;
};
