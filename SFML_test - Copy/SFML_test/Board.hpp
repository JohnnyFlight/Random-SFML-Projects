#pragma once

#include <SFML/Graphics.hpp>

#include "Mask.hpp"

class Board
{
protected:
	Mask _mask;
	//	Tracks when tiles are placed and removed from board
	Mask _fill;

public:
	Board();
	Board(unsigned width, unsigned height);
	Board(Mask mask);

	//	Returns the axis in which they are adjacent/aligned
	//	Returns -1 is not adjacent/aligned
	//	Point one is "source" point
	//	Point 2 is compared with point 1 to determine adjacency
	int areAdjacent(unsigned x1, unsigned y1, unsigned x2, unsigned y2);

	bool isValid(unsigned x, unsigned y);
	bool isEmpty(unsigned x, unsigned y);

	void placeTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);

	sf::Vector2u getAdjacent(unsigned x, unsigned y, unsigned rotation);

	bool isFull();

	inline unsigned getWidth() { return _mask.getWidth(); }
	inline unsigned getHeight() { return _mask.getHeight(); }
};