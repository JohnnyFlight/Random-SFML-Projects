#include "PlayingCardDrawable.hpp"

#include <sstream>

namespace
{
	const sf::Vector2f kDefaultDimensions = sf::Vector2f(64.0f, 89.0f);
}

PlayingCardDrawable::PlayingCardDrawable()
{
	setSize(kDefaultDimensions);

	setCard(PlayingCard());
}

PlayingCardDrawable::PlayingCardDrawable(PlayingCard card, PlayingCardManager *manager)
{
	setSize(kDefaultDimensions);

	if (manager != NULL)
	{
		if (manager->font() != NULL)
		{
			_font = manager->font();
		}

		if (manager->back() != NULL)
		{
			_back = manager->back();
		}
	}

	setCard(card);

	initialise();
}

void PlayingCardDrawable::initialise()
{
	_text.setColor(sf::Color::Black);

	if (_font != NULL)
	{
		_text.setFont(*_font);
	}

	if (_back != NULL)
	{
		setTexture(_back);
	}
}

void PlayingCardDrawable::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (_faceUp == true)
		setTexture(NULL);
	else
		setTexture(_back);

	//	Render card
	target.draw(*this, states);
	
	//	Render text
	if (_faceUp == true)
	{
		target.draw(_text, this->getTransform());
	}
}

bool PlayingCardDrawable::clicked(unsigned x, unsigned y)
{
	sf::FloatRect rect = getGlobalBounds();
	return rect.contains(sf::Vector2f(x, y));
}

void PlayingCardDrawable::setFont(sf::Font *font)
{
	_font = font;
	_text.setFont(*_font);
}

void PlayingCardDrawable::setBack(sf::Texture *back)
{
	_back = back;
	setTexture(back);
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