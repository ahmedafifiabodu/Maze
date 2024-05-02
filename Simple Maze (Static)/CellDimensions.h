#pragma once

#include <array>

constexpr int rows = 11;
constexpr int cols = 27;
constexpr int tileSize = 30;

constexpr std::array<std::array<int, cols>, rows> grid = { {
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1}
} };

//class CoinAnimation
//{
//	float time = 0.0f;
//	static constexpr float holdTime = 0.1f;
//
//	static constexpr int nFramesCoin = 4;
//	sf::IntRect framesCoin[nFramesCoin];
//	int iFrameCoin = 0;
//
//	sf::Texture coinTexture;
//
//public:
//	void advance()
//	{
//		if (++iFrameCoin >= nFramesCoin)
//			iFrameCoin = 0;
//	}
//
//	CoinAnimation() = default;
//
//	CoinAnimation(int x, int y, int width, int height)
//	{
//		if (!coinTexture.loadFromFile("./Asset/Coin/Coin (Resize).png")) {
//			 //handle error
//		}
//		std::cout << "Here";
//		for (int i = 0; i < nFramesCoin; i++)
//			framesCoin[i] = { x + i * width, y,  width,  height };
//	}
//
//	void applyToSpriteCoin(sf::Sprite& s)const
//	{
//		s.setTexture(coinTexture);
//		s.setTextureRect(framesCoin[iFrameCoin]);
//	}
//
//	void updateAnimation(float dt)
//	{
//		time += dt;
//
//		while (time >= holdTime)
//		{
//			time -= holdTime;
//			advance();
//		}
//	}
//};
//
//class Coin
//{
//	enum class AnimationCoinIndex
//	{
//		Front,				//0
//		SemiHalfFront,		//1
//		AboutHalfFront,		//2
//		Half,				//3
//		SemiHalfBack,		//4
//		AboutHalfBack,		//5
//		Count				//6
//	};
//
//	int x, y;
//
//	CoinAnimation animationsCoin[int(AnimationCoinIndex::Count)];
//	AnimationCoinIndex currentAnimationIdeal = AnimationCoinIndex::Front;
//
//	sf::Texture texture;
//	sf::Sprite sprite;
//
//public:
//	Coin(int x, int y) : x(x), y(y)
//	{
//		animationsCoin[int(AnimationCoinIndex::Front)] = CoinAnimation(0, 0, 400, 400);
//		animationsCoin[int(AnimationCoinIndex::SemiHalfFront)] = CoinAnimation(400, 0, 400, 400);
//		animationsCoin[int(AnimationCoinIndex::AboutHalfFront)] = CoinAnimation(800, 0, 400, 400);
//		animationsCoin[int(AnimationCoinIndex::Half)] = CoinAnimation(400, 400, 400, 400);
//		animationsCoin[int(AnimationCoinIndex::SemiHalfBack)] = CoinAnimation(400, 400, 400, 400);
//		animationsCoin[int(AnimationCoinIndex::AboutHalfBack)] = CoinAnimation(800, 400, 400, 400);
//
//		sprite.setTextureRect({ 0, 0, 400, 400 });
//		sprite.setPosition(x * tileSize, y * tileSize);
//		sprite.setScale(0.25f, 0.25f);
//	}
//
//	void update(float dt)
//	{
//		animationsCoin[int(currentAnimationIdeal)].updateAnimation(dt);
//		animationsCoin[int(currentAnimationIdeal)].applyToSpriteCoin(sprite);
//	}
//
//	void draw(sf::RenderTarget& rt) const
//	{
//		rt.draw(sprite);
//	}
//};
