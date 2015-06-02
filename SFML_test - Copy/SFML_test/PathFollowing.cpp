#include "PathFollowing.hpp"

#include "SuperEllipse.hpp"
#include <sstream>

namespace
{
	const float kDefaultVelocity = 150.0f;
	const float kDefaultAngleVelocity = atanf(1.0f) * 2.0f;

	const float kDefaultRadius = 10.0f;
	const sf::Color kDefaultColour = sf::Color::Magenta;

	const float kColourDecay = 0.99999f;
	const float kColourThreshold = 0.00001f;

	const unsigned kDefaultFramesCounted = 1000;
}

PathFollowing::PathFollowing(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void PathFollowing::initialise()
{
	if (_font.loadFromFile("comic.ttf") == true)
	{
		_text.setFont(_font);
		_text.setColor(sf::Color::White);
	}

	_frameCounter = 0;
	_framesToCount = kDefaultFramesCounted;

	_velocity = kDefaultVelocity;
	_angleVelocity = kDefaultAngleVelocity;

	_shape.setFillColor(kDefaultColour);
	_shape.setRadius(kDefaultRadius);
	_shape.setOrigin(kDefaultRadius, kDefaultRadius);

	SuperEllipse ellipse;

	unsigned pointNumber = 45;
	unsigned rotations = 1;

	float lScale = 300.0f;
	float aScale = 1.0f;

	_rose = Rose(lScale, aScale);

	for (unsigned i = 0; i < pointNumber + 1; i++)
	{
		//_path.addAnchor(ellipse.getPoint(atanf(1.0f) * 8.0f * rotations * i / pointNumber));
		//_linePath.addPoint(ellipse.getPoint(atanf(1.0f) * 8.0f * rotations * i / pointNumber));
		sf::Vector2f point = _rose.getPoint(atanf(1.0f) * 8.0f * rotations * i / pointNumber);
		//_linePath.addPoint(point);

		sf::CircleShape circle(kDefaultRadius);
		circle.setOrigin(kDefaultRadius, kDefaultRadius);
		circle.setFillColor(sf::Color::Green);
		//circle.setPosition(ellipse.getPoint(atanf(1.0f) * 8.0f * rotations * i / pointNumber));
		circle.setPosition(point);

		_points.push_back(circle);
	}
	
	_pathLength = _path.getLength();

	_position = 0.0f;
	_distance = 0.0f;
	_angle = 0.0f;
}

void PathFollowing::update()
{
	float timeStep = _clock.restart().asSeconds();
	float frameRate = 1.0f / timeStep;

	_frameRates.push_back(frameRate);
	if (_frameRates.size() > _framesToCount)
	{
		_frameRates.pop_front();
	}

	_frameCounter++;

	//	Calculate rolling average
	float rollingAverage = 0.0f;
	for (auto iter = _frameRates.begin(); iter != _frameRates.end(); iter++)
	{
		rollingAverage += *iter;
	}
	rollingAverage /= _framesToCount;

	std::stringstream stream;
	stream << "FPS: " << rollingAverage << std::endl;
	stream << "Angle: " << (int)(_angle * (180.0f / (atanf(1.0f) * 8.0f))) << " degrees" << std::endl;
	stream << "Frames: " << _frameCounter << std::endl;
	stream << "Rotations: " << (int)(_angle / (atanf(1.0f) * 8.0f)) << std::endl;
	stream << "Distance: " << _distance << std::endl;
	_text.setString(stream.str());

	/*_position += _velocity * timeStep;
	while (_position > _pathLength)
	{
		_position -= _pathLength;
	}*/

	/*_distance += _velocity * timeStep;
	while (_distance > _linePath.getLength())
	{
		_distance -= _linePath.getLength();
	}*/

	_angle += _angleVelocity * timeStep;

	_shape.setPosition(_rose.getPoint(_angle));
	_shapes.push_back(_shape);

	for (auto iter = _shapes.begin(); iter != _shapes.end();)
	{
		sf::Color colour = iter->getFillColor();
		colour.a *= kColourDecay;
		colour.r *= kColourDecay;
		if (colour.a < kColourThreshold)
		{
			iter = _shapes.erase(iter);
		}
		else
		{
			iter->setFillColor(colour);
			iter++;
		}
	}
}

void PathFollowing::draw()
{
	_window.clear(sf::Color::Black);

	for (auto iter = _shapes.begin(); iter != _shapes.end(); iter++)
	{
		_window.draw(*iter);
	}

	for (auto iter = _points.begin(); iter != _points.end(); iter++)
	{
		_window.draw(*iter);
	}

	_window.draw(_shape);

	_window.draw(_text);

	_window.display();
}