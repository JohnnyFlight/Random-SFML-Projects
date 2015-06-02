#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Agent : public sf::RectangleShape
{
public:
	Agent();
	Agent(float width, float height);

	void update(std::vector<Agent> *agents);
	void move(float timeStep);

	inline sf::Vector2f getDirection() { return _direction; }

protected:
	sf::Vector2f _direction;
	float _velocity;

	sf::Vector2f _accelerationDirection;
	float _acceleration;

	float _neighbourhoodRadius;
	//	Angle spreads out from centre
	float _neighbourhoodAngle;

private:

};