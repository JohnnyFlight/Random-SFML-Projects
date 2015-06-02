#pragma once

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

class BezierCurve2D
{
public:
	BezierCurve2D();

	void addAnchor(sf::Vector2f anchor, int position = -1);

	sf::Vector2f getAnchor(unsigned position);
	sf::Vector2f getPoint(float position, bool preCalc = false);
	inline unsigned size() { return _anchors.size(); }
	inline unsigned preCalcSize() { return _preCalc.size(); }

	float getLength(unsigned segments = 100);

private:
	std::vector<sf::Vector2f> _anchors;

	//	List of used points
	std::map<unsigned, sf::Vector2f> _preCalc;
};