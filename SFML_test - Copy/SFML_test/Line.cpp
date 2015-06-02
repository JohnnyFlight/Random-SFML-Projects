#include "Line.hpp"
#include "MathsUtility.hpp"
#include "VectorUtility.hpp"

namespace
{
	const float kDefaultThickness = 1.0f;
}

Line::Line()
	: sf::RectangleShape(sf::Vector2f(1.0f, 1.0f))
{
	_thickness = 1.0f;
	_length = 1.0f;

	_start = sf::Vector2f(0.0f, 0.0f);
	_end = sf::Vector2f(1.0f, 0.0f);
}

void Line::recalculateLength()
{
	//	Euclidean distance from start to end
	sf::Vector2f startToEnd = _end - _start;
	_length = VectorUtility::magnitude(startToEnd);

	setPosition(_start);

	setRotation(atan2f(startToEnd.y, startToEnd.x) * 180.0f / MathsUtility::pi());
	setScale(_length, getScale().y);
}

void Line::recalculateOrigin()
{
	//	Half thickness on y
	setOrigin(0.0f, _thickness / 2.0f);
}