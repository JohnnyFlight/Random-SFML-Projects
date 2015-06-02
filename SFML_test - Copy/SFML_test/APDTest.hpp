#pragma once

#include "Application.hpp"

#include <vector>

class APDTest : public Application
{
public:
	APDTest(unsigned width, unsigned height, std::string title);

	void initialise();
	void update();
	void draw();

protected:
	unsigned _width;
	unsigned _height;

	unsigned _distribution;

	std::vector<std::vector<unsigned> > _counter;
	std::vector<std::vector<bool> > _tokens;

	unsigned _testNumber;
	unsigned _lowestCounter;
	unsigned _highestCounter;

	bool _prevSpace;

private:

};