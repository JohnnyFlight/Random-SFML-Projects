#ifndef EDGE_HPP
#define EDGE_HPP

class Edge
{
	bool _net;
	unsigned _melee;
	unsigned _shot;
	bool _armour;
	bool _laser;

public:
	Edge();
	Edge(bool net, unsigned shot, unsigned melee, bool armour, bool laser);

	bool inline hasNet() { return _net; }
	unsigned inline hasMelee() { return _melee; }
	unsigned inline hasShot() { return _shot; }
	bool inline hasArmour() { return _armour; }
	bool inline hasLaser() { return _laser; }
};

#endif