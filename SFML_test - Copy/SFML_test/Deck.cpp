#include "Deck.hpp"

#include <ctime>

namespace
{
	const unsigned kShuffleIterations = 3;
}

Deck::Deck()
{

}

Deck::~Deck()
{

}

Tile Deck::peek()
{
	return _tiles.top();
}

Tile Deck::draw()
{
	Tile tile = _tiles.top();
	_tiles.pop();
	return tile;
}

bool Deck::isEmpty()
{
	return _tiles.empty();
}

void Deck::shuffle()
{
	//	No idea how to do this.
	srand(time(NULL));

	//	Create vector to store tiles
	std::vector<Tile> shuffleContainer;

	while (_tiles.empty() == false)
	{
		shuffleContainer.push_back(_tiles.top());
		_tiles.pop();
	}

	//	For the number of iterations
	for (unsigned i = 0; i < kShuffleIterations; i++)
	{
		//	For each entry in the shuffle container
		for (unsigned j = 0; j < shuffleContainer.size(); j++)
		{
			//	Pick a random entry in the container
			unsigned switchValue = rand() % shuffleContainer.size();

			//	Swap j and switch value
			std::swap(shuffleContainer[j], shuffleContainer[switchValue]);
		}
	}

	//	Empty shuffleContainer back into stack
	while (shuffleContainer.empty() == false)
	{
		_tiles.push(*(shuffleContainer.end() - 1));
		shuffleContainer.pop_back();
	}
}