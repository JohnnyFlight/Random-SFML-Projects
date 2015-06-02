#ifndef HAND_HPP
#define HAND_HPP

#include "HexTile.hpp"
#include "IClickable.hpp"

#include <vector>

namespace
{
	const unsigned kHandSize = 3;
}

class Hand
{
private:
	std::vector<HexTile> _tiles;
	sf::Vector2f _position;

public:
	Hand();

	bool addTile(Tile tile);
	HexTile *getTile(unsigned position);
	bool removeTile(unsigned positon);

	//	Returns -1 if not clicked
	//	Returns position of clicked tile otherwise
	int clicked(unsigned x, unsigned y);

	inline void setPosition(sf::Vector2f position) { _position = position; resetTilePositions(); }
	inline sf::Vector2f getPosition() { return _position; }

	inline unsigned size() { return _tiles.size(); }

	static inline unsigned handSize() { return kHandSize; }

private:
	void resetTilePositions();
};

#endif