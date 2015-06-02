#pragma once

#include <SFML/Graphics.hpp>

#include "VectorUtility.hpp"

class Particle : public sf::CircleShape
{
public:
	Particle();
	Particle(float radius);
	Particle(float radius, sf::Vector2f position);

	void initialise();

	void update(float timeStep);
	void move(float timeStep);

	inline void setVelocityDirection(sf::Vector2f velocityDirection) { _velocityDirection = VectorUtility::normalised(velocityDirection); }
	inline void setVelocity(const float velocity) { _velocity = velocity; }

	inline void setAccelerationDirection(const sf::Vector2f accelerationDirection) { _accelerationDirection = VectorUtility::normalised(accelerationDirection); }
	inline void setAcceleration(const float acceleration) { _acceleration = acceleration; }

	inline void setAlphaDecay(const float alphaDecay) { _alphaDecay = alphaDecay; }
	inline void setScaleDecay(const float scaleDecay) { _scaleDecay = scaleDecay; }

	inline sf::Vector2f velocityDirection() { return _velocityDirection; }
	inline const float velocity() { return _velocity; }

	inline sf::Vector2f accelerationDirection() { return _accelerationDirection; }
	inline const float acceleration() { return _acceleration; }

	inline const float alpha() { return _alpha; }
	inline const float alphaDecay() { return _alphaDecay; }
	inline const float scaleDecay() { return _scaleDecay; }

protected:
	sf::Vector2f _velocityDirection;
	float _velocity;

	sf::Vector2f _accelerationDirection;
	float _acceleration;

	float _alpha;
	float _alphaDecay;
	float _scaleDecay;

private:

};