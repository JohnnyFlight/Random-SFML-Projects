#pragma once

#include "Application.hpp"

class StrategyTestGame : public Application
{
public:
	StrategyTestGame(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	void update();
	void draw();

};