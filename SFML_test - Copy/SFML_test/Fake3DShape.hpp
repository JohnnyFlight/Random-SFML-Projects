#pragma once

#include <SFML/Graphics.hpp>

class Fake3DShape : public sf::Shape
{
public:
	Fake3DShape();

	inline sf::Vector3f *realPosition() { return &_realPosition; }
protected:
	sf::Vector3f _realPosition;
private:
};