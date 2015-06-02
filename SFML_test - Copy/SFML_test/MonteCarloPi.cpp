#include "MonteCarloPi.hpp"

#include "MathsUtility.hpp"
#include "VectorUtility.hpp"

#include <sstream>

namespace
{
	const sf::Vector2f kAreaDimensions = sf::Vector2f(600.0f, 600.0f);
	const sf::Vector2f kStartPoint = sf::Vector2f(50.0f, 50.0f);

	const sf::Color kSquareColour = sf::Color::White;
	const sf::Color kCircleColour = sf::Color(64, 64, 64);
	const sf::Color kDotColour = sf::Color::Magenta;

	const float kDotRadius = 1.0f;
	const unsigned kDefaultDotsToAdd = 10;
	const unsigned kIncrementValue = 10;
}

MonteCarloPi::MonteCarloPi(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void MonteCarloPi::initialise()
{
	_dotsToAdd = kDefaultDotsToAdd;

	Nc = Ns = 0;

	_circle = sf::CircleShape(kAreaDimensions.x / 2.0f);
	_circle.setPosition(kStartPoint + kAreaDimensions);
	_circle.setOrigin(kAreaDimensions);
	_circle.setFillColor(kCircleColour);

	_square = sf::RectangleShape(kAreaDimensions);
	_square.setPosition(kStartPoint);
	_square.setFillColor(kSquareColour);

	//	Load font
	if (_font.loadFromFile("comic.ttf"))
	{
		_text.setFont(_font);
		_text.setColor(sf::Color::White);
		_text.setPosition(kStartPoint.x + kAreaDimensions.x, 0.0f);
		_text.setString("HJKHKJHKJHJKHJKHKJ");
		_text.setCharacterSize(20);
	}
}

void MonteCarloPi::update()
{
	bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

	if (space && !_prevSpace)
	{
		for (unsigned i = 0; i < _dotsToAdd; i++)
		{
			addNewDot();
		}
	}

	if (up && !_prevUp)
	{
		_dotsToAdd += kIncrementValue;
	}

	if (down && !_prevDown)
	{
		if (_dotsToAdd >= kIncrementValue)
		{
			_dotsToAdd -= kIncrementValue;
		}
	}

	std::stringstream stream;
	stream << "Theory:" << std::endl;
	stream << "Area of circle = pi * radius ^ 2" << std::endl;
	stream << "Area of square = (2 * radius) ^ 2" << std::endl;
	stream << "Ratio of two areas is 4 / pi" << std::endl;
	stream << "Where Nd is dots in circle and Ns is dots in square" << std::endl;
	stream << "pi ~= 4 * Nc / Ns" << std::endl;
	stream << "So with Nc = " << Nc << " and Ns = " << Ns << std::endl;
	stream << "Our approximation of pi = " << 4.0f * Nc / Ns << std::endl;
	stream << "Press space to add " << _dotsToAdd << " dots." << std::endl;
	stream << "Press up and down to add " << kIncrementValue << " more or fewer dots.";

	_text.setString(stream.str());

	_prevSpace = space;
	_prevUp = up;
	_prevDown = down;
}

void MonteCarloPi::draw()
{
	_window.clear(sf::Color::Black);

	_window.draw(_square);
	_window.draw(_circle);

	for (unsigned i = 0; i < _dots.size(); i++)
	{
		_window.draw(_dots[i]);
	}

	_window.draw(_text);

	_window.display();
}

void MonteCarloPi::addNewDot()
{
	sf::Vector2f position = VectorUtility::randomInRectf(sf::Rect<float>(kStartPoint, kAreaDimensions));

	sf::CircleShape dot(kDotRadius, 6);
	dot.setPosition(position);
	dot.setOrigin(kDotRadius, kDotRadius);
	dot.setFillColor(kDotColour);

	_dots.push_back(dot);

	Ns++;
	if (VectorUtility::magnitude(position - _circle.getPosition()) < kAreaDimensions.x)
	{
		Nc++;
	}
}

void MonteCarloPi::recalculatePi()
{
	//	Ac = pi * r * r
	//	As = 4 * r * r
	//	Ratio between two areas = 
}