#pragma once

#include "PlayingCardDrawable.hpp"
#include <SFML/Graphics.hpp>

class PlayingCardManager
{
public:
	PlayingCardManager();
	
	inline void setBack(sf::Texture back) { _cardBack = back; }
	inline void setFont(sf::Font font) { _cardFont = font; }
	inline void setEmpty(sf::Texture empty) { _deckEmpty = empty; }

	inline sf::Texture* back() { return &_cardBack; }
	inline sf::Font* font() { return &_cardFont; }
	inline sf::Texture* empty() { return &_deckEmpty; }

private:
	sf::Texture _cardBack;
	sf::Font _cardFont;
	sf::Texture _deckEmpty;

};