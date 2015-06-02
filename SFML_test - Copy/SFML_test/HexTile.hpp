#ifndef HEX_TILE_HPP
#define HEX_TILE_HPP

/*
	File:		HexTile.hpp
	Date:		31-01-2015
	Author:		Johnathon Forster

	Class:		HexTile
	Requires:	Tile
	Inherits:	sf::CircleShape, IClickable

	Description:
				
*/

#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "Edge.hpp"
#include "IClickable.hpp"

class HexTile : public sf::CircleShape, IClickable
{
protected:
	Tile _tile;

	sf::Texture _texture;

	//	 0 - 5
	unsigned _rotation;

	void initialise();
public:
	HexTile();
	HexTile(Tile tile);

	inline Tile getTile() { return _tile; }
	inline void setTile(Tile tile) { _tile = tile; }

	inline unsigned getRotation() { return _rotation; }
	inline void setRotation(unsigned rotation) { _rotation = rotation; sf::Transformable::setRotation(60.0f * rotation); }

	Edge getEdge(unsigned edge, bool local);

	inline void setRadius(float radius) { sf::CircleShape::setRadius(radius); setOrigin(radius, radius); }
	//inline float getRadius() { return _radius; }

	bool clicked(unsigned x, unsigned y);
};

#endif