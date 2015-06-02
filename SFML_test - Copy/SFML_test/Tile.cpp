#include "Tile.hpp"

Tile::Tile()
{
	_edges = std::vector<Edge>(numberOfEdges());

	_type = Type::Unit;
	_playType = PlayType::Null;
	_name = "Default";
	_faction = Faction::None;

	initialise();
}

Tile::Tile(Type type, PlayType playType, Faction faction, std::string name)
{
	_edges = std::vector<Edge>(numberOfEdges());

	_type = type;
	_playType = playType;
	_name = name;
	_faction = faction;

	initialise();
}

Edge Tile::getEdge(unsigned edge)
{
	return _edges[edge % numberOfEdges()];
}

void Tile::setEdge(Edge edge, unsigned position)
{
	_edges[position % numberOfEdges()] = edge;
}

void Tile::applyWounds(unsigned wounds)
{
	_wounds += wounds;
}

bool Tile::resolveWounds()
{
	return (_wounds > _shields);
}

void Tile::initialise()
{
	_shields = 0;
	_wounds = 0;
	_initiative = 0;
}