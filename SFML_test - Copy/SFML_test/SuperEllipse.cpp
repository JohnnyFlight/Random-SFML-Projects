#include "SuperEllipse.hpp"

#include <cmath>

namespace
{
	const float kDefaultXExponent = 3.0f;
	const float kDefaultYExponent = 3.0f;

	const float kDefaultRadius = 300.0f;

	const sf::Vector2f kDefaultPosition = sf::Vector2f(600.0f, 350.0f);
}

SuperEllipse::SuperEllipse()
{
	_xExponent = kDefaultXExponent;
	_yExponent = kDefaultYExponent;

	_radius = kDefaultRadius;

	_position = kDefaultPosition;
}

SuperEllipse::SuperEllipse(float xExponent, float yExponent, float radius)
{
	_xExponent = xExponent;
	_yExponent = yExponent;

	_radius = radius;

	_position = kDefaultPosition;
}

sf::Vector2f SuperEllipse::getPoint(float angle)
{
	//	Use polar equations to get points
	
	float a = 1.0f;
	float b = 1.0f;

	float n = 0.5f;
	float m = 4.0f;

	float r = _radius * powf(powf((abs(cosf(m * angle / 4.0f) / a)), n) + powf(abs((sinf(m * angle / 4.0f) / b)), n), -1.0f / n);

	float x = r * cosf(angle) + _position.x;
	float y = r * sinf(angle) + _position.y;

	return sf::Vector2f(x, y);
}