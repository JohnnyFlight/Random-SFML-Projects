#pragma once

#include <SFML/Graphics.hpp>

class Line : public sf::RectangleShape
{
public:
	Line();

	inline void setStartPoint(sf::Vector2f start) { _start = start; recalculateLength(); }
	inline void setEndPoint(sf::Vector2f end) { _end = end; recalculateLength(); }

	inline sf::Vector2f start() { return _start; }
	inline sf::Vector2f end() { return _end; }

private:
	float _thickness;
	float _length;

	sf::Vector2f _start;
	sf::Vector2f _end;

	void recalculateLength();
	void recalculateOrigin();
};