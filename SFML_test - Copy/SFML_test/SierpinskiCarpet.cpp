#include "SierpinskiCarpet.h"

namespace
{
	const float kDefaultWidth = 100.0f;
	const float kDefaultHeight = 100.0f;

	const sf::Color kDefaultColour = sf::Color::Blue;
}

SierpinskiCarpet::SierpinskiCarpet()
{
	_colour = kDefaultColour;
	
	_depth = 0;

	sf::RectangleShape square = sf::RectangleShape(sf::Vector2f(kDefaultWidth, kDefaultHeight));
	square.setFillColor(_colour);
	_squares.push_back(square);
}

SierpinskiCarpet::SierpinskiCarpet(unsigned depth)
{
	_colour = kDefaultColour;

	_depth = 0;

	sf::RectangleShape square = sf::RectangleShape(sf::Vector2f(kDefaultWidth, kDefaultHeight));
	square.setFillColor(_colour);
	_squares.push_back(square);

	for (unsigned i = 0; i < depth; i++)
	{
		increaseDepth();
	}
}

SierpinskiCarpet::SierpinskiCarpet(float width, float height)
{
	_colour = kDefaultColour;

	_depth = 0;

	sf::RectangleShape square = sf::RectangleShape(sf::Vector2f(width, height));
	square.setFillColor(_colour);
	_squares.push_back(square);
}

SierpinskiCarpet::SierpinskiCarpet(float width, float height, unsigned depth)
{
	_colour = kDefaultColour;

	_depth = 0;

	sf::RectangleShape square = sf::RectangleShape(sf::Vector2f(width, height));
	square.setFillColor(_colour);
	_squares.push_back(square);

	for (unsigned i = 0; i < depth; i++)
	{
		increaseDepth();
	}
}

void SierpinskiCarpet::increaseDepth()
{
	//	For every square
	//	Divide into 8 smaller squares (1/3 size) around a blank square
	std::vector<sf::RectangleShape> squares;
	for (unsigned i = 0; i < _squares.size(); i++)
	{
		sf::Vector2f position = _squares[i].getPosition();
		sf::Vector2f size = _squares[i].getSize();
		size /= 3.0f;
		for (unsigned j = 0; j < 9; j++)
		{
			if (j == 4) continue;

			sf::RectangleShape square = sf::RectangleShape(size);
			square.setPosition(position.x + size.x * (j % 3), position.y + size.y * (j / 3));
			square.setFillColor(_colour);
			squares.push_back(square);
		}
	}

	_squares.clear();
	_squares = squares;

	_depth++;
}

void SierpinskiCarpet::setColour(sf::Color colour)
{
	_colour = colour;

	for (unsigned i = 0; i < _squares.size(); i++)
	{
		_squares[i].setFillColor(_colour);
	}
}