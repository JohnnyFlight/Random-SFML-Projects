#include "StrategyTestGame.hpp"

StrategyTestGame::StrategyTestGame(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void StrategyTestGame::initialise()
{

}

void StrategyTestGame::update()
{

}

void StrategyTestGame::draw()
{
	_window.clear(sf::Color::Black);

	_window.display();
}