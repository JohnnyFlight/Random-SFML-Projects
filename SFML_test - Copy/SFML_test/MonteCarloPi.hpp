#pragma once

#include "Application.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class MonteCarloPi : public Application
{
public:
	MonteCarloPi(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	sf::CircleShape _circle;
	sf::RectangleShape _square;

	sf::Font _font;
	sf::Text _text;

	float _piApproximation;

	unsigned _dotsToAdd;

	std::vector<sf::CircleShape> _dots;

	unsigned Nc, Ns;

	bool _prevSpace;
	bool _prevUp;
	bool _prevDown;
	
	void update();
	void draw();

	void addNewDot();
	void recalculatePi();
};