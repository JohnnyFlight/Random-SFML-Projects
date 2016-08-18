#include "PlayingCardDeck.hpp"

#include "MathsUtility.hpp"
#include <algorithm>

namespace
{
	const unsigned kShuffleIterations = 3;
}

PlayingCardDeck::PlayingCardDeck()
{
	initialise();
}

PlayingCardDeck::PlayingCardDeck(unsigned deckNumber)
{
	addDeck(deckNumber);
	
	initialise();
}

void PlayingCardDeck::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	_emptyIndex = 0;

	if (_deck.empty() == true)
		_rect.setTexture(&_emptyTextures[_emptyIndex]);
	else 
		if (_faceUp == false)
			_rect.setTexture(&_cardBacks[_backIndex]);
		else
			_rect.setTexture(NULL);

	target.draw(_rect, states);

	if (_faceUp == true && _deck.empty() == false)
		target.draw(_text, states);
}

void PlayingCardDeck::shuffleDeck()
{
	//	For each iteration
	for (unsigned i = 0; i < kShuffleIterations; i++)
	{
		//	For each card in deck
		for (unsigned j = 0; j < _deck.size(); j++)
		{
			//	Select a random position
			unsigned position = MathsUtility::randUnsigned(0, _deck.size() - 1);
			std::iter_swap(_deck.begin() + j, _deck.begin() + position);
		}
	}
}

void PlayingCardDeck::shuffleCard(PlayingCard card)
{
	//	Select random position
	unsigned position = MathsUtility::randUnsigned(0, _deck.size());
	_deck.insert(_deck.begin() + position, card);
}

void PlayingCardDeck::addCard(PlayingCard card)
{
	_deck.push_back(card);
}

void PlayingCardDeck::addDeck(unsigned number)
{
	addSuitDeck(PlayingCard::Suit::Heart, number);
	addSuitDeck(PlayingCard::Suit::Diamond, number);
	addSuitDeck(PlayingCard::Suit::Spade, number);
	addSuitDeck(PlayingCard::Suit::Club, number);
}

void PlayingCardDeck::addSuitDeck(PlayingCard::Suit suit, unsigned number)
{
	for (unsigned i = 0; i < number; i++)
	{
		for (unsigned j = 0; j < 13; j++)
		{
			_deck.push_back(PlayingCard(suit, j + 1));
		}
	}
}

void PlayingCardDeck::removeSuit(PlayingCard::Suit suit, unsigned instances, bool random)
{

}

void PlayingCardDeck::removeCard(PlayingCard card, unsigned instances, bool random)
{

}

void PlayingCardDeck::removePip(unsigned pip, unsigned instances, bool random)
{

}

PlayingCard PlayingCardDeck::drawCard()
{
	PlayingCard card = *(_deck.end() - 1);
	_deck.pop_back();
	return card;
}

void PlayingCardDeck::setEmptyTexture(unsigned index)
{
	if (index < _emptyTextures.size())
		_emptyIndex = index;
}