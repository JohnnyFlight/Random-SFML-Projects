#pragma once

#include <SFML/Graphics.hpp>

class SuperEllipse
{
public:
	SuperEllipse();
	SuperEllipse(float xExponent, float yExponent, float radius);

	sf::Vector2f getPoint(float angle);

private:
	float _xExponent;
	float _yExponent;
	float _radius;

	sf::Vector2f _position;

};