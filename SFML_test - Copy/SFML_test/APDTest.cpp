#include "APDTest.hpp"

#include <iostream>

APDTest::APDTest(unsigned width, unsigned height, std::string title)
	: Application(width, height, title)
{

}

void APDTest::initialise()
{
	_width = 50;
	_height = 50;

	_distribution = 200;
	
	_counter = std::vector<std::vector<unsigned> >(_width, std::vector<unsigned>(_height, 0));
	_tokens = std::vector<std::vector<bool> >(_width, std::vector<bool>(_height, false));

	_testNumber = 0;
}

void APDTest::update()
{
	_lowestCounter = (unsigned)-1;
	_highestCounter = 0;

	_testNumber++;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true && _prevSpace == false)
	//{
		unsigned toDistribute = _distribution;
		unsigned allocatedSpace = _width * _height;

		for (unsigned i = 0; i < _width; i++)
		{
			for (unsigned j = 0; j < _height; j++)
			{
				//	Probability is always dist/allo
				//	For each point determine if it is true
				if (rand() % allocatedSpace < toDistribute)
				{
					_counter[i][j]++;

					if (_counter[i][j] < _lowestCounter)
					{
						_lowestCounter = _counter[i][j];
					}
					else if (_counter[i][j] > _highestCounter)
					{
						_highestCounter = _counter[i][j];
					}

					//	If so reduce distributed
					_tokens[i][j] = true;
					toDistribute--;
				}
				else
				{
					_tokens[i][j] = false;
				}

				allocatedSpace--;
			}
		}
	//}

	_prevSpace = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

void APDTest::draw()
{
	if (_prevSpace == false) return;

	_window.clear(sf::Color::Black);

	float radius = 10.0f;
	sf::RectangleShape shape(sf::Vector2f(radius, radius));

	for (unsigned i = 0; i < _width; i++)
	{
		for (unsigned j = 0; j < _height; j++)
		{
			if (_tokens[i][j] == true)
			{
				shape.setFillColor(sf::Color::Green);
			}
			else
			{
				shape.setFillColor(sf::Color::Blue);
			}

			shape.setPosition(i * radius, j * radius);

			_window.draw(shape);
		}
	}

	for (unsigned i = 0; i < _width; i++)
	{
		for (unsigned j = 0; j < _height; j++)
		{
			sf::Color colour = sf::Color::Black;
			colour.r = (unsigned)((_counter[i][j] / (float)_testNumber) * 255);

			shape.setFillColor(colour);

			shape.setPosition(radius * _width + i * radius, j * radius);

			_window.draw(shape);
		}
	}

	_window.display();
}