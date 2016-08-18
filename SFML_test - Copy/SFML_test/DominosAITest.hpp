#pragma once

#include "Application.hpp"

#include "DominoAI.hpp"
#include <vector>

class DominosAITest : public Application
{
public:
	DominosAITest(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	void update();
	void draw();

	void playerDraw();
	void opponentDraw();

	sf::Text _fps;
	sf::Font _font;

	std::vector<Domino> _boneyard;
	std::vector<Domino> _playerHand;
	std::vector<Domino> _opponentHand;

	DominoAI _AI;
};