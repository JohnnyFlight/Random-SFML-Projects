#pragma once

#include "Application.hpp"

#include "PlayingCardManager.hpp"
#include "PlayingCardDrawable.hpp"
#include "PlayingCardDeck.hpp"

class PlayingCardTest : public Application
{
public:
	PlayingCardTest(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	void update();
	void draw();

	PlayingCardManager _manager;
	PlayingCardDrawable _card;
	PlayingCardDeck _deck;

	bool _prevMouse;
};