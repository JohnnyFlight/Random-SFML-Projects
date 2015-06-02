#include "MandelbrotTest.hpp"

#include <iostream>
#include <sstream>

#include <complex>
#include "VectorUtility.hpp"

namespace
{
	const sf::Vector2u kDefaultDimensions = sf::Vector2u(1080, 720);

	const sf::Vector2f kDefaultRegionPos = sf::Vector2f(-2.0f, -1.0f);
	const sf::Vector2f kDefaultRegionDimensions = sf::Vector2f(3.0f, 2.0f);

	const sf::Rect<float> kDefaultRegion = sf::Rect<float>(kDefaultRegionPos, kDefaultRegionDimensions);
	const unsigned kRegionsWide = 3;
	const unsigned kRegionsHigh = 3;

	const unsigned kIterationNumber = 1000;

	const float kHighlightThreshold = 20.0f;
}

MandelbrotTest::MandelbrotTest(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void MandelbrotTest::initialise()
{
	_dimensions = kDefaultDimensions;
	_region = kDefaultRegion;

	_iterationNumber = kIterationNumber;

	_texture.create(_dimensions.x, _dimensions.y);

	//	Fill texture data with cyan
	_textureData = std::vector<sf::Uint8>(_dimensions.x * _dimensions.y * 4, 255);

	_shape = sf::RectangleShape(sf::Vector2f(_dimensions));
	_shape.setTexture(&_texture);

	_highlightBox.setFillColor(sf::Color::Transparent);
	_highlightBox.setOutlineColor(sf::Color::Magenta);
	_highlightBox.setOutlineThickness(1.0f);

	if (_font.loadFromFile("comic.ttf") == true)
	{
		_infoText.setFont(_font);
		_infoText.setColor(sf::Color::White);
	}

	initialiseRegions();

	_prevClick = false;

	//	Try doing mandelbrot here?
	recalculate();
}

void MandelbrotTest::initialiseRegions()
{
	_subDimensions.resize(kRegionsWide, std::vector<sf::Rect<unsigned> >());
	_regionShapes.resize(kRegionsWide, std::vector<sf::RectangleShape>());
	for (unsigned i = 0; i < kRegionsWide; i++)
	{
		_subDimensions[i].resize(kRegionsHigh, sf::Rect<unsigned>(sf::Vector2u(0, 0), sf::Vector2u(_dimensions.x / kRegionsWide, _dimensions.y / kRegionsWide)));
		_regionShapes[i].resize(kRegionsHigh, sf::RectangleShape(sf::Vector2f(_dimensions.x / kRegionsWide, _dimensions.y / kRegionsWide)));
		for (unsigned j = 0; j < kRegionsHigh; j++)
		{
			_subDimensions[i][j].left = i * _subDimensions[i][j].width;
			_subDimensions[i][j].top = j * _subDimensions[i][j].height;

			_regionShapes[i][j].setPosition(i * _subDimensions[i][j].width, j * _subDimensions[i][j].height);
			_regionShapes[i][j].setFillColor(sf::Color::Transparent);
			_regionShapes[i][j].setOutlineColor(sf::Color::Magenta);
			_regionShapes[i][j].setOutlineThickness(1.0f);
		}
	}

	_subRegions.resize(kRegionsWide, std::vector<sf::Rect<float> >());
	for (unsigned i = 0; i < kRegionsWide; i++)
	{
		_subRegions[i].resize(kRegionsHigh, sf::Rect<float>());
	}

	_threads.resize(kRegionsWide, std::vector<sf::Thread*>());
	for (unsigned i = 0; i < kRegionsWide; i++)
	{
		_threads[i].resize(kRegionsHigh, NULL);
	}

	recalculateRegions();
}

void MandelbrotTest::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !_prevR)
	{
		_region = kDefaultRegion;
		recalculateRegions();
		recalculate();
	}

	//	Use WASD to move around
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !_prevW)
	{
		_region.top -= _region.height / kRegionsHigh;
		recalculateRegions();
		recalculate();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !_prevA)
	{
		_region.left -= _region.width / kRegionsWide;
		recalculateRegions();
		recalculate();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !_prevS)
	{
		_region.top += _region.height / kRegionsHigh;
		recalculateRegions();
		recalculate();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !_prevD)
	{
		_region.left += _region.width / kRegionsWide;
		recalculateRegions();
		recalculate();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//	Get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

		//	Update highlight box position
		//	Depending on position of mouse point to click point
		//	Change dimensions of box accordingly

		sf::Vector2f boxPos;
		if (mousePos.x < _clickPosition.x)
			boxPos.x = mousePos.x;
		else
			boxPos.x = _clickPosition.x;

		if (mousePos.y < _clickPosition.y)
			boxPos.y = mousePos.y;
		else
			boxPos.y = _clickPosition.y;

		_highlightBox.setPosition(boxPos);
		_highlightBox.setSize(sf::Vector2f(abs(mousePos.x - _clickPosition.x), abs(mousePos.y - _clickPosition.y)));

		if (!_prevClick)
		{
			//	If click then create box at position
			_highlightBox.setPosition(sf::Vector2f(mousePos));
			_highlightBox.setSize(sf::Vector2f(0.0f, 0.0f));

			//	And set position
			_clickPosition = sf::Vector2f(mousePos);
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && _prevClick)
	{
		//	Get position
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

		if (VectorUtility::sqrMagnitude(_highlightBox.getSize()) > kHighlightThreshold * kHighlightThreshold)
		{
			sf::Vector2f relativePosition = _highlightBox.getPosition();
			sf::Vector2f relativeSize = _highlightBox.getSize();

			relativePosition.x = _region.left + _region.width * (_highlightBox.getPosition().x / kDefaultDimensions.x);
			relativePosition.y = _region.top + _region.height * (_highlightBox.getPosition().y / kDefaultDimensions.y);
			
			//	Find out which of the two box edges is largest compared to dimension size
			//	Scale region by both sides
			sf::Vector2f relativeDimensions(relativeSize.x / kDefaultDimensions.x, relativeSize.y / kDefaultDimensions.y);
			if (relativeDimensions.x > relativeDimensions.y)
			{
				relativeSize.x = _region.width * relativeDimensions.x;
				relativeSize.y = _region.height * relativeDimensions.x;
			}
			else
			{
				relativeSize.x = _region.width * relativeDimensions.y;
				relativeSize.y = _region.height * relativeDimensions.y;
			}


			_region = sf::Rect<float>(relativePosition, relativeSize);

			recalculateRegions();
			recalculate();
		}
		else
		{
			for (unsigned i = 0; i < kRegionsWide; i++)
			{
				for (unsigned j = 0; j < kRegionsHigh; j++)
				{
					//	Check if sub-dimension is clicked
					//	Resize based on appropriate region
					if (_subDimensions[i][j].contains(sf::Vector2u(mousePos)))
					{
						_region = _subRegions[i][j];
						recalculateRegions();
						recalculate();
					}
				}
			}
		}
	}

	//	Right click zoom out
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !_prevClick)
	{
		_region.left -= _region.width;
		_region.top -= _region.height;

		_region.width *= kRegionsWide;
		_region.height *= kRegionsHigh;
		recalculateRegions();
		recalculate();
	}

	_prevClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	_prevR = sf::Keyboard::isKeyPressed(sf::Keyboard::R);

	_prevW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	_prevA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	_prevS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	_prevD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void MandelbrotTest::draw()
{
	_window.clear(sf::Color::Black);

	_window.draw(_shape);

	for (unsigned i = 0; i < kRegionsWide; i++)
	{
		for (unsigned j = 0; j < kRegionsHigh; j++)
		{
			_window.draw(_regionShapes[i][j]);
		}
	}

	if (_prevClick)
	{
		_window.draw(_highlightBox);
	}

	_window.draw(_infoText);

	_window.display();
}

void MandelbrotTest::recalculate()
{
	sf::Clock clock;
	clock.restart();

	//	Initialise each thread
	CalculateParams p;
			
	p.pixelData = &_textureData;
	p.iterationNumber = _iterationNumber;
	p.rect = _region;

	for (unsigned i = 0; i < _threads.size(); i++)
	{
		for (unsigned j = 0; j < _threads[i].size(); j++)
		{
			p.pixels = _subDimensions[i][j];

			//	Create if uninitialised
			if (_threads[i][j] != NULL)
				delete _threads[i][j];

			_threads[i][j] = new sf::Thread(&MandelbrotTest::calculate, p);
			_threads[i][j]->launch();
		}
	}
	
	for (unsigned i = 0; i < _threads.size(); i++)
	{
		for (unsigned j = 0; j < _threads[i].size(); j++)
		{
			_threads[i][j]->wait();
		}
	}

	if (_textureData.empty() == false)
	{
		_texture.update(&_textureData[0]);
	}

	_computeTime = clock.getElapsedTime().asSeconds();

	updateText();
}

void MandelbrotTest::calculate(CalculateParams params)
{
	for (unsigned i = params.pixels.left; i < (params.pixels.left + params.pixels.width); i++)
	{
		for (unsigned j = params.pixels.top; j < (params.pixels.top + params.pixels.height); j++)
		{
			//	Scale i and j so that -2 < i < 1 and -1 < j < 1
	//		float real = ((float)i / (float)_dimensions.x) * _region.width + _region.left;
	//		float imag = ((float)j / (float)_dimensions.y) * _region.height + _region.top;
			float real = ((float)i / (float)kDefaultDimensions.x) * params.rect.width + params.rect.left;
			float imag = ((float)j / (float)kDefaultDimensions.y) * params.rect.height + params.rect.top;

			std::complex<float> c(real, imag);
			std::complex<float> z(0.0f, 0.0f);

			unsigned iter = 0;
			while(std::norm(z) < 4.0f && iter < params.iterationNumber)
			{
				z = z * z + c;
				iter++;
			}

			float norm = std::norm(z);
			if (norm < 4.0f)
			{
				//	Point is in the set, make it black
				(*params.pixelData)[j * kDefaultDimensions.x * 4 + i * 4 + 0] = 0;
				(*params.pixelData)[j * kDefaultDimensions.x * 4 + i * 4 + 1] = 0;
				(*params.pixelData)[j * kDefaultDimensions.x * 4 + i * 4 + 2] = 0;
			}
			else
			{
				unsigned value = ((float)iter / kIterationNumber) * (256 * 256);
				(*params.pixelData)[j * kDefaultDimensions.x * 4 + i * 4 + 0] = value % 256;
				(*params.pixelData)[j * kDefaultDimensions.x * 4 + i * 4 + 1] = (value / 256) % 256;
				(*params.pixelData)[j * kDefaultDimensions.x * 4 + i * 4 + 2] = 255;
			}
		}
	}
}

void MandelbrotTest::recalculateRegions()
{
	//	Create sub-region
	sf::Rect<float> subRegion = _region;
	subRegion.width /= kRegionsWide;
	subRegion.height /= kRegionsHigh;

	for (unsigned i = 0; i < kRegionsWide; i++)
	{
		for (unsigned j = 0; j < kRegionsHigh; j++)
		{
			_subRegions[i][j] = subRegion;
			_subRegions[i][j].left += subRegion.width * i;
			_subRegions[i][j].top += subRegion.height * j;
		}
	}
}

void MandelbrotTest::updateText()
{
	//	Create sstream
	std::stringstream stream;

	//	Push info into sstream
	stream << "Number of iterations: " << _iterationNumber << std::endl;
	stream << "Time to compute: " << _computeTime << " seconds." << std::endl;
	stream << "Average time to compute pixel: " << _computeTime / (_dimensions.x * _dimensions.y) << " seconds." << std::endl;
	stream << "Computed region top-left: " << _region.left << ", " << _region.top << std::endl;
	stream << "Computed region dimensions: " << _region.width << ", " << _region.height << std::endl << std::endl;

	//	Push sstream into text
	_infoText.setString(stream.str());
}