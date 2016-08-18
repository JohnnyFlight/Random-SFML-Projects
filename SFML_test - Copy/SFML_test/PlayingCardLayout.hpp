#pragma once

#include "PlayingCard.hpp"
#include "PlayingCardDrawable.hpp"
#include "PlayingCardDeck.hpp"
#include "PlayingCardPile.hpp"

#include <vector>
#include <map>

class PlayingCardLayout
{
public:
	PlayingCardLayout();

	void clear();
	void loadFromFile(std::string fileName);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

private:
	std::map<std::string, PlayingCardDrawable> _cards;

	//std::vector<PlayingCardDrawable> _cards;
	std::vector<PlayingCardDeck> _decks;
	std::vector<PlayingCardPile> _piles;
	
	void handleCardToken(std::vector<std::vector<std::string> >::iterator& iter, std::vector<std::vector<std::string> >::iterator& end);
	void handleDeckToken(std::vector<std::vector<std::string> >::iterator& iter, std::vector<std::vector<std::string> >::iterator& end);
	void handlePileToken(std::vector<std::vector<std::string> >::iterator& iter, std::vector<std::vector<std::string> >::iterator& end);

	int isValidPipToken(std::string *token);
	PlayingCard::Suit isValidSuitToken(std::string *token);
};