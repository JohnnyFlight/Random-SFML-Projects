#include "Player.hpp"

namespace
{
	const unsigned kDefaultInitialHealth = 20;
}

Player::Player()
{
	_deck = new Deck();
	_hand = new Hand();

	_health = kDefaultInitialHealth;
}

Player::Player(Deck *deck)
{
	_deck = deck;
	_hand = new Hand();

	_health = kDefaultInitialHealth;
}

Player::~Player()
{
	delete _deck;
	_deck = NULL;

	delete _hand;
	_hand = NULL;
}