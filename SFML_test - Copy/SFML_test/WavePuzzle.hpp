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

	sf::RenderTexture _puzzleWave;
	std::vector<sf::RenderTexture*> _guessedWaves;

	void update();
	void draw();

	void drawWaves();

	void generateNewWave();
	void guess();
};