#include "Edge.hpp"

Edge::Edge()
{
	_net = false;
	_shot = 0;
	_melee = 0;
	_armour = false;
	_laser = false;
}

Edge::Edge(bool net, unsigned shot, unsigned melee, bool armour, bool laser)
{
	_net = net;
	_melee = melee;
	_shot = shot;
	_armour = armour;
	_laser = laser;
}