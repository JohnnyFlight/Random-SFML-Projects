#pragma once

#include <SFML/Graphics.hpp>

class Spline
{
public:
	Spline();
	Spline(sf::Vector3f start, sf::Vector3f end, sf::Vector3f anchor);
	
	inline sf::Vector3f start() { return _start; }
	inline sf::Vector3f end() { return _end; }
	inline sf::Vector3f anchor() { return _anchor; }
	
	inline void setStart(sf::Vector3f start) { _start = start; }
	inline void setEnd(sf::Vector3f end) { _end = end; }
	inline void setAnchor(sf::Vector3f anchor) { _anchor = anchor; }

	sf::Vector3f getPoint(float position);
	sf::Vector3f getNormal(float position);

protected:
	sf::Vector3f _start;
	sf::Vector3f _end;
	sf::Vector3f _anchor;

private:

};