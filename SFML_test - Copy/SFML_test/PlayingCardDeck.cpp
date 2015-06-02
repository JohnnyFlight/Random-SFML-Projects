#include "PlayingCardDeck.hpp"

#include "MathsUtility.hpp"
#include <algorithm>

namespace
{
	const unsigned kShuffleIterations = 3;
}

PlayingCardDeck::PlayingCardDeck()
{

}

PlayingCardDeck::PlayingCardDeck(unsigned deckNumber)
{
	addDeck(deckNumber);
}

void PlayingCardDeck::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (_deck.empty() == true)
		setTexture(_empty);
	else 
		if (_faceUp == false)
			setTexture(_back);
		else
			setTexture(NULL);

	target.draw(*this, states);

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

void PlayingCardDeck::setEmptyTexture(sf::Texture *texture)
{
	_empty = texture;
}