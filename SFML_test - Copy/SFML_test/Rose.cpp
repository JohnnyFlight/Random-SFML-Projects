#include "Rose.hpp"

namespace
{
	const float kDefaultLengthScale = 300.0f;
	const float kDefaultAngleScale = 5.0f;

	const sf::Vector2f kDefaultPosition = sf::Vector2f(600.0f, 350.0f);
}

Rose::Rose()
{
	_lengthScale = kDefaultLengthScale;
	_angleScale = kDefaultAngleScale;

	_position = kDefaultPosition;
}

Rose::Rose(float lengthScale, float angleScale)
{
	_lengthScale = lengthScale;
	_angleScale = angleScale;

	_position = kDefaultPosition;
}

sf::Vector2f Rose::getPoint(float angle)
{
	float r = _lengthScale * sinf(_angleScale * angle);

	float x = r * cosf(angle) + _position.x;
	float y = r * sinf(angle) + _position.y;

	return sf::Vector2f(x, y);
}