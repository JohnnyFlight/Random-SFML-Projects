#pragma once

#include <SFML/Graphics.hpp>
#include "IClickable.hpp"

class Button : public sf::RectangleShape, public IClickable
{
public:
	Button();
	Button(float width, float height);
	~Button();

	bool clicked(unsigned x, unsigned y);
protected:

private:

};