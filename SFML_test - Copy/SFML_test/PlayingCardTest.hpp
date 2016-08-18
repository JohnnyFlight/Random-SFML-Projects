#pragma once

#include "Application.hpp"

#include "PlayingCardDrawable.hpp"
#include "PlayingCardDeck.hpp"
#include "PlayingCardPile.hpp"
#include "PlayingCardLayout.hpp"

class PlayingCardTest : public Application
{
public:
	PlayingCardTest(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	void update();
	void draw();

	PlayingCardLayout _layout;

	PlayingCardDrawable _card;
	PlayingCardDeck _deck;
	PlayingCardPile _pile;

	bool _prevMouse;
};