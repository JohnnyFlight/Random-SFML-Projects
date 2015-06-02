#pragma once

#include "Deck.hpp"

class DeckGenerator
{
public:
	static Deck *outpostDeck();
	static Deck *hegemonyDeck();
	static Deck *molochDeck();
	static Deck *doomsdayDeck();
	static Deck *borgoDeck();
};