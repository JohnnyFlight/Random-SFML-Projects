#pragma once

#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

class PixelBuffer
{
public:
	PixelBuffer();
	PixelBuffer(unsigned width, unsigned height, unsigned depth = 1);

	sf::Uint8 *getPointer(unsigned layer = 0);
	
	bool matches(sf::Color colour, unsigned x, unsigned y, unsigned z = 0, bool matchAlpha = false);
	inline bool matches(sf::Color colour, unsigned x, unsigned y, bool matchAlpha = false, unsigned z = 0) { return matches(colour, x, y, z, matchAlpha); }

	sf::Color getColour(unsigned x, unsigned y, unsigned z = 0);
	void setColour (sf::Color colour, unsigned x, unsigned y, unsigned z = 0);

	void fill(sf::Color colour);

	void drawLine(sf::Color colour, sf::Vector3<unsigned> start, sf::Vector3<unsigned> end, float thickness = 0.5f);

private:
	void initialise();

	sf::Vector3<unsigned> _dimensions;

	std::vector<sf::Uint8> _data;
};