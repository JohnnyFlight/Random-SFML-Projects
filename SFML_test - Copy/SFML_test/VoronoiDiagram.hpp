#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class VoronoiDiagram
{
public:
	VoronoiDiagram();

	void addPoint(sf::Vector2f point, sf::Color colour);

	sf::Color colourManhattan(sf::Vector2f);
	sf::Color colourEuclidean(sf::Vector2f);

	sf::Vector2f pointManhattan(sf::Vector2f);
	sf::Vector2f pointEuclidean(sf::Vector2f);

private:
	void update();
	void draw();

	std::vector<sf::Vector2f> _points;
	std::vector<sf::Color> _colours;

};