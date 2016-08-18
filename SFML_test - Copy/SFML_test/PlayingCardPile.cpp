#include "PlayingCardPile.hpp"

namespace
{
	const unsigned kDefaultCardsVisible = 5;
	const sf::Vector2f kDefaultPosition = sf::Vector2f(400.0f, 200.0f);
	const sf::Vector2f kDefaultOffset = sf::Vector2f(25.0f, 0.0f);
}

PlayingCardPile::PlayingCardPile()
{
	_cardsVisible = kDefaultCardsVisible;

	_emptyIndex = 0;

	_position = kDefaultPosition;
	_offset = kDefaultOffset;

	setupDrawables();
}

PlayingCardPile::~PlayingCardPile()
{

}

void PlayingCardPile::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	for (unsigned i = 0; i < _drawables.size(); i++)
	{
		_drawables[i].draw(target);
	}
}

int PlayingCardPile::cardClicked(unsigned x, unsigned y)
{
	if (_cards.size() == 0) return -1;

	//	Go backwards checking clicks
	for (unsigned i = _drawables.size() - 1; i < _drawables.size(); i--)
	{
		if (_drawables[i].clicked(x, y) == true)
			return i;
	}

	return -1;
}

void PlayingCardPile::addCard(PlayingCard card)
{
	_cards.push_back(card);

	setupDrawables();
}

PlayingCard PlayingCardPile::getCard(unsigned index)
{
	if (_cards.size() < index)
		return _cards[index];

	return PlayingCard();
}

PlayingCardDrawable PlayingCardPile::getCardDrawable(unsigned index)
{
	if (_cards.size() < index)
		return _drawables[index];
}

void PlayingCardPile::setupDrawables()
{
	_drawables.clear();
	
	//	Create drawables
	unsigned visibleCards = (_cardsVisible < _cards.size())?(_cardsVisible):(_cards.size());
	for (unsigned i = 0; i < visibleCards; i++)
	{
		PlayingCardDrawable drawable(_cards[_cards.size() - 1 - i]);
		drawable.setPosition(_position + (_offset * (float)i));
		drawable.setOrientation(true);
		_drawables.push_back(drawable);
	}

	if (_drawables.empty() == true)
	{
		//	Add a blank card with empty texture
		PlayingCardDrawable empty = PlayingCardDrawable();
		empty.setPosition(_position);

		_drawables.push_back(empty);
	}
}