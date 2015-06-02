#include "PlayingCardManager.hpp"

PlayingCardManager::PlayingCardManager()
{

}

PlayingCardManager::PlayingCardManager(sf::Texture back, sf::Font font)
{
	_cardBack = back;
	_cardFont = font;
}