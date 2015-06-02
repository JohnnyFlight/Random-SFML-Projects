#include "SPHTest.h"

#include "VectorUtility.hpp"

namespace
{
	const unsigned kParticleNumber = 1000;
}

SPHTest::SPHTest(unsigned width, unsigned height, std::string title)
	: Application(width, height, title)
{

}

void SPHTest::initialise()
{
	//	Create particles
	for (unsigned i = 0; i < kParticleNumber; i++)
	{
		//	Position randomly
		SPHParticle particle(VectorUtility::randomInRectf(sf::Rect<float>(0.0f, 0.0f, _windowWidth, _windowHeight)));
		_particles.push_back(particle);
	}

	_clock.restart();
}

void SPHTest::update()
{
	float timeStep = _clock.restart().asSeconds();

	_maxDensity = 0.0f;

	float minDensity = 10000.0f;

	for (unsigned i = 0; i < _particles.size(); i++)
	{
		float density = calculateDensity(_particles[i].position());
		_particles[i].setDensity(density);

		if (density > _maxDensity)
		{
			_maxDensity = density;
		}
		else if (density < minDensity)
		{
			minDensity = density;
		}
	}

	if (_maxDensity == 0.0f)
	{
		_maxDensity = 1.0f;
	}
}

void SPHTest::draw()
{
	_window.clear(sf::Color::Black);

	sf::CircleShape shape;

	sf::Color spatialDifferenceColour(sf::Color::Green);
	spatialDifferenceColour.a = 16;
	
	sf::Color particleColour(sf::Color::Cyan);

	//	Render spatial distance
	for (unsigned i = 0; i < _particles.size(); i++)
	{
		float spatialDistance = _particles[i].spatialDistance();
		shape.setRadius(spatialDistance);
		shape.setOrigin(spatialDistance, spatialDistance);
		shape.setPosition(_particles[i].position());
		shape.setFillColor(spatialDifferenceColour);

		_window.draw(shape);
	}

	//	Then render particle size based on mass
	for (unsigned i = 0; i < _particles.size(); i++)
	{
		float radius = sqrtf(_particles[i].mass());
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(_particles[i].position());

		//	Eventually convert this to HSL
		sf::Vector3f colourHSL(120.0f - (_particles[i].density() / _maxDensity) * 120.0f, 1.0f, 0.5f);
		sf::Color colourRGB = VectorUtility::vectorToColour(VectorUtility::HSLToRGB(colourHSL), 1.0f);
		shape.setFillColor(colourRGB);
		//shape.setFillColor(sf::Color(0, 0, (unsigned)((_particles[i].density() / _maxDensity) * 255.0f)));

		_window.draw(shape);
	}

	_window.display();
}

float SPHTest::calculateDensity(sf::Vector2f position)
{
	//	Density = density(pos)
	//	density(pos) = sigma(mass*kernel(pos - position, sd))
	float density = 0.0f;

	for (unsigned i = 0; i < _particles.size(); i++)
	{
		float mass = _particles[i].mass();
		float gkf = gaussianKernelFunction(position - _particles[i].position(), _particles[i].spatialDistance());
		density += mass * gkf;
	}

	return density;
}

unsigned SPHTest::calculateQuantity(sf::Vector2f position, float range)
{
	//	Apparently this is much more complex than I previously thought
	unsigned quantity = 0;
	//	Quantity is every particle in this range
	for (unsigned i = 0; i < _particles.size(); i++)
	{
		if (VectorUtility::sqrMagnitude(position - _particles[i].position()) > range * range)
		{
			quantity++;
		}
	}

	return 0;
}

float SPHTest::gaussianKernelFunction(sf::Vector2f position, float range)
{
	float gamma = 1.0f / (2.0f * range * range);
	return expf(-VectorUtility::sqrMagnitude(position) * gamma);
}