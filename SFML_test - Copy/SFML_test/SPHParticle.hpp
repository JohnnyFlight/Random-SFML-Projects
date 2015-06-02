#pragma once

#include <SFML/Graphics.hpp>

class SPHParticle
{
public:
	SPHParticle();
	SPHParticle(sf::Vector2f position);

	void initialise();

	inline void setMass(float mass) { _mass = mass; }
	inline void setPosition(sf::Vector2f position) { _position = position; }
	inline void setSpatialDistance(float spatialDistance) { _spatialDistance = spatialDistance; }
	inline void setDensity(float density) { _density = density; }

	inline float mass() { return _mass; }
	inline sf::Vector2f position() { return _position; }
	inline float spatialDistance() { return _spatialDistance; }
	inline float density() { return _density; }

private:
	float _mass;
	float _density;

	sf::Vector2f _position;

	float _spatialDistance;
};