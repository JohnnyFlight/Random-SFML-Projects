#include "WavePuzzle.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "MathsUtility.hpp"
#include "InputManager.hpp"

namespace
{
	const unsigned kDotsPerWave = 4000;
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

	const unsigned kFontSize = 20;
	const sf::Vector2f kGuessTextPosition = sf::Vector2f(800.0f, 0.0f);
}

WavePuzzle::WavePuzzle(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void WavePuzzle::initialise()
{
	//	Seed rand()
	srand(time(NULL));

	//	Load font
	if (_font.loadFromFile("comic.ttf"))
	{
		//	Apply font to text
		_guessText.setFont(_font);

		//	Initialise text
		_guessText.setCharacterSize(kFontSize);
		_guessText.setPosition(kGuessTextPosition);
	}

	//	

	_state = State::Game;

	//	Create composite wave texture
	_puzzleWave.create(kPuzzleDimensions.width, kPuzzleDimensions.height);
	_puzzleWave.clear(sf::Color::Magenta);

	//	Setup composite wave sprite
	_puzzleWaveSprite.setTexture(_puzzleWave.getTexture());
	_puzzleWaveSprite.setPosition(kPuzzleDimensions.left, kPuzzleDimensions.top);

	//	Setup single wave texture
	_singleWaves.create(kPuzzleDimensions.width, kPuzzleDimensions.height);
	_singleWaves.clear(sf::Color::Magenta);

	//	Setup single wave sprite
	_singleWavesSprite.setTexture(_singleWaves.getTexture());
	_singleWavesSprite.setPosition(kGuessDimensions.left, kGuessDimensions.top);

	_values.resize(kWavesToGuess);
	_guess.resize(kWavesToGuess);

	_guessIndex = 0;
	_prevGuessIndex = 0;
	_showingGuesses = false;
	_guessesRemaining = kMaxGuesses;

	reset();
}

void WavePuzzle::update()
{
	if (InputManager::get()->keyPressed(sf::Keyboard::Escape))
	{
		quit();
		return;
	}

	switch(_state)
	{
	case State::Menu:
		updateMenu();
		break;
	case State::Game:
		updateGame();
		break;
	}

	InputManager::get()->update();
}

void WavePuzzle::updateMenu()
{

}

void WavePuzzle::updateGame()
{
	//	Resetting game
	if (InputManager::get()->keyPressed(sf::Keyboard::R))
	{
		reset();
	}

	std::stringstream stream;

	stream << "Guess: ";
	for (unsigned i = 0, n = _guess.size(); i < n; i++)
	{
		stream << ((i == _guessIndex)?("*"):(" "));
		stream << _guess[i] << ((i == n-1)?(""):(", "));
	}
	stream << std::endl << "Guesses remaining: " << _guessesRemaining << std::endl;
	
	//	Only allow guess to be made/modified if not showing guess
	if (!_showingGuesses)
	{
		//	Modifying guess
		if (InputManager::get()->keyPressed(sf::Keyboard::Left))
		{
			_guessIndex = (_guessIndex == 0)?(kWavesToGuess - 1):(_guessIndex - 1);
		}
		if (InputManager::get()->keyPressed(sf::Keyboard::Right))
		{
			_guessIndex = (_guessIndex == kWavesToGuess - 1)?(0):(_guessIndex + 1);
		}
		if (InputManager::get()->keyPressed(sf::Keyboard::Up))
		{
			_guess[_guessIndex] += (_guess[_guessIndex] + kRandRange < 2 * kRandRange)?(1):(0);
			drawSingleWaves();
		}
		if (InputManager::get()->keyPressed(sf::Keyboard::Down))
		{
			_guess[_guessIndex] -= (_guess[_guessIndex] + kRandRange > 0)?(1):(0);
			drawSingleWaves();
		}

		//	Submit guess
		if (InputManager::get()->keyPressed(sf::Keyboard::G))
		{
			guess();
		}
	}
	else
	{
		bool change = false;

		//	Allow user to navigate guesses with left and right
		if (InputManager::get()->keyPressed(sf::Keyboard::Left))
		{
			_guessIndex = (_guessIndex)?(_guessIndex-1):(_guessedWaves.size()-1);
			change = true;
		}
		if (InputManager::get()->keyPressed(sf::Keyboard::Right))
		{
			_guessIndex = (_guessIndex < _guessedWaves.size()-1)?(_guessIndex+1):(0);
			change = true;
		}

		if (change == true)
		{
			_singleWavesSprite.setTexture(_guessedWaves[_guessIndex]->getTexture());
		}
	}

	//	Showing/hiding previous guesses
	if (InputManager::get()->keyPressed(sf::Keyboard::Return))
	{
		switchShowingGuesses();
	}

	_guessText.setString(stream.str());

	//	Add things to be drawn
	_drawables.push(&_puzzleWaveSprite);
	_drawables.push(&_singleWavesSprite);
	_drawables.push(&_guessText);
}

void WavePuzzle::draw()
{
	_window.clear(sf::Color::Black);

	while (!_drawables.empty())
	{
		_window.draw(*_drawables.top());
		_drawables.pop();
	}

	_window.display();
}

void WavePuzzle::reset()
{
	//	Reset guesses
	for (auto iter = _guess.begin(); iter != _guess.end(); iter++)
	{
		*iter = 0;
	}

	_guessesRemaining = kMaxGuesses;

	generateNewWave();
	drawCompositeWave(&_values);
	drawSingleWaves();
}

void WavePuzzle::switchShowingGuesses()
{
	//	Only switch if there are guesses to show
	if (!_showingGuesses)
	{
		if (!_prevGuesses.empty())
		{
			//	Flip flag
			_showingGuesses = true;

			//	Show last guess
			_guessIndex = _guessedWaves.size() - 1;
			_singleWavesSprite.setTexture(_guessedWaves[_guessIndex]->getTexture());
		}
		else
		{
			std::cout << "No guesses made yet" << std::endl;
		}
	}
	else
	{
		_guessIndex = 0;
		_showingGuesses = false;
		
		_singleWavesSprite.setTexture(_singleWaves.getTexture());
	}
}

void WavePuzzle::drawCompositeWave(std::vector<int>* values, sf::RenderTexture* target)
{
	if (target == nullptr)
	{
		target = &_puzzleWave;
	}

	//	Clear RT
	target->clear(sf::Color::Transparent);

	//	Create circle to draw
	sf::CircleShape shape(1.0f, 4);
	shape.setFillColor(kWaveColour);

	//	For each dot to draw
	for (unsigned i = 0; i < kDotsPerWave; i++)
	{
		shape.setPosition(kPuzzleDimensions.width / static_cast<float>(kDotsPerWave) * i, kPuzzleDimensions.height / 2.0f);
		//	For each element in values
		for (unsigned j = 0, n = values->size(); j < n; j++)
		{	
			float multiplier;
			if ((*values)[j] < 0.0f)
				multiplier = -1.0f / ((*values)[j] - 1.0f);
			else if ((*values)[j] > 0.0f)
				multiplier = (*values)[j] + 1.0f;
			else
				multiplier = 1.0f;

			shape.move(0.0f, (sinf((i / static_cast<float>(kDotsPerWave)) * kWavesToDraw * 2.0f * kPi * multiplier) * kPuzzleDimensions.height / 2.0f) / kWavesToGuess);
		}
		target->draw(shape);
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
		for (unsigned j = 0, n = _guess.size(); j < n; j++)
		{	
			float multiplier;
			if (_guess[j] < 0.0f)
				multiplier = -1.0f / (_guess[j] - 1);
			else if (_guess[j] > 0.0f)
				multiplier = _guess[j] + 1;
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
	if (_guessesRemaining)
	{
		_guessesRemaining--;
	}
	else
	{
		std::cout << "No guesses remaining" << std::endl;
		return;
	}

	//	Copy guesses
	std::vector<int> copy = _guess;

	//	Sort copy
	std::sort(copy.begin(), copy.end());

	//	Store guess
	_prevGuesses.push_back(copy);

	//	Create new guess RT
	_guessedWaves.push_back(new sf::RenderTexture());
	_guessedWaves[_guessedWaves.size()-1]->create(kGuessDimensions.width, kGuessDimensions.height);

	//	Render guess
	drawCompositeWave(&_guess, _guessedWaves[_guessedWaves.size()-1]);

	//	Show guess
	switchShowingGuesses();

	//	Compare with solution
	for (unsigned i = 0, n = _values.size(); i < n; i++)
	{
		//	If mismatch return
		if (_values[i] != copy[i])
		{
			std::cout << "Guess wrong" << std::endl;
			return;
		}
	}

	//	No mismatch
	std::cout << "Guess right" << std::endl;
}