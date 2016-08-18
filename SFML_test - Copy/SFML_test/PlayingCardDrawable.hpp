#pragma once

#include "PlayingCard.hpp"

#include "IClickable.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class PlayingCardDrawable : public IClickable
{
public:
	PlayingCardDrawable();
	PlayingCardDrawable(PlayingCard card);

	void initialise();

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	bool clicked(unsigned x, unsigned y);

	void setFont(unsigned index);
	void setBack(unsigned index);

	inline void setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }
	inline void setPosition(sf::Vector2f position) { _rect.setPosition(position); }

	inline void flip() { _faceUp = !_faceUp; }
	inline void setOrientation(bool faceUp) { _faceUp = faceUp; }
	inline bool orientation() { return _faceUp; }

	void setCard(PlayingCard card);
	inline PlayingCard &card() { return _card; }

	static inline void addCardBack(sf::Texture back) { _cardBacks.push_back(back); }
	static inline void addEmptyTexture(sf::Texture empty) { _emptyTextures.push_back(empty); }
	static inline void addCardFont(sf::Font font) { _cardFonts.push_back(font); }

	static inline sf::Texture* getCardBack(unsigned index) { return (index < _cardBacks.size())?(&_cardBacks[index]):(NULL); }
	static inline sf::Texture* getEmptyTexture(unsigned index) { return (index < _emptyTextures.size())?(&_emptyTextures[index]):(NULL); }
	static inline sf::Font* getCardFont(unsigned index) { return (index < _cardFonts.size())?(&_cardFonts[index]):(NULL); }

protected:
	sf::RectangleShape _rect;
	sf::Text _text;

	PlayingCard _card;
	bool _faceUp;

	unsigned _backIndex;
	unsigned _emptyIndex;
	unsigned _fontIndex;

	static std::vector<sf::Texture> _cardBacks;
	static std::vector<sf::Texture> _emptyTextures;
	static std::vector<sf::Font> _cardFonts;
};