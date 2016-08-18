#include "PlayingCardDrawable.hpp"

#include <sstream>

namespace
{
	const sf::Vector2f kDefaultDimensions = sf::Vector2f(64.0f, 89.0f);
}

std::vector<sf::Texture> PlayingCardDrawable::_cardBacks;
std::vector<sf::Texture> PlayingCardDrawable::_emptyTextures;
std::vector<sf::Font> PlayingCardDrawable::_cardFonts;

PlayingCardDrawable::PlayingCardDrawable()
{
	_rect.setSize(kDefaultDimensions);

	_backIndex = 0;
	_emptyIndex = 0;
	_fontIndex = 0;

	setCard(PlayingCard());

	initialise();
}

PlayingCardDrawable::PlayingCardDrawable(PlayingCard card)
{
	_rect.setSize(kDefaultDimensions);

	_backIndex = 0;
	_emptyIndex = 0;
	_fontIndex = 0;

	setCard(card);

	initialise();
}

void PlayingCardDrawable::initialise()
{
	if (_card.isBlack())
		_text.setColor(sf::Color::Black);
	else
		_text.setColor(sf::Color::Red);

	if (_cardFonts.size() > _fontIndex)
	{
		_text.setFont(_cardFonts[_fontIndex]);
	}

	if (_cardBacks.size() > _backIndex)
	{
		_rect.setTexture(&_cardBacks[_backIndex]);
	}

	if (_card.isEmpty())
	{

	}

	_rect.setOutlineColor(sf::Color::Black);
	_rect.setOutlineThickness(1.0f);
}

void PlayingCardDrawable::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (_card.isEmpty())
		_rect.setTexture(&_emptyTextures[_emptyIndex]);
	else
		if (_faceUp == true)
			_rect.setTexture(NULL);
		else
			_rect.setTexture(&_cardBacks[_backIndex]);

	//	Render card
	target.draw(_rect, states);
	
	//	Render text
	if (_faceUp == true && _card.isEmpty() == false)
	{
		target.draw(_text, _rect.getTransform());
	}
}

bool PlayingCardDrawable::clicked(unsigned x, unsigned y)
{
	return _rect.getGlobalBounds().contains(sf::Vector2f(x, y));
}

void PlayingCardDrawable::setFont(unsigned index)
{
	if (_cardFonts.size() >= index) return;

	_fontIndex = index;

	_text.setFont(_cardFonts[index]);
}

void PlayingCardDrawable::setBack(unsigned index)
{
	if (_cardBacks.size() >= index) return;

	_backIndex = index;
}

void PlayingCardDrawable::setCard(PlayingCard card)
{
	_card = card;
	std::stringstream stream;
	stream << card.pipString() << std::endl << card.suitString();
	_text.setString(stream.str());
	if (card.isBlack())
	{
		_text.setColor(sf::Color::Black);
	}
	else
	{
		_text.setColor(sf::Color::Red);
	}
}