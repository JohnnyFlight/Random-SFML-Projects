#include "Button.hpp"

namespace
{
	const float kDefaultWidth = 50.0f;
	const float kDefaultHeight = 50.0f;
}

Button::Button()
	: sf::RectangleShape(sf::Vector2f(kDefaultWidth, kDefaultHeight))
{

}

Button::Button(float width, float height)
	: sf::RectangleShape(sf::Vector2f(width, height))
{

}

Button::~Button()
{

}

bool Button::clicked(unsigned x, unsigned y)
{
	if (x < getPosition().x) return false;
	if (x > getPosition().x + getSize().x) return false;
	if (y < getPosition().y) return false;
	if (y > getPosition().y + getSize().y) return false;

	return true;
}