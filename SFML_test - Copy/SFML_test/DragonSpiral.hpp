#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

class DragonSpiral
{
public:
	DragonSpiral();
	DragonSpiral(sf::Vector2f start, sf::Vector2f end);

	inline std::vector<sf::Vector2f> *points() { return &_points; }

	void iterate();

	void clear();

private:
	sf::Vector2f _start;
	sf::Vector2f _end;

	std::vector<sf::Vector2f> _points;

};