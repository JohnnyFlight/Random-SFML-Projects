#pragma once

#include <SFML/Graphics.hpp>

class PerlinNoise
{
public:
	PerlinNoise();
	PerlinNoise(float width, float height, unsigned seed = 0);

	void initialise();

	float getNoise(float x, float y);

protected:
	unsigned _seed;

	//	These will be random unit vectors
	std::vector<std::vector<sf::Vector2f> > _gradients;
	
	float _width, _height;

private:

};