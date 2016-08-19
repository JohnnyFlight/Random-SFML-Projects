#pragma once
#include "Application.hpp"

#include <vector>
#include <stack>
#include <memory>

class WavePuzzle : public Application
{
public:
	WavePuzzle(unsigned width, unsigned height, std::string name);

	void initialise();

protected:
	//	Font for drawing text
	sf::Font _font;

	//	Showing guesses
	sf::Text _guessText;

	enum State
	{
		Menu,
		Game
	};

	State _state;

	unsigned _guessesRemaining;
	unsigned _guessIndex;
	
	std::stack<sf::Drawable*> _drawables;

	std::vector<int> _values;
	std::vector<int> _guess;
	std::vector<std::vector<int> > _prevGuesses;

	unsigned _prevGuessIndex;

	sf::RenderTexture _puzzleWave;
	sf::Sprite _puzzleWaveSprite;

	sf::RenderTexture _singleWaves;
	sf::Sprite _singleWavesSprite;

	std::vector<sf::RenderTexture*> _guessedWaves;

	bool _showingGuesses;

	void update();
	void updateMenu();
	void updateGame();

	void draw();

	void reset();
	void switchShowingGuesses();

	void drawCompositeWave(std::vector<int>* values, sf::RenderTexture* target = nullptr);
	void drawSingleWaves();

	void generateNewWave();
	void guess();
};