#include "Coin.h"

Coin::Coin(int x, int y)
{
	animationsCoin[int(AnimationCoinIndex::Front)] = CoinAnimation(0, 0, 16, 16);
	animationsCoin[int(AnimationCoinIndex::SemiHalfFront)] = CoinAnimation(0, 32, 16, 16);
	animationsCoin[int(AnimationCoinIndex::Half)] = CoinAnimation(0, 48, 16, 16);
	animationsCoin[int(AnimationCoinIndex::SemiHalfBack)] = CoinAnimation(0, 64, 16, 16);
	animationsCoin[int(AnimationCoinIndex::Back)] = CoinAnimation(0, 80, 16, 16);

	sprite.setTextureRect({ 0, 0, 16, 16 });
	sprite.setPosition(x * tileSize + 3, y * tileSize + 2);
	sprite.setScale(1.7f, 1.7f);
}

void Coin::update(float dt)

{
	animationsCoin[int(currentAnimationIdeal)].updateAnimation(dt);
	animationsCoin[int(currentAnimationIdeal)].applyToSpriteCoin(sprite);
}

void Coin::draw(sf::RenderTarget& rt) const
{
	rt.draw(sprite);
}