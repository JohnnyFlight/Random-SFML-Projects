#include "SPHParticle.hpp"

namespace
{
	const float kDefaultMass = 100.0f;
	const float kDefaultSpatialDistance = 100.0f;
}

SPHParticle::SPHParticle()
{
	initialise();
}

SPHParticle::SPHParticle(sf::Vector2f position)
{
	initialise();

	_position = position;
}

void SPHParticle::initialise()
{
	_mass = kDefaultMass;
	_spatialDistance = kDefaultSpatialDistance;
}