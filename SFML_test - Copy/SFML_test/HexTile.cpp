#include "HexTile.hpp"

namespace
{
	const float kDefaultRadius = 70.0f;
}

HexTile::HexTile() :
	sf::CircleShape(kDefaultRadius, 6)
{
	//_radius = kDefaultRadius;
	setRadius(kDefaultRadius);
	setRotation(0);

	initialise();
}

HexTile::HexTile(Tile tile) :
	sf::CircleShape(kDefaultRadius, 6)
{
	_tile = tile;
	setRotation(0);

	//_radius = kDefaultRadius;

	initialise();
}

void HexTile::initialise()
{
	setOrigin(getRadius(), getRadius());
}

Edge HexTile::getEdge(unsigned edge, bool local)
{
	if (local)
	{
		return _tile.getEdge(edge);
	}
	else
	{
		return _tile.getEdge(Tile::numberOfEdges() - edge - 1);
	}
}

bool HexTile::clicked(unsigned x, unsigned y)
{
	//	Assume tile is a circle with radius extending
	//	To the centre of a tile edge
	float rad = getRadius() * sqrt(3.0f) / 2.0f;
	rad *= rad;

	float dx = getPosition().x - x;
	dx *= dx;

	float dy = getPosition().y - y;
	dy *= dy;

	return dx + dy < rad;
}