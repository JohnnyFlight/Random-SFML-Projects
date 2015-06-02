#pragma once

#include <SFML/Graphics.hpp>

class Rose
{
public:
	Rose();
	Rose(float lengthScale, float angleScale);

	sf::Vector2f getPoint(float angle);

private:
	float _lengthScale;
	float _angleScale;

	sf::Vector2f _position;
};