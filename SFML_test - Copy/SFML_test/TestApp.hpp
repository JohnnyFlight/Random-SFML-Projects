#pragma once

#include "Application.hpp"

#include "Spline.hpp"
#include "Fibonacci.hpp"
#include "PascalTriangle.hpp"
#include "SierpinskiTriangle.hpp"
#include "SierpinskiArrowhead.hpp"
#include "SierpinskiCarpet.h"

#include <SFML/Graphics.hpp>
#include <vector>

class TestApp : public Application
{
public:
	TestApp();
	TestApp(unsigned width, unsigned height, std::string title);

	void initialise();

protected:
	Spline _spline;
	std::vector<Spline> _splines;
	std::vector<sf::Vector2i> _points;
	//	Used to determine if point should add or subtract from the x- or y-value
	unsigned _stepCounter;

	sf::CircleShape _circle;

	unsigned _splineResolution;

private:
	void update();
	void draw();

	void drawSpline(Spline spline);
	void drawPascal();
	void drawSierpinski();
	void drawSierpinskiArrowhead();
	void drawSierpinskiCarpet();

	sf::Transform _screenCentre;
	sf::Transform _camera;
	float _cameraVelocity;
	float _cameraScale;

	Fibonacci _fibonacci;
	PascalTriangle _pascalTriangle;
	SierpinskiTriangle _sierpinskiTriangle;
	SierpinskiArrowhead _arrowhead;
	SierpinskiCarpet _carpet;

	unsigned _circlesInRing;

	sf::Clock _clock;
};