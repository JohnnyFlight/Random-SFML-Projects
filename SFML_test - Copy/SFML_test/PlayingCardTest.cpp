#include "PlayingCardTest.hpp"

#include <iostream>

PlayingCardTest::PlayingCardTest(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void PlayingCardTest::initialise()
{
	//	Load in texture and font
	sf::Font cardFont;
	cardFont.loadFromFile("comic.ttf");

	sf::Texture cardTexture;
	cardTexture.loadFromFile("Card_Back.png");

	sf::Texture emptyTexture;
	emptyTexture.loadFromFile("Empty_Card.png");

	PlayingCardDrawable::addCardBack(cardTexture);
	PlayingCardDrawable::addCardFont(cardFont);
	PlayingCardDrawable::addEmptyTexture(emptyTexture);

	_card = PlayingCardDrawable(PlayingCard());
	_card.setPosition(200.0f, 100.0f);
	_card.setOrientation(true);

	_deck.addDeck(1);
	_deck.shuffleDeck();
	_deck.setOrientation(false);

	_card.initialise();
	_deck.initialise();

	_layout.loadFromFile("testLayout.txt");
}

void PlayingCardTest::update()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		if (_deck.clicked(mousePos.x, mousePos.y))
		{
			if (_deck.count() != 0)
			{
				PlayingCard card = _deck.drawCard();
				_card.setCard(card);
				_pile.addCard(card);
			}
		}

		if (_card.clicked(mousePos.x, mousePos.y))
		{
			_card.flip();
		}

		int cardClicked = _pile.cardClicked(mousePos.x, mousePos.y);
		if (cardClicked != -1)
		{
			std::cout << "Clicked card " << cardClicked << std::endl;
		}
	}

	_prevMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void PlayingCardTest::draw()
{
	_window.clear(sf::Color::Black);

	_layout.draw(_window);
	//_card.draw(_window);
	//_deck.draw(_window);
	//_pile.draw(_window);

	_window.display();
}