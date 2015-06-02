#include "Board.hpp"

namespace
{
	const unsigned kDefaultWidth = 10;
	const unsigned kDefaultHeight = 20;

	const unsigned kDefaultAxis = (unsigned)-1;
}

Board::Board()
{
	_mask = Mask::create4PlayerMask();
	_fill = Mask::create4PlayerMask();
}

Board::Board(unsigned width = kDefaultWidth, unsigned height = kDefaultHeight)
{
	_mask = Mask(width, height);
	_fill = Mask(width, height);
}

Board::Board(Mask mask)
{
	_mask = mask;
}

int Board::areAdjacent(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
{
	//	Checking if above-right
	
	//	If y1 is above y2
	if (y2 == y1 - 1)
	{
		//	If y1 is even
		if (y1 % 2 == 0)
		{
			if (x2 == x1) return 0;
		}
		//	If y1 is odd
		else
		{
			if (x2 == x1 + 1) return 0;
		}
	}

	//	Right
	if (x2 == (x1 + 1) && y2 == y1) return 1;

	//	Below-right
	
	//	If y1 is below y2
	if (y2 == y1 + 1)
	{
		//	If y1 is even
		if (y1 % 2 == 0)
		{
			if (x2 == x1) return 2;
		}
		//	If y1 is odd
		else
		{
			if (x2 == x1 + 1) return 2;
		}
	}

	//	Below-left

	//	If y2 is below y1
	if (y2 == y1 + 1)
	{
		//	If y1 is even
		if (y1 % 2 == 0)
		{
			if (x2 == x1 - 1) return 3;
		}
		//	If y1 is odd
		else
		{
			if (x2 == x1) return 3;
		}
	}

	//	Left
	if ((x2 == (x1 - 1)) && (y2 == y1)) return 4;

	//	Above-left

	//	If y2 is above y1
	if (y2 == y1 - 1)
	{
		//	If y1 is even
		if (y1 % 2 == 0)
		{
			if (x2 == x1 - 1) return 5;
		}
		//	If y1 is odd
		else
		{
			if (x2 == x1) return 5;
		}
	}

	return -1;
}

//\__/01\__/11\__/  \__/
///02\__/12\__/  \__/  \
//\__/03\__/13\__/  \__/
///04\__/14\__/  \__/  \
//\__/05\__/15\__/  \__/
///06\__/16\__/  \__/  \

bool Board::isValid(unsigned x, unsigned y)
{
	return _mask.isValid(x, y);
}

bool Board::isEmpty(unsigned x, unsigned y)
{
	return _fill.isValid(x, y);
}

void Board::placeTile(unsigned x, unsigned y)
{
	_fill.setState(x, y, false);
}

void Board::removeTile(unsigned x, unsigned y)
{
	_fill.setState(x, y, true);
}

sf::Vector2u Board::getAdjacent(unsigned x, unsigned y, unsigned rotation)
{
	switch (rotation)
	{
	case 0:
		if (y % 2 == 0)
		{
			return sf::Vector2u(x, y - 1);
		}
		else
		{
			return sf::Vector2u(x + 1, y - 1);
		}
		break;
	case 1:
		return sf::Vector2u(x + 1, y);
		break;
	case 2:
		if (y % 2 == 0)
		{
			return sf::Vector2u(x, y + 1);
		}
		else
		{
			return sf::Vector2u(x + 1, y + 1);
		}
		break;
	case 3:
		if (y % 2 == 0)
		{
			return sf::Vector2u(x - 1, y + 1);
		}
		else
		{
			return sf::Vector2u(x, y + 1);
		}
		break;
	case 4:
		return sf::Vector2u(x - 1, y);
		break;
	case 5:
		if (y % 2 == 0)
		{
			return sf::Vector2u(x + 1, y - 1);
		}
		else
		{
			return sf::Vector2u(x, y - 1);
		}
		break;
	}

	return sf::Vector2u();
}

bool Board::isFull()
{
	//	Go through fill
	for (unsigned i = 0; i < _fill.getWidth(); i++)
	{
		for (unsigned j = 0; j < _fill.getHeight(); j++)
		{
			//	If any cell is empty return false
			if (_fill.isValid(i, j) == true)
			{
				return false;
			}
		}
	}

	//	Otherwise return true
	return true;
}