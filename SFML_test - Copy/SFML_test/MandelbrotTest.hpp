#pragma once

#include "Application.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class MandelbrotTest : public Application
{
public:
	MandelbrotTest(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	void initialiseRegions();

	void update();
	void updateText();

	void draw();

	void recalculate();
	
	struct CalculateParams
	{
		std::vector<sf::Uint8> *pixelData;
		sf::Rect<float> rect;
		sf::Rect<unsigned> pixels;
		unsigned iterationNumber;
	};
	static void calculate(CalculateParams params);

	void recalculateRegions();

	sf::Texture _texture;
	std::vector<sf::Uint8> _textureData;

	sf::Vector2u _dimensions;
	std::vector<std::vector<sf::Rect<unsigned> > > _subDimensions;

	sf::RectangleShape _shape;
	std::vector<std::vector<sf::RectangleShape> > _regionShapes;

	sf::Rect<float> _region;
	std::vector<std::vector<sf::Rect<float> > > _subRegions;

	std::vector<std::vector<sf::Thread*> > _threads;
	sf::RectangleShape _highlightBox;

	sf::Vector2f _clickPosition;

	float _computeTime;
	unsigned _iterationNumber;

	sf::Font _font;
	sf::Text _infoText;

	bool _prevClick;
	bool _prevR;

	bool _prevW;
	bool _prevA;
	bool _prevS;
	bool _prevD;
};