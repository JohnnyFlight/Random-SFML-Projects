#pragma once

#include "PlayingCardDrawable.hpp"
#include <vector>

class PlayingCardPile
{
public:
	PlayingCardPile();
	~PlayingCardPile();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	int cardClicked(unsigned x, unsigned y);
	void addCard(PlayingCard card);
	PlayingCard getCard(unsigned index);
	PlayingCardDrawable getCardDrawable(unsigned index);
	PlayingCard removeCard(unsigned index);

private:
	void setupDrawables();

	unsigned _cardsVisible;

	unsigned _emptyIndex;

	sf::Vector2f _position;
	sf::Vector2f _offset;

	std::vector<PlayingCard> _cards;
	std::vector<PlayingCardDrawable> _drawables;

};