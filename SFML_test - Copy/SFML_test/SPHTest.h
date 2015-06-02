#pragma once

#include "Application.hpp"

#include "SPHParticle.hpp"
#include <vector>

class SPHTest : public Application
{
public:
	SPHTest(unsigned width, unsigned height, std::string title);

	void initialise();
	void update();
	void draw();

private:
	sf::Clock _clock;

	float _maxDensity;

	unsigned calculateQuantity(sf::Vector2f position, float range);
	float calculateDensity(sf::Vector2f position);
	float gaussianKernelFunction(sf::Vector2f position, float range);

	std::vector<SPHParticle> _particles;
};