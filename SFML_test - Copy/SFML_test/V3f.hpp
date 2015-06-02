#pragma once

#include <SFML/Graphics.hpp>

class V3f : public sf::Vector3f
{
public:
	inline sf::Vector2f xx() { return sf::Vector2f(x, x); }
	inline sf::Vector2f xy() { return sf::Vector2f(x, y); }
	inline sf::Vector2f xz() { return sf::Vector2f(x, z); }

	inline sf::Vector2f yx() { return sf::Vector2f(y, x); }
	inline sf::Vector2f yy() { return sf::Vector2f(y, y); }
	inline sf::Vector2f yz() { return sf::Vector2f(y, z); }

	inline sf::Vector2f zx() { return sf::Vector2f(z, x); }
	inline sf::Vector2f zy() { return sf::Vector2f(z, y); }
	inline sf::Vector2f zz() { return sf::Vector2f(z, z); }

protected:

private:

};