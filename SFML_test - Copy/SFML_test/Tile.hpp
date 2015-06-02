#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

#include "Edge.hpp"

namespace
{
	const unsigned kDefaultNumberOfEdges = 6;
}

class Tile
{
public:
	enum Type { Unit, Position, Play, HeadQuarters };
	enum PlayType { Null, Snipe, AirStrike, Move, Battle };
	enum Faction { None, Outpost, Hegemony, Moloch, Doomsday, Borgo };

	Tile();
	Tile(Type type, PlayType playType, Faction _faction, std::string name);

	Edge getEdge(unsigned edge);
	void setEdge(Edge edge, unsigned position);

	void applyWounds(unsigned wounds);

	//	Returns true if tile is dead
	bool resolveWounds();
	inline void resetWounds() { _wounds = 0; }

	inline Type getType() { return _type; }
	inline PlayType getPlayType() { return _playType; }
	inline Faction getFaction() { return _faction; }

	inline void setShields(unsigned shields) { _shields = shields; }
	inline unsigned getShields() { return _shields; }

	inline unsigned getWounds() { return _wounds; }

	inline void setInitiative(unsigned initiative) { _initiative = initiative; }
	inline unsigned getInitiative() { return _initiative; }

	//	Name corresponds to a texture
	inline void setName(std::string name) { _name = name; }
	inline std::string getName() { return _name; }

	static inline unsigned numberOfEdges() { return kDefaultNumberOfEdges; }

private:
	std::string _name;

	Type _type;
	PlayType _playType;
	Faction _faction;

	std::vector<Edge> _edges;
	unsigned _shields;
	unsigned _wounds;
	unsigned _initiative;

	virtual void initialise();
};

#endif