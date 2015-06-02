#include "BoomParticle.hpp"

#include "VectorUtility.hpp"

namespace
{
	const float kInitialRadius = 10.0f;
	const float kDefaultMaxRadius = 100.0f;

	const float kDefaultRadiusGrowthRate = 30.0f;
	const float kDefaultRadiusShrinkRate = 100.0f;

	const sf::Vector2f kDefaultMovementDirection = VectorUtility::normalised(sf::Vector2f(1.0f, 1.0f));
	const float kDefaultVelocity = 100.0f;
}

BoomParticle::BoomParticle()
{
	initialise();
}

BoomParticle::BoomParticle(sf::Vector2f position, sf::Vector2f direction)
{
	initialise();
	
	setPosition(position);
	_movementDirection = direction;
}

void BoomParticle::initialise()
{
	_state = State::Moving;

	_radius = kInitialRadius;
	_maxRadius = kDefaultMaxRadius;

	_radiusGrowthRate = kDefaultRadiusGrowthRate;
	_radiusShrinkRate = kDefaultRadiusShrinkRate;

	_movementDirection = kDefaultMovementDirection;
	_velocity = kDefaultVelocity;

	setRadius(_radius);
}

void BoomParticle::update(float timeStep)
{
	switch (_state)
	{
	case State::Moving:
		move(_movementDirection * _velocity * timeStep);
		break;
	case State::Expanding:
		_radius += _radiusGrowthRate * timeStep;

		if (_radius >= _maxRadius)
		{
			_radius = _maxRadius;
			_state = State::Shrinking;
		}
		break;
	case State::Shrinking:
		_radius -= _radiusShrinkRate * timeStep;
		if (_radius < 0.0f)
		{
			_radius = 0.0f;
		}
		break;
	}

	setRadius(_radius);
	resetCentre();
}

void BoomParticle::bounce(int direction)
{
	switch (direction)
	{
	case BOUNCE_UP:
		_movementDirection.y *= -1.0f;
		break;
	case BOUNCE_RIGHT:
		_movementDirection.x *= -1.0f;
		break;
	case BOUNCE_DOWN:
		_movementDirection.y *= -1.0f;
		break;
	case BOUNCE_LEFT:
		_movementDirection.x *= -1.0f;
		break;
	}
}

void BoomParticle::hit()
{
	_state = State::Expanding;
}

void BoomParticle::resetCentre()
{
	setOrigin(_radius, _radius);
}