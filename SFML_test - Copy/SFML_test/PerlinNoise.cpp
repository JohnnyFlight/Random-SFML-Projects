#include "PerlinNoise.hpp"

#include "MathsUtility.hpp"
#include "VectorUtility.hpp"

namespace
{
	const unsigned kMaxWidth = 256;
	const unsigned kMaxHeight = 256;
}

PerlinNoise::PerlinNoise()
{

}

PerlinNoise::PerlinNoise(float width, float height, unsigned seed)
{
	_width = width;
	_height = height;

	_seed = seed;
}

float PerlinNoise::getNoise(float x, float y)
{
	//	Limit 0 <= x and y <= width or height
	while (x < 0.0f) x += kMaxWidth;
	while (x >= kMaxWidth) x -= kMaxWidth;
	while (y < 0.0f) y += kMaxHeight;
	while (y >= kMaxHeight) y -= kMaxHeight;

	//	Turn points into a vector
	sf::Vector2f point = sf::Vector2f(x, y);

	//	Get adjacent points
	sf::Vector2f x0y0 = _gradients[(int)x][(int)y];
	sf::Vector2f x0y1 = _gradients[(int)x][(int)y + 1];
	sf::Vector2f x1y0 = _gradients[(int)x + 1][(int)y];
	sf::Vector2f x1y1 = _gradients[(int)x + 1][(int)y + 1];
	
	float s = VectorUtility::dot(x0y0, point - sf::Vector2f((int)x, (int)y));
	float t = VectorUtility::dot(x1y0, point - sf::Vector2f((int)x + 1, (int)y));
	float u = VectorUtility::dot(x0y1, point - sf::Vector2f((int)x, (int)y + 1));
	float v = VectorUtility::dot(x1y1, point - sf::Vector2f((int)x + 1, (int)y + 1));

	float sx = 3 * powf(x - (int)x, 2) - 2 * powf(x - (int)x, 3);
	float a = s + sx * (t - s);
	float b = u + sx * (v - u);

	float sy = 3 * powf(y - (int)y, 2) - 2 * powf(y - (int)y, 3);

	return a + sy * (b - a);
}

void PerlinNoise::initialise()
{
	srand(_seed);

	//	Generate vectors
	for (unsigned i = 0; i < kMaxWidth + 1; i++)
	{
		_gradients.push_back(std::vector<sf::Vector2f>());
		for (unsigned j = 0; j < kMaxHeight + 1; j++)
		{
			float angle = MathsUtility::randFloat(0.0f, MathsUtility::pi() * 2.0f);
			_gradients[i].push_back(sf::Vector2f(sinf(angle), cosf(angle)));
		}
	}
}