#include "PlayingCard.hpp"

namespace
{
	const PlayingCard::Suit kDefaultSuit = PlayingCard::Suit::Spade;
	const unsigned kDefaultPip = 1;
}

PlayingCard::PlayingCard()
{
	_suit = kDefaultSuit;
	_pip = kDefaultPip;
}

PlayingCard::PlayingCard(Suit suit, unsigned pip)
{
	_suit = suit;
	_pip = pip;
}

std::string PlayingCard::suitString()
{
	switch (_suit)
	{
	case Suit::Heart:
		return "H";
	case Suit::Diamond:
		return "D";
	case Suit::Spade:
		return "S";
	case Suit::Club:
		return "C";
	}

	return "_";
}

std::string PlayingCard::pipString()
{
	switch (_pip)
	{
	case 1:
		return "A";
	case 11:
		return "J";
	case 12:
		return "Q";
	case 13:
		return "K";
	default:
		return std::to_string((unsigned long long)_pip);
	}

	return "_";
}