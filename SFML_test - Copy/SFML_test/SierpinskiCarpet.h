#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

class SierpinskiCarpet
{
public:
	SierpinskiCarpet();
	SierpinskiCarpet(unsigned depth);
	SierpinskiCarpet(float width, float height);
	SierpinskiCarpet(float width, float height, unsigned depth);

	inline std::vector<sf::RectangleShape> *squares() { return &_squares; }

	void increaseDepth();
	void setColour(sf::Color colour);

protected:
	std::vector<sf::RectangleShape> _squares;
	sf::Color _colour;
	unsigned _depth;
private:

};