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

	sf::Sprite _dotsSprite;
	sf::RenderTexture _dotsTexture;

	std::vector<float> _deviations;
	sf::Sprite _deviationSprite;
	sf::RenderTexture _deviationTexture;

	sf::Vector2f _deviationLimits;

	float _piApproximation;

	unsigned _dotsToAdd;

	unsigned Nc, Ns;

	bool _prevSpace;
	bool _prevUp;
	bool _prevDown;
	bool _prevR;
	
	void update();
	void updateDeviations();

	void draw();
	void drawDeviations();

	void reset();

	void addNewDot(unsigned dots);
	void addDeviation();

	void recalculatePi();
};