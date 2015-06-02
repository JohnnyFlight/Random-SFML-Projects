#pragma once

#include <SFML/Graphics.hpp>

class PerlinNoise3D
{
public:
	PerlinNoise3D();
	PerlinNoise3D(float width, float height, float depth, unsigned seed = 0);

	void initialise();

	float getNoise(float x, float y, float z);

private:
	unsigned _seed;

	std::vector<std::vector<std::vector<sf::Vector3f> > > _gradients;

	float _width, _height, _depth;
};