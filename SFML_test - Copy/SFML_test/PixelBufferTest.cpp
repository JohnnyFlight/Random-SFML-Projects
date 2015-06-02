#include "PixelBufferTest.hpp"

namespace
{
	const sf::Vector2f kShapeDimensions = sf::Vector2f(1280.0f, 720.0f);

	const unsigned kDragonSpiralIterations = 20;

	const sf::Vector2u kRepititions = sf::Vector2u(4, 3);

	const float kSpiralLength = 600.0f;
}

PixelBufferTest::PixelBufferTest(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void PixelBufferTest::initialise()
{
	_dragon = DragonSpiral(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(kSpiralLength, 0.0f));

	for (unsigned i = 0; i < kDragonSpiralIterations; i++)
	{
		_dragon.iterate();
	}

	_buffer = PixelBuffer(1280, 720);
	_buffer.fill(sf::Color::White);

	std::vector<sf::Vector2f> *points = _dragon.points();
	for (unsigned i = 0; i < points->size() - 1; i++)
	{
		for (unsigned j = 0; j < kRepititions.x; j++)
		{
			for (unsigned k = 0; k < kRepititions.y; k++)
			{
				sf::Vector3<unsigned> start = sf::Vector3<unsigned>((*points)[i].x, (*points)[i].y, 0);
				start.x += kSpiralLength * j;
				start.y += kSpiralLength * k;

				sf::Vector3<unsigned> end = sf::Vector3<unsigned>((*points)[i + 1].x, (*points)[i + 1].y, 0);
				end.x += kSpiralLength * j;
				end.y += kSpiralLength * k;

				_buffer.drawLine(sf::Color::Black, start, end);
			}
		}
	}

	_texture.create(1280, 720);
	_texture.update(_buffer.getPointer());

	_shape.setSize(kShapeDimensions);
	_shape.setTexture(&_texture);
}

void PixelBufferTest::update()
{

}

void PixelBufferTest::draw()
{
	_window.clear(sf::Color::Black);

	_window.draw(_shape);

	_window.display();
}