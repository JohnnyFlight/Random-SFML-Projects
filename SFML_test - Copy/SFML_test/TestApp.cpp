#include "TestApp.hpp"

namespace
{
	const float kDefaultWidth = 200.0f;
	const float kDefaultHeight = 200.0f;

	const std::string kDefaultTitle = "Titty Sprinkles";

	const unsigned kDefaultSplineResolution = 20;
	const float kDefaultCircleRadius = 5.0f;
	const unsigned kDefaultCirclesInRing = 8;

	const float kDefaultCameraVelocity = 100.0f;

	const unsigned kDefaultFibonacciSteps = 20;
}

TestApp::TestApp() :
Application(kDefaultWidth, kDefaultHeight, kDefaultTitle)
{
	
}

TestApp::TestApp(unsigned width, unsigned height, std::string title) :
Application(width, height, title)
{

}

void TestApp::initialise()
{
	sf::Vector2f windowSize;
	windowSize.x = _window.getSize().x / 2;
	windowSize.y = _window.getSize().y / 2;
	_screenCentre.translate(windowSize);

	_splineResolution = kDefaultSplineResolution;

	_circle.setRadius(kDefaultCircleRadius);
	_circle.setFillColor(sf::Color::Magenta);

	_spline.setEnd(sf::Vector3f(800.0f, 200.0f, 0.0f));
	_spline.setAnchor(sf::Vector3f(400.0f, 400.0f, 0.0f));

	_cameraVelocity = kDefaultCameraVelocity;
	_cameraScale = 1.0f;

	_fibonacci = Fibonacci(kDefaultFibonacciSteps);

	_circlesInRing = kDefaultCirclesInRing;

	_stepCounter = 0;
	_points.push_back(sf::Vector2i(0, 0));

	for (_stepCounter = 0; _stepCounter < kDefaultFibonacciSteps; _stepCounter++)
	{
		sf::Vector2i point = _points[_points.size() - 1];
		float fibValue = _fibonacci.calculateValue(_stepCounter);

		//	1: +x, +y
		//	2: +x, -y
		//	3: -x, -y
		//	0: -x, +y
		switch ((_stepCounter + 1) % 4)
		{
		case 1:
			point.x += fibValue;
			point.y += fibValue;
			break;
		case 2:
			point.x += fibValue;
			point.y -= fibValue;
			break;
		case 3:
			point.x -= fibValue;
			point.y -= fibValue;
			break;
		case 0:
			point.x -= fibValue;
			point.y += fibValue;
			break;
		}

		_points.push_back(point);
	}

	for (unsigned i = 2; i < _points.size(); i++)
	{
		//	Create a spline from i-2 to i-1
		sf::Vector3f start = sf::Vector3f(_points[i-2].x, _points[i-2].y, 0.0f);
		sf::Vector3f end = sf::Vector3f(_points[i-1].x, _points[i-1].y, 0.0f);
		sf::Vector3f anchor;
		if (i % 2 == 0)
		{
			anchor = sf::Vector3f(start.x, end.y, 0.0f);
		}
		else
		{
			anchor = sf::Vector3f(end.x, start.y, 0.0f);
		}

		_splines.push_back(Spline(start, end, anchor));
	}

	_pascalTriangle = PascalTriangle(10);
	_sierpinskiTriangle = SierpinskiTriangle(100);

	_arrowhead = SierpinskiArrowhead(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(200.0f, 0.0f));
	_carpet = SierpinskiCarpet(4);
}

void TestApp::update()
{
	sf::Time elapsedTime = _clock.restart();

	float deltaTime = elapsedTime.asSeconds();

	//	Input stuff goes here
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_arrowhead.increaseDepth();
	}

	_navigation.moveCamera(&_camera, deltaTime);
}

void TestApp::draw()
{
	_window.clear(sf::Color::Black);

	for (unsigned i = 0; i < _splineResolution; i++)
	{
		float position = (float)i / _splineResolution;

		sf::Vector3f splinePoint = _spline.getPoint(position);

		//	Render circles around each node in the spline

		_circle.setPosition(splinePoint.x, splinePoint.y);

		_window.draw(_circle, _screenCentre * _camera);
	}

	for (unsigned i = 0; i < _fibonacci.calculatedSteps(); i++)
	{
		_circle.setPosition(i * 10, _fibonacci.calculateValue(i));

		_window.draw(_circle, _screenCentre * _camera);
	}

	for (unsigned i = 0; i < _points.size(); i++)
	{
		_circle.setPosition(_points[i].x, _points[i].y);

		_window.draw(_circle, _screenCentre * _camera);
	}

	for (unsigned i = 0; i < _splines.size(); i++)
	{
		drawSpline(_splines[i]);
	}

	drawSierpinskiCarpet();

	_window.display();
}

void TestApp::drawSpline(Spline spline)
{
	for (unsigned i = 0; i < kDefaultSplineResolution; i++)
	{
		float position = (float)i / kDefaultSplineResolution;
		sf::Vector3f point = spline.getPoint(position);
		_circle.setPosition(point.x, point.y);

		_window.draw(_circle, _screenCentre * _camera);
	}
}

void TestApp::drawPascal()
{
	float spacing = 20.0f;
	sf::CircleShape circle(10.0f);

	for (unsigned i = 0; i < _pascalTriangle.depth(); i++)
	{
		for (unsigned j = 0; j <= i; j++)
		{
			circle.setPosition(j * spacing - i * spacing / 2.0f, i * spacing);
			long long unsigned value = _pascalTriangle.getValue(i, j);
			switch (value % 3)
			{
			case 0:
				circle.setFillColor(sf::Color::Red);
				break;
			case 1:
				circle.setFillColor(sf::Color::Green);
				break;
			case 2:
				circle.setFillColor(sf::Color::Blue);
				break;
			}

			_window.draw(circle, _screenCentre * _camera);
		}
	}
}

void TestApp::drawSierpinski()
{
	float spacing = 20.0f;
	sf::CircleShape circle(10.0f, 3);

	for (unsigned i = 0; i < _sierpinskiTriangle.depth(); i++)
	{
		for (unsigned j = 0; j <= i; j++)
		{
			circle.setPosition(j * spacing - i * spacing / 2.0f, i * spacing);
			long long unsigned value = _sierpinskiTriangle.getValue(i, j);
			switch (value)
			{
			case 0:
				circle.setFillColor(sf::Color::Red);
				break;
			case 1:
				circle.setFillColor(sf::Color::Green);
				break;
			case 2:
				circle.setFillColor(sf::Color::Blue);
				break;
			}

			_window.draw(circle, _screenCentre * _camera);
		}
	}
}

void TestApp::drawSierpinskiArrowhead()
{
	std::vector<sf::Vector2f> *points = _arrowhead.points();

	sf::CircleShape circle(0.1f, 3);
	circle.setFillColor(sf::Color::Green);
	for (unsigned i = 0; i < points->size(); i++)
	{
		circle.setPosition((*points)[i]);
		_window.draw(circle, _screenCentre * _camera);
	}
}

void TestApp::drawSierpinskiCarpet()
{
	std::vector<sf::RectangleShape> *squares = _carpet.squares();

	for (unsigned i = 0; i < squares->size(); i++)
	{
		_window.draw((*squares)[i], _screenCentre * _camera);
	}
}