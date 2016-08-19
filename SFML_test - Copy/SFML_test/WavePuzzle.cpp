#include "WavePuzzle.hpp"

#include <algorithm>
#include <iostream>
#include "MathsUtility.hpp"
#include "InputManager.hpp"

namespace
{
	const unsigned kDotsPerWave = 2000;
	const unsigned kWavesToDraw = 3;
	const unsigned kWavesToGuess = 2;

	const unsigned kMaxGuesses = 3;

	const sf::Rect<unsigned> kPuzzleDimensions = sf::Rect<unsigned>(0, 0, 800, 360);
	const sf::Rect<unsigned> kGuessDimensions = sf::Rect<unsigned>(0, 360, 800, 360);

	const sf::Color kWaveColour = sf::Color::White;
	//	-max to max, so 2 * max + 1 possible values
	//	0 = sin(x)
	//	+ve = sin((1+i)*n)
	//	-ve = sin(n/(i-1))
	const unsigned kRandRange = 5;
}

WavePuzzle::WavePuzzle(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void WavePuzzle::initialise()
{
	srand(time(NULL));

	//	Create sprite to be copied into sprites container repeatedly
	sf::Sprite sprite;

	//	Create composite wave texture
	_puzzleWave.create(kPuzzleDimensions.width, kPuzzleDimensions.height);
	_puzzleWave.clear(sf::Color::Magenta);

	//	Setup composite wave sprite
	sprite.setTexture(_puzzleWave.getTexture());
	sprite.setPosition(kPuzzleDimensions.left, kPuzzleDimensions.top);
	_sprites.push_back(sprite);

	//	Setup single wave texture
	_singleWaves.create(kPuzzleDimensions.width, kPuzzleDimensions.height);
	_singleWaves.clear(sf::Color::Magenta);

	//	Setup single wave sprite
	sprite.setTexture(_singleWaves.getTexture());
	sprite.setPosition(kGuessDimensions.left, kGuessDimensions.top);
	_sprites.push_back(sprite);

	_values.resize(kWavesToGuess);

	for(unsigned i = 0; i < kMaxGuesses; i++)
	{
		_guessedWaves.push_back(new sf::RenderTexture());
		_guessedWaves[_guessedWaves.size() - 1]->create(kGuessDimensions.width, kGuessDimensions.height);
		_guessedWaves[_guessedWaves.size() - 1]->clear(sf::Color::Transparent);

		sprite.setTexture(_guessedWaves[_guessedWaves.size() - 1]->getTexture());
		_sprites.push_back(sprite);
	}

	reset();
}

void WavePuzzle::update()
{
	if (InputManager::get()->keyPressed(sf::Keyboard::R))
	{
		reset();
	}

	InputManager::get()->update();
}

void WavePuzzle::draw()
{
	_window.clear(sf::Color::Black);

	for (auto iter = _sprites.begin(); iter != _sprites.end(); iter++)
	{
		_window.draw(*iter);
	}

	_window.display();
}

void WavePuzzle::reset()
{
	generateNewWave();
	drawCompositeWave();
	drawSingleWaves();
}

void WavePuzzle::switchShowingGuesses()
{
	_showingGuesses = !_showingGuesses;

	if (_showingGuesses)
	{

	}
}

void WavePuzzle::drawCompositeWave()
{
	//	Clear RT
	_puzzleWave.clear(sf::Color::Transparent);

	//	Create circle to draw
	sf::CircleShape shape(1.0f, 4);
	shape.setFillColor(kWaveColour);

	//	For each dot to draw
	for (unsigned i = 0; i < kDotsPerWave; i++)
	{
		shape.setPosition(kPuzzleDimensions.width / static_cast<float>(kDotsPerWave) * i, kPuzzleDimensions.height / 2.0f);
		//	For each element in values
		for (unsigned j = 0, n = _values.size(); j < n; j++)
		{	
			float multiplier;
			if (_values[j] < 0.0f)
				multiplier = -1.0f / (_values[j] - 1);
			else if (_values[j] > 0.0f)
				multiplier = _values[j] + 1;
			else
				multiplier = 1.0f;

			shape.move(0.0f, (sinf((i / static_cast<float>(kDotsPerWave)) * kWavesToDraw * 2.0f * kPi * multiplier) * kPuzzleDimensions.height / 2.0f) / kWavesToGuess);
		}
		_puzzleWave.draw(shape);
	}
}

void WavePuzzle::drawSingleWaves()
{
	//	Clear RT
	_singleWaves.clear(sf::Color::Transparent);

	//	Create circle to draw
	sf::CircleShape shape(1.0f, 4);
	shape.setFillColor(kWaveColour);

	//	For each dot to draw
	for (unsigned i = 0; i < kDotsPerWave; i++)
	{
		//	For each element in values
		for (unsigned j = 0, n = _values.size(); j < n; j++)
		{	
			float multiplier;
			if (_values[j] < 0.0f)
				multiplier = -1.0f / (_values[j] - 1);
			else if (_values[j] > 0.0f)
				multiplier = _values[j] + 1;
			else
				multiplier = 1.0f;

			shape.setPosition(kGuessDimensions.width / static_cast<float>(kDotsPerWave) * i, (kGuessDimensions.height / 2.0f) + (sinf((i / static_cast<float>(kDotsPerWave)) * kWavesToDraw * 2.0f * kPi * multiplier) * kGuessDimensions.height / 2.0f) / kWavesToGuess);
			_singleWaves.draw(shape);
		}
	}
}

void WavePuzzle::generateNewWave()
{
	//	Clear vector
	std::fill(_values.begin(), _values.end(), RAND_MAX);

	int r;

	//	Populate with unique random numbers
	for (unsigned i = 0, n = _values.size(); i < n; i++)
	{
		do
		{
			r = rand() % (2 * kRandRange + 1) - kRandRange;
		}
		while (std::find(_values.begin(), _values.end(), r) != _values.end());
		_values[i] = r;
	}

	//	Sort low to high
	std::sort(_values.begin(), _values.end());

	for (auto iter = _values.begin(); iter != _values.end(); iter++)
	{
		std::cout << *iter << ", ";
	}
	std::cout << std::endl;
}

void WavePuzzle::guess()
{

}