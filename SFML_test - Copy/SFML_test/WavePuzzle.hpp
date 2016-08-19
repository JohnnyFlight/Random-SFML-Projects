#pragma once
#include "Application.hpp"

#include <vector>

class WavePuzzle : public Application
{
public:
	WavePuzzle(unsigned width, unsigned height, std::string name);

	void initialise();

protected:
	unsigned _guessesRemaining;
	
	std::vector<sf::Sprite> _sprites;
	std::vector<int> _values;
	std::vector<int> _guesses;

	sf::RenderTexture _puzzleWave;
	sf::RenderTexture _singleWaves;
	std::vector<sf::RenderTexture*> _guessedWaves;

	bool _showingGuesses;

	void update();
	void draw();

	void reset();
	void switchShowingGuesses();

	void drawCompositeWave();
	void drawSingleWaves();

	void generateNewWave();
	void guess();
};