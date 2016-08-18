#include "PlayingCard.hpp"

namespace
{
	const PlayingCard::Suit kDefaultSuit = PlayingCard::Suit::None;
	const unsigned kDefaultPip = 0;
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
	default:
		return "_";
	}
}

std::string PlayingCard::pipString()
{
	switch (_pip)
	{
	case 0:
		return "_";
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
}