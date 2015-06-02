#include "ModuloProduct.hpp"

#include <sstream>
#include "BezierCurve2D.hpp"

namespace
{
	const unsigned kDefaultNumberWidth = 64;
	const unsigned kDefaultNumberHeight = 64;
	const unsigned kDefaultModulo = 1;

	const float kShapeDimensions = 5.0f;
}

ModuloProduct::ModuloProduct(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void ModuloProduct::initialise()
{
	_numberWidth = kDefaultNumberWidth;
	_numberHeight = kDefaultNumberHeight;
	_modulo = kDefaultModulo;

	if (_font.loadFromFile("comic.ttf"))
	{
		_text.setFont(_font);
		_text.setColor(sf::Color::White);
		_text.setPosition(sf::Vector2f(640.0f, 0.0f));

		updateText();
	}

	_texture = new sf::Texture();
	_texture->create(_numberWidth, _numberHeight);

	recalculate();
}

void ModuloProduct::update()
{
	bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	
	bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	bool W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

	//	Check input here
	if (up && !_prevUp)
	{
		if (_numberHeight > 0)
		{
			_numberHeight--;
			recalculate();
		}
	}

	if (down && !_prevDown)
	{
		_numberHeight++;
		recalculate();
	}

	if (left && !_prevLeft)
	{
		if (_numberWidth > 0)
		{
			_numberWidth--;
			recalculate();
		}
	}

	if (right && !_prevRight)
	{
		_numberWidth++;
		recalculate();
	}

	if (W)
	{
		_modulo++;
		recalculate();
	}

	if (S && !_prevS)
	{
		if (_modulo > 0)
		{
			_modulo--;
			recalculate();
		}
	}

	updateText();

	_prevUp = up;
	_prevDown = down;

	_prevLeft = left;
	_prevRight = right;

	_prevW = W;
	_prevS = S;
}

void ModuloProduct::draw()
{
	_window.clear(sf::Color::Black);

	for (unsigned i = 0; i < _shapes.size(); i++)
	{
		for (unsigned j = 0; j < _shapes[i].size(); j++)
		{
			//_window.draw(_shapes[i][j]);
		}
	}

	sf::RectangleShape shape(sf::Vector2f(kShapeDimensions * _numberWidth, kShapeDimensions * _numberHeight));
	shape.setTexture(_texture);

	_window.draw(shape);

	_window.draw(_text);

	//	Create Bezier curve
	BezierCurve2D curve;
	curve.addAnchor(sf::Vector2f(0.0f, 0.0f));
	curve.addAnchor(sf::Vector2f(200.0f, 200.0f));
	curve.addAnchor(sf::Vector2f(400.0f, 200.0f));
	curve.addAnchor(sf::Vector2f(600.0f, 400.0f));

	sf::CircleShape circle(10.0f);
	shape.setFillColor(sf::Color::White);

	for (unsigned i = 0; i < 100; i++)
	{
		circle.setPosition(curve.getPoint(0.01f * i));
		_window.draw(circle);
	}

	_window.display();
}

void ModuloProduct::recalculate()
{
	//	Updating width
	if (_numberWidth < _shapes.size())
	{
		_shapes.resize(_numberWidth);
	}
	else if (_numberWidth > _shapes.size())
	{
		for (unsigned i = _shapes.size(); i < _numberWidth; i++)
		{
			_shapes.push_back(std::vector<sf::RectangleShape>());
			for (unsigned j = 0; j < _numberHeight; j++)
			{
				sf::RectangleShape shape(sf::Vector2f(kShapeDimensions, kShapeDimensions));
				shape.setPosition(i * kShapeDimensions, j * kShapeDimensions);

				_shapes[i].push_back(shape);
			}
		}
	}

	//	Updating height
	if (_shapes.size() > 0)
	{
		if (_numberHeight < _shapes[0].size())
		{
			for (unsigned i = 0; i < _shapes.size(); i++)
			{
				_shapes[i].resize(_numberHeight);
			}
		}
		else if (_numberHeight > _shapes[0].size())
		{
			for (unsigned i = 0; i < _shapes.size(); i++)
			{
				for (unsigned j = _shapes[i].size(); j < _numberHeight; j++)
				{
					sf::RectangleShape shape(sf::Vector2f(kShapeDimensions, kShapeDimensions));
					shape.setPosition(i * kShapeDimensions, j * kShapeDimensions);

					_shapes[i].push_back(shape);
				}
			}
		}
	}

	//	Create array of colours
	_textureData = std::vector<sf::Uint8>(4 * _numberWidth * _numberHeight, 0);
	delete _texture;
	_texture = new sf::Texture();
	_texture->create(_numberWidth, _numberHeight);

	//	Updating modulo
	for (unsigned i = 0; i < _numberWidth; i++)
	{
		for (unsigned j = 0; j < _numberHeight; j++)
		{
			unsigned value = (i + 1) * (j + 1);
			if (_modulo > 0)
				value %= _modulo;
			else
				value = 1;

			sf::Color colour;
			if (value == 0)
			{
				//colour = sf::Color::White;
				_textureData[j * 4 * _numberWidth + i * 4] = 255;
				_textureData[j * 4 * _numberWidth + i * 4 + 1] = 255;
				_textureData[j * 4 * _numberWidth + i * 4 + 2] = 255;
				_textureData[j * 4 * _numberWidth + i * 4 + 3] = 255;
			}
			else
			{
				//colour = sf::Color(value * (255.0 / _modulo), 0, 255 - (value * (255.0 / _modulo)));
				_textureData[j * 4 * _numberWidth + i * 4] = value * (255.0 / _modulo);
				_textureData[j * 4 * _numberWidth + i * 4 + 1] = 0;
				_textureData[j * 4 * _numberWidth + i * 4 + 2] = 255 - (value * (255.0 / _modulo));
				_textureData[j * 4 * _numberWidth + i * 4 + 3] = 255;
			}

			//_shapes[i][j].setFillColor(colour);
		}
	}

	if (_textureData.size() > 0)
	{
		_texture->update(&_textureData[0]);
	}
}

void ModuloProduct::updateText()
{
	std::stringstream stream;
	stream << "The colour of each cell represents:" << std::endl;
	stream << "\t(x * y) % modulo" << std::endl;
	stream << "Modulo is the remainder of a division." << std::endl;
	stream << "For example: 5 % 2 = 1" << std::endl;
	stream << "Because 5 / 2 = 2 remainder 1" << std::endl;
	stream << "Width: " << _numberWidth << std::endl;
	stream << "Height: " << _numberHeight << std::endl;
	stream << "Modulo: " << _modulo << std::endl;

	_text.setString(stream.str());
}