#include "Noise3DTest.hpp"

#include "MathsUtility.hpp"

namespace
{
	const float kDefaultZVelocity = 1.0f;
	const float kNoiseDimension = 25.0f;
}

Noise3DTest::Noise3DTest(unsigned width, unsigned height, std::string title)
	: Application(width, height, title)
{

}

void Noise3DTest::initialise()
{
	_zPosition = 0.0f;
	_zVelocity = kDefaultZVelocity;

	calculateNoise();
}

void Noise3DTest::calculateNoise()
{
	_noise = PerlinNoise3D(kNoiseDimension, kNoiseDimension, kNoiseDimension);
	_noise.initialise();
}

void Noise3DTest::update()
{
	float timeStep = _clock.restart().asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true)
	{
		_zPosition += _zVelocity * timeStep;
		if (_zPosition > kNoiseDimension)
		{
			_zPosition = kNoiseDimension;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		_zPosition -= _zVelocity * timeStep;
		if (_zPosition < 0.0f)
		{
			_zPosition = 0.0f;
		}
	}
}

void Noise3DTest::draw()
{
	_window.clear(sf::Color::Black);

	unsigned drawDim = 200;

	float shapeDim = 3.0f;

	sf::RectangleShape shape(sf::Vector2f(shapeDim, shapeDim));

	for (unsigned i = 0; i < drawDim; i++)
	{
		for (unsigned j = 0; j < drawDim; j++)
		{
			//	"Quarter Circle" smoothing here
			float noise = ((_noise.getNoise(i * 0.1f, j * 0.1f, _zPosition) + 1.0f) / 2.0f) * sinf((j / (float)drawDim) * MathsUtility::pi() / 2.0f);
			noise *= (1.0f - noise);

			sf::Color colour(255, 255, 255, noise * 255);
			shape.setFillColor(colour);
			shape.setPosition(i * shapeDim, j * shapeDim);

			_window.draw(shape);
		}
	}

	_window.display();
}