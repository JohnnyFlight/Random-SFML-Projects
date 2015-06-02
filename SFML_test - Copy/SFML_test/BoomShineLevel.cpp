#include "BoomShineLevel.hpp"

namespace
{
	const unsigned kDefaultParticles = 10;
	const unsigned kDefaultClicks = 1;
}

BoomShineLevel::BoomShineLevel()
{
	_particles = kDefaultParticles;
	_clicks = kDefaultClicks;
}

BoomShineLevel::BoomShineLevel(unsigned particles, unsigned clicks, unsigned goal)
{
	_particles = particles;
	_clicks = clicks;
	_goal = goal;
}