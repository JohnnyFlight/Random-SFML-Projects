#include "PlayingCardTest.hpp"

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

	_manager = PlayingCardManager(cardTexture, cardFont);
	_card = PlayingCardDrawable(PlayingCard(), &_manager);
	_card.setPosition(200.0f, 100.0f);
	_card.setOrientation(true);

	_deck = PlayingCardDeck();
	_deck.addCard(PlayingCard());
	_deck.shuffleDeck();
	_deck.setBack(_manager.back());
	_deck.setFont(_manager.font());
}

void PlayingCardTest::update()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		if (_deck.clicked(mousePos.x, mousePos.y))
		{
			_card.setCard(_deck.drawCard());
		}
	}

	_prevMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void PlayingCardTest::draw()
{
	_window.clear(sf::Color::Black);

	_card.draw(_window);
	_deck.draw(_window);

	_window.display();
}