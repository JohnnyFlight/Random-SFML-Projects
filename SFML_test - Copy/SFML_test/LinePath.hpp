#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class LinePath
{
public:
	LinePath();

	inline void addPoint(sf::Vector2f point) { _points.push_back(point); _recalcLength = true; }

	sf::Vector2f getPosition(float distance);
	float getLength();

private:
	std::vector<sf::Vector2f> _points;

	float _length;
	bool _recalcLength;

};