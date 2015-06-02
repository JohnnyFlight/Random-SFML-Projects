#pragma once

#include "PlayingCard.hpp"
#include "PlayingCardManager.hpp"

#include "IClickable.hpp"
#include <SFML/Graphics.hpp>

//	Forward Declaration
class PlayingCardManager;

class PlayingCardDrawable : public sf::RectangleShape, IClickable
{
public:
	PlayingCardDrawable();
	PlayingCardDrawable(PlayingCard card, PlayingCardManager *manager = NULL);

	void initialise();

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	bool clicked(unsigned x, unsigned y);

	void setFont(sf::Font *font);
	void setBack(sf::Texture *back);

	inline void flip() { _faceUp = !_faceUp; }
	inline void setOrientation(bool faceUp) { _faceUp = faceUp; }
	inline bool orientation() { return _faceUp; }

	void setCard(PlayingCard card);
	inline PlayingCard card() { return _card; }

protected:
	sf::Font *_font;
	sf::Text _text;

	sf::Texture *_back;

	PlayingCard _card;
	bool _faceUp;
};