#pragma once

#include "Application.hpp"

#include "Line.hpp"
#include <vector>

class DragonSpiralTest : public Application
{
public:
	DragonSpiralTest(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	std::vector<std::vector<Line> > _dragonSpirals;

	sf::Color _lineColour;

	float _length;
	unsigned _curveNumber;

	void update();
	void draw();

	void iterate();

	bool _prevSpace;

};