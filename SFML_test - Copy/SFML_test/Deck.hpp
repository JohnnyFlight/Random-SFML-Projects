#ifndef DECK_HPP
#define DECK_HPP

#include "Tile.hpp"
#include "HexTile.hpp"

#include <stack>

class Deck : public HexTile
{
public:
	Deck();
	virtual ~Deck();

	Tile peek();
	Tile draw();
	bool isEmpty();
	unsigned getSize();
	inline void addTile(Tile tile) { _tiles.push(tile); }

	void shuffle();

protected:
	std::stack<Tile> _tiles;
};	

#endif