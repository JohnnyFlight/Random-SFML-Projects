#include "Agent.hpp"

#include "VectorUtility.hpp"

namespace
{
	const float kDefaultVelocity = 10.0f;
	const float kDefualtAcceleration = 1.0f;
	const float kDefaultNeighbourhoodRadius = 100.0f;
}

Agent::Agent()
{
	_velocity = kDefaultVelocity;
	_acceleration = kDefualtAcceleration;
	_neighbourhoodRadius = kDefaultNeighbourhoodRadius;
}

Agent::Agent(float width, float height)
	: RectangleShape(sf::Vector2f(width, height))
{
	_velocity = kDefaultVelocity;
	_acceleration = kDefualtAcceleration;
	_neighbourhoodRadius = kDefaultNeighbourhoodRadius;
}

void Agent::update(std::vector<Agent> *agents)
{
	//	Create appropriate vectors
	sf::Vector2f separation(0.0f, 0.0f);
	sf::Vector2f alignment(0.0f, 0.0f);
	sf::Vector2f cohesion(0.0f, 0.0f);

	unsigned consideredAgents = 0;

	for (unsigned i = 0; i < agents->size(); i++)
	{
		Agent *agent = &(*agents)[i];
		//	Discard if not in range
		float sqrMag = VectorUtility::sqrMagnitude(getPosition() - agent->getPosition());
		if (sqrMag < _neighbourhoodRadius * _neighbourhoodRadius)
		{
			consideredAgents++;
			float mag = sqrt(sqrMag);

			//	Separation is line agent->this
			separation += (getPosition() - agent->getPosition()) / (1.0f - (mag / _neighbourhoodRadius));

			//	Alignment
			alignment += agent->getDirection();

			//	Cohesion
			cohesion += (agent->getPosition() - getPosition()) * (1.0f - (mag / _neighbourhoodRadius));
		}
	}
	
	/*
	separation /= (float)consideredAgents;
	alignment /= (float)consideredAgents;
	cohesion /= (float)consideredAgents;
	*/

	_accelerationDirection = separation + alignment + cohesion;
	float mag = VectorUtility::magnitude(_accelerationDirection);
	VectorUtility::normalise(_accelerationDirection);
	if (mag > _acceleration)
	{
		_accelerationDirection *= _acceleration;
	}
	else
	{
		_accelerationDirection *= (mag / _acceleration);
	}
}

void Agent::move(float timeStep)
{
	_direction += _accelerationDirection;
	float mag = VectorUtility::magnitude(_direction);
	VectorUtility::normalise(_direction);
	if (mag > _velocity)
	{
		_direction *= _velocity;
	}

	sf::Shape::move(_direction * timeStep);
}