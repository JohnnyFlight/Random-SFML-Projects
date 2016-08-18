#include "WavePuzzle.hpp"

#include <algorithm>
#include "MathsUtility.hpp"

namespace
{
	const unsigned kDotsPerWave = 1000;
	const unsigned kWavesToDraw = 1;
	const unsigned kWavesToGuess = 3;

	const unsigned kMaxGuesses = 3;

	const sf::Rect<unsigned> kPuzzleDimensions = sf::Rect<unsigned>(50, 50, 600, 200);
	const sf::Rect<unsigned> kGuessDimensions = sf::Rect<unsigned>(50, 350, 600, 200);

	const sf::Color kWaveColour = sf::Color::White;
	//	-max to max, so 2 * max + 1 possible values
	//	0 = sin(x)
	//	+ve = sin((1+i)*n)
	//	-ve = sin(n/(i-1))
	const unsigned kRandRange = 2;
}

WavePuzzle::WavePuzzle(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void WavePuzzle::initialise()
{
	srand(time(NULL));

	sf::Sprite sprite;

	_puzzleWave.create(kPuzzleDimensions.width, kPuzzleDimensions.height);
	_puzzleWave.clear(sf::Color::Magenta);

	sprite.setTexture(_puzzleWave.getTexture());
	sprite.setPosition(kPuzzleDimensions.left, kPuzzleDimensions.top);
	_sprites.push_back(sprite);

	sprite.setPosition(kGuessDimensions.left, kGuessDimensions.top);

	_values.resize(kWavesToGuess);

	for(unsigned i = 0; i < kMaxGuesses; i++)
	{
		_guessedWaves.push_back(new sf::RenderTexture());
		_guessedWaves[_guessedWaves.size() - 1]->create(kGuessDimensions.width, kGuessDimensions.height);
		_guessedWaves[_guessedWaves.size() - 1]->clear(sf::Color::Magenta);

		sprite.setTexture(_guessedWaves[_guessedWaves.size() - 1]->getTexture());
		_sprites.push_back(sprite);
	}

	generateNewWave();
	drawWaves();
}

void WavePuzzle::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		generateNewWave();
		drawWaves();
	}
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

void WavePuzzle::drawWaves()
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
}

void WavePuzzle::guess()
{

}