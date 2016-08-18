#pragma once

#include <string>

class PlayingCard
{
public:
	enum Suit { Heart, Diamond, Spade, Club, None };

	PlayingCard();
	PlayingCard(Suit suit, unsigned pip);

	inline Suit suit() { return _suit; }
	inline void setSuit(Suit suit) { _suit = suit; }

	inline unsigned pip() { return _pip; }
	inline void setPip(unsigned pip) { if (pip > 0 && pip < 13) _pip = pip; }
	
	std::string suitString();
	std::string pipString();

	inline bool isRed() { return (_suit == Suit::Heart) || (_suit == Suit::Diamond); }
	inline bool isBlack() { return (_suit == Suit::Spade) || (_suit == Suit::Club); }

	inline bool isEmpty() { return (_pip == 0) || (_suit == Suit::None); }

private:

	Suit _suit;
	unsigned _pip;

};