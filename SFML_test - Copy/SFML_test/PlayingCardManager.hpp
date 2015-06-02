#pragma once

#include "PlayingCardDrawable.hpp"
#include <SFML/Graphics.hpp>

class PlayingCardManager
{
public:
	PlayingCardManager();
	PlayingCardManager(sf::Texture back, sf::Font font);

	inline sf::Texture* back() { return &_cardBack; }
	inline sf::Font* font() { return &_cardFont; }
	inline sf::Texture* empty() { return &_deckEmpty; }

private:
	sf::Texture _cardBack;
	sf::Font _cardFont;
	sf::Texture _deckEmpty;

};