#include "PerlinNoise3D.hpp"

#include "MathsUtility.hpp"
#include "VectorUtility.hpp"

namespace
{
	const unsigned kMaxWidth = 32;
	const unsigned kMaxHeight = 32;
	const unsigned kMaxDepth = 32;
}

PerlinNoise3D::PerlinNoise3D()
{

}

PerlinNoise3D::PerlinNoise3D(float width, float height, float depth, unsigned seed)
{
	_width = width;
	_height = height;
	_depth = depth;

	_seed = seed;
}

void PerlinNoise3D::initialise()
{
	srand(_seed);

	//	Generate vectors
	for (unsigned i = 0; i < kMaxWidth + 1; i++)
	{
		_gradients.push_back(std::vector<std::vector<sf::Vector3f> >());
		for (unsigned j = 0; j < kMaxHeight + 1; j++)
		{
			_gradients[i].push_back(std::vector<sf::Vector3f>());
			for (unsigned k = 0; k < kMaxDepth + 1; k++)
			{
				float theta = MathsUtility::randFloat(0.0f, 2.0f * MathsUtility::pi());
				float phi = MathsUtility::randFloat(0.0f, 2.0f * MathsUtility::pi());
				_gradients[i][j].push_back(sf::Vector3f(sinf(phi) * cosf(theta), sinf(phi) * sinf(theta), sinf(theta)));
			}
		}
	}
}

float PerlinNoise3D::getNoise(float x, float y, float z)
{
	//	Limiting parameters
	while (x < 0.0f) x += kMaxWidth;
	while (x >= kMaxWidth) x -= kMaxWidth;
	while (y < 0.0f) y += kMaxHeight;
	while (y >= kMaxHeight) y -= kMaxHeight;
	while (z < 0.0f) z += kMaxDepth;
	while (z >= kMaxDepth) z -= kMaxDepth;

	//	Turn points into a vector
	sf::Vector3f point(x, y, z);

	//	Get adjacent points
	sf::Vector3f x0y0z0 = _gradients[(int)x][(int)y][(int)z];
	sf::Vector3f x0y0z1 = _gradients[(int)x][(int)y][(int)z + 1];
	sf::Vector3f x0y1z0 = _gradients[(int)x][(int)y + 1][(int)z];
	sf::Vector3f x0y1z1 = _gradients[(int)x][(int)y + 1][(int)z + 1];
	sf::Vector3f x1y0z0 = _gradients[(int)x + 1][(int)y][(int)z];
	sf::Vector3f x1y0z1 = _gradients[(int)x + 1][(int)y][(int)z + 1];
	sf::Vector3f x1y1z0 = _gradients[(int)x + 1][(int)y + 1][(int)z];
	sf::Vector3f x1y1z1 = _gradients[(int)x + 1][(int)y + 1][(int)z + 1];

	//	Get distance from point for each gradient
	float o = VectorUtility::dot(x0y0z0, point - sf::Vector3f((int)x, (int)y, (int)z));
	float p = VectorUtility::dot(x0y0z1, point - sf::Vector3f((int)x, (int)y, (int)z + 1));
	float q = VectorUtility::dot(x0y1z0, point - sf::Vector3f((int)x, (int)y + 1, (int)z));
	float r = VectorUtility::dot(x0y1z1, point - sf::Vector3f((int)x, (int)y + 1, (int)z + 1));
	float s = VectorUtility::dot(x1y0z0, point - sf::Vector3f((int)x + 1, (int)y, (int)z));
	float t = VectorUtility::dot(x1y0z1, point - sf::Vector3f((int)x + 1, (int)y, (int)z + 1));
	float u = VectorUtility::dot(x1y1z0, point - sf::Vector3f((int)x + 1, (int)y + 1, (int)z));
	float v = VectorUtility::dot(x1y1z1, point - sf::Vector3f((int)x + 1, (int)y + 1, (int)z + 1));

	//	Get weighted average of each point in each axis
	float sx = 3 * powf(x - (int)x, 2) - 2 * powf(x - (int)x, 3);

	float a = o + sx * (s - o);
	float b = p + sx * (t - p);
	float c = q + sx * (u - q);
	float d = r + sx * (v - r);

	float sy = 3 * powf(y - (int)y, 2) - 2 * powf(y - (int)y, 3);

	float e = a + sy * (c - a);
	float f = b + sy * (d - b);

	float sz = 3 * powf(z - (int)z, 2) - 2 * powf(z - (int)z, 3);

	//	Return value
	return e + sz * (f - e);
}