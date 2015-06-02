#include "Hand.hpp"

namespace
{
	const float kTileDistance = 150.0f;
}

Hand::Hand()
{

}

bool Hand::addTile(Tile tile)
{
	if (_tiles.size() < handSize())
	{
		HexTile ht = tile;
		_tiles.push_back(ht);
		resetTilePositions();
		return true;
	}
	else
		return false;
}

HexTile *Hand::getTile(unsigned position)
{
	if (position < _tiles.size())
		return &_tiles[position];
	else
		return NULL;
}

bool Hand::removeTile(unsigned position)
{
	if (position < _tiles.size())
	{
		_tiles.erase(_tiles.begin() + position);
		resetTilePositions();

		return true;
	}
	else
		return false;
}

int Hand::clicked(unsigned x, unsigned y)
{
	for (unsigned i = 0; i < _tiles.size(); i++)
	{
		if (_tiles[i].clicked(x, y))
		{
			return i;
		}
	}

	return -1;
}

void Hand::resetTilePositions()
{
	//	Reset positions of each tile
	for(unsigned i = 0; i < _tiles.size(); i++)
	{
		_tiles[i].setPosition(_position);
		_tiles[i].move(kTileDistance * i, 0.0f);
	}
}