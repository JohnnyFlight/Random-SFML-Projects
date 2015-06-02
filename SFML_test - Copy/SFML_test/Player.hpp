#pragma once

#include "Deck.hpp"
#include "Hand.hpp"

class Player
{
public:
	Player();
	Player(Deck *deck);
	~Player();

	inline Deck *getDeck() { return _deck; }
	inline Hand *getHand() { return _hand; }
	inline Tile::Faction getFaction() { return _faction; }
	inline void setFaction(Tile::Faction faction) { _faction = faction; }

	inline unsigned getHealth() { return _health; }
	inline void removeHealth(unsigned health) { _health -= (health > _health)?(_health):(health); }
	inline bool isDead() { return _health == 0; }
protected:
	Deck *_deck;
	Hand *_hand;
	Tile::Faction _faction;

	unsigned _health;
private:

};