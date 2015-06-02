#pragma once

#include "Application.hpp"

#include <list>

#include "BezierCurve2D.hpp"
#include "LinePath.hpp"
#include "Rose.hpp"

class PathFollowing : public Application
{
public:
	PathFollowing(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	void update();
	void draw();

	BezierCurve2D _path;
	float _pathLength;

	Rose _rose;

	LinePath _linePath;

	float _velocity;
	float _angleVelocity;

	float _position;
	float _distance;
	float _angle;

	unsigned _frameCounter;
	unsigned _framesToCount;
	std::list<float> _frameRates;

	sf::Font _font;
	sf::Text _text;

	std::list<sf::CircleShape> _shapes;
	std::list<sf::CircleShape> _points;

	sf::CircleShape _shape;

};