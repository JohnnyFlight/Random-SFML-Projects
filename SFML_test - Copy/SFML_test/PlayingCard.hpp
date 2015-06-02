#pragma once

#include <string>

class PlayingCard
{
public:
	enum Suit { Heart, Diamond, Spade, Club };

	PlayingCard();
	PlayingCard(Suit suit, unsigned pip);

	inline Suit suit() { return _suit; }
	inline unsigned pip() { return _pip; }
	
	std::string suitString();
	std::string pipString();

	inline bool isRed() { return (_suit == Suit::Heart) || (_suit == Suit::Diamond); }
	inline bool isBlack() { return (_suit == Suit::Spade) || (_suit == Suit::Club); }

private:

	Suit _suit;
	unsigned _pip;

};