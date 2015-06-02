#pragma once

#include "Application.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#include "VoronoiDiagram.hpp"

class VoronoiDiagramTest : public Application
{
public:
	VoronoiDiagramTest(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	void update();
	void draw();

	VoronoiDiagram _diagram;

	sf::Texture _euclideanTexture;
	std::vector<sf::Uint8> _euclideanData;

	sf::Texture _manhattanTexture;
	std::vector<sf::Uint8> _manhattanData;

	sf::RectangleShape _shape;

	sf::Vector2u _dimensions;

	std::vector<sf::CircleShape> _points;

};