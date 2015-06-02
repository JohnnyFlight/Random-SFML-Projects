#pragma once

#include "SFML/Graphics.hpp"

class BoomParticle : public sf::CircleShape
{
public:
	enum State { Moving, Expanding, Shrinking };
	
	static const int BOUNCE_UP = 0;
	static const int BOUNCE_RIGHT = 1;
	static const int BOUNCE_DOWN = 2;
	static const int BOUNCE_LEFT = 3;

	BoomParticle();
	BoomParticle(sf::Vector2f position, sf::Vector2f direction);

	void initialise();
	void update(float timeStep);
	void bounce(int direction);
	void hit();

	inline bool expired() { return _radius == 0.0f; }

	inline void setState(State state) { _state = state; }
	
	inline void setMovementDirection(sf::Vector2f movementDirection) { _movementDirection = movementDirection; }
	inline void setVelocity(float velocity) { _velocity = velocity; }

	inline State state() { return _state; }
	
	inline sf::Vector2f movementDirection() { return _movementDirection; }
	inline float velocity() { return _velocity; }

private:
	State _state;

	sf::Vector2f _movementDirection;
	float _velocity;

	float _radius;
	float _maxRadius;

	float _radiusGrowthRate;
	float _radiusShrinkRate;

	void resetCentre();
};