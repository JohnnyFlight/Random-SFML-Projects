#pragma once

#include "PlayingCardDrawable.hpp"

//	Would ideally use a stack but
//	this makes it easier to shuffle
#include <vector>

class PlayingCardDeck : public PlayingCardDrawable
{
public:
	PlayingCardDeck();
	//	Creates a deck with n number of cards
	PlayingCardDeck(unsigned deckNumber);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	//	Shuffles whole deck
	void shuffleDeck();
	//	Places a card randomly in the deck
	void shuffleCard(PlayingCard card);
	//	Places card on the top of the deck
	void addCard(PlayingCard card);

	void addDeck(unsigned number);

	//	Some additional functions for creating
	//	Custom decks
	void addSuitDeck(PlayingCard::Suit suit, unsigned number);

	//	Removing cards
	void removeSuit(PlayingCard::Suit suit, unsigned instances = 0, bool random = false);
	void removeCard(PlayingCard card, unsigned instances = 0, bool random = false);
	void removePip(unsigned pip, unsigned instances = 0, bool random = false);

	PlayingCard drawCard();

	void setEmptyTexture(unsigned index);

	inline unsigned count() { return _deck.size(); }

protected:
	std::vector<PlayingCard> _deck;

	unsigned _emptyIndex;

};