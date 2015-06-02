#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class SierpinskiArrowhead
{
public:
	SierpinskiArrowhead();
	//	Add custom start points here
	SierpinskiArrowhead(unsigned depth);
	SierpinskiArrowhead(sf::Vector2f start, sf::Vector2f end);
	SierpinskiArrowhead(sf::Vector2f start, sf::Vector2f end, unsigned depth);

	void increaseDepth();
	std::vector<sf::Vector2f> *points() { return &_points; }

protected:
	std::vector<sf::Vector2f> _points;
	unsigned _depth;

private:

};