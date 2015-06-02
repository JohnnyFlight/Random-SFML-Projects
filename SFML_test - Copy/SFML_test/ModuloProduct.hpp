#pragma once

#include "Application.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class ModuloProduct : public Application
{
public:
	ModuloProduct(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	std::vector<std::vector<sf::RectangleShape> > _shapes;

	unsigned _numberWidth;
	unsigned _numberHeight;
	unsigned _modulo;

	bool _prevUp;
	bool _prevDown;

	bool _prevLeft;
	bool _prevRight;

	bool _prevW;
	bool _prevS;

	sf::Font _font;
	sf::Text _text;
	sf::Texture *_texture;
	std::vector<sf::Uint8> _textureData;

	void update();
	void draw();

	void recalculate();

	void updateText();

};