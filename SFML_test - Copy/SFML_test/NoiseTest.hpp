#pragma once

#include "Application.hpp"

#include "Noise.hpp"
#include "PerlinNoise.hpp"

class NoiseTest : public Application
{
public:
	NoiseTest(unsigned width, unsigned height, std::string title);

	void initialise();
	void update();
	void draw();

protected:
	Noise _noise;
	std::vector<PerlinNoise> _perlin;

	unsigned _octaves;

	sf::Texture _noiseTexture;
	std::vector<sf::Uint8> _noiseData;
	std::vector<sf::Texture> _sampleTextures;
	std::vector<std::vector<sf::Uint8> > _sampleData;

	void calculateNoise();

private:

};