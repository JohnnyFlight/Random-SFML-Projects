#include "Particle.hpp"

namespace
{
	const float kDefaultRadius = 10.0f;
	const float kDefaultAlpha = 255.0f;
}

Particle::Particle()
	: sf::CircleShape(kDefaultRadius)
{
	initialise();

	_alpha = kDefaultAlpha;
	setOrigin(kDefaultRadius, kDefaultRadius);
}

Particle::Particle(float radius)
	: sf::CircleShape(radius)
{
	initialise();

	_alpha = kDefaultAlpha;
	setOrigin(radius, radius);
}

Particle::Particle(float radius, sf::Vector2f position)
	: sf::CircleShape(radius)
{
	initialise();

	setPosition(position);
	_alpha = kDefaultAlpha;
	setOrigin(radius, radius);
}

void Particle::initialise()
{
	_velocityDirection = sf::Vector2f(0.0f, 0.0f);
	_velocity = 0.0f;

	_accelerationDirection = sf::Vector2f(0.0f, 0.0f);
	_acceleration = 0.0f;
}

void Particle::update(float timeStep)
{
	setScale(getScale().x - _scaleDecay * timeStep, getScale().y - _scaleDecay * timeStep);
	sf::Color colour = getFillColor();
	_alpha -= _alphaDecay * timeStep;
	if (_alpha < 0.0f) _alpha = 0.0f;
	colour.a = (unsigned)_alpha;
	setFillColor(colour);
}

void Particle::move(float timeStep)
{
	//	Update velocity
	_velocityDirection = _velocityDirection * _velocity + _accelerationDirection * _acceleration * timeStep;
	_velocity = VectorUtility::magnitude(_velocityDirection);
	VectorUtility::normalise(_velocityDirection);

	//	Update position
	setPosition(getPosition() + _velocityDirection * _velocity * timeStep);
}