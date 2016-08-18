#include "DragonSpiralTest.hpp"

#include "VectorUtility.hpp"
#include "MathsUtility.hpp"

namespace
{
	const sf::Color kLineStartColour = sf::Color::Blue;
	const sf::Color kLineColourOffset = sf::Color(7, 7, 0);

	const float kDefaultLength = 200.0f;
	const unsigned kDefaultCurveNumber = 4;
}

DragonSpiralTest::DragonSpiralTest(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void DragonSpiralTest::initialise()
{
	sf::Color colour = kLineStartColour;

	Line line;

	_length = kDefaultLength;
	_curveNumber = kDefaultCurveNumber;

	sf::Vector2f centre = sf::Vector2f(0.0f, 360.0f);
	sf::Vector2f offset = sf::Vector2f(1280.0f, 0.0f);
	
	//	Create line
	line.setStartPoint(centre);
	line.setEndPoint(centre + offset);
	line.setFillColor(colour);

	_dragonSpirals.push_back(std::vector<Line>(1, line));

	_points.push_back(centre);
	_points.push_back(centre + offset);
}

void DragonSpiralTest::update()
{
	float deltaTime = _clock.restart().asSeconds();

	_navigation.moveCamera(&_camera, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_prevSpace)
	{
		iterate();
	}

	_prevSpace = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

void DragonSpiralTest::draw()
{
	_window.clear(sf::Color::Black);

	if (_points.size())
	{
		_window.draw(&_points[0], _points.size(), sf::LinesStrip, _camera);
	}

	_window.display();
}

void DragonSpiralTest::iterate()
{
	//	Create new list
	//std::vector<Line> newList;
	std::vector<sf::Vertex> newList;

	//	Increase colour
	_lineColour += kLineColourOffset;

	sf::Color colour = kLineStartColour;

	if (_points.size() < 2) return;

	//	For each point except the last
	for (int i = 0; i < _points.size() - 1; i++)
	{
		//	Add point to new list
		newList.push_back(_points[i]);

		//	Calculate new point
		sf::Vector2f line = _points[i+1].position - _points[i].position;
		line /= 2.0f;

		float temp = line.x;
		line.x = line.y;
		line.y = -temp;

		sf::Vector2f newPoint = ((_points[i].position + _points[i+1].position) / 2.0f) + line * (1.0f - 2.0f * (i % 2));

		//	Add new point into list
		newList.push_back(newPoint);
	}

	//	Add final point
	newList.push_back(_points[_points.size()-1]);

	_points = newList;

}