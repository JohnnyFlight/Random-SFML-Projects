#include "VoronoiDiagramTest.hpp"

#include "VectorUtility.hpp"

namespace
{
	const sf::Vector2u kDefaultDimensions = sf::Vector2u(600, 600);
	const sf::Vector2f kDefaultShapeSize = sf::Vector2f(600.0f, 600.0f);

	const float kPointRadius = 5.0f;
}

VoronoiDiagramTest::VoronoiDiagramTest(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void VoronoiDiagramTest::initialise()
{
	_dimensions = kDefaultDimensions;

	_euclideanTexture.create(_dimensions.x, _dimensions.y);
	_manhattanTexture.create(_dimensions.x, _dimensions.y);

	_shape.setSize(kDefaultShapeSize);
	_shape.setTexture(&_manhattanTexture, true);

	for (unsigned i = 0; i < 36; i++)
	{
		//sf::Vector2f position = sf::Vector2f(50.0f + (100.0f * (i % 6)) + (((i / 6) % 2) * 50.0f), 50.0f + 100.0f * (i / 6));
		sf::Vector2f position = VectorUtility::randomInRectf(sf::Rect<float>(sf::Vector2f(0.0f, 0.0f), (sf::Vector2f)_dimensions));
		sf::Color colour = sf::Color(255 * (((i % 6) + 1) / 6.0f), 255 * (((i / 6) + 1) / 6.0f), 0);

		_diagram.addPoint(position, colour);

		sf::CircleShape circle(kPointRadius);
		
		circle.setPosition(position);
		circle.setOutlineColor(sf::Color::Black);
		circle.setOutlineThickness(1.0f);
		circle.setFillColor(colour);
		circle.setOrigin(kPointRadius, kPointRadius);

		_points.push_back(circle);
	}

	//	Calculate Euclidean and Manhattan voronoi maps
	_euclideanData.resize(_dimensions.x * _dimensions.y * 4, 0);
	_manhattanData.resize(_dimensions.x * _dimensions.y * 4, 0);

	for (unsigned i = 0; i < _dimensions.x; i++)
	{
		for (unsigned j = 0; j < _dimensions.y; j++)
		{
			//	Get colour value for point
			sf::Vector2f point(i, j);
			sf::Color colour = _diagram.colourEuclidean(point);
			_euclideanData[j * _dimensions.x * 4 + i * 4 + 0] = colour.r;
			_euclideanData[j * _dimensions.x * 4 + i * 4 + 1] = colour.g;
			_euclideanData[j * _dimensions.x * 4 + i * 4 + 2] = colour.b;
			_euclideanData[j * _dimensions.x * 4 + i * 4 + 3] = colour.a;
			
			colour = _diagram.colourManhattan(point);
			_manhattanData[j * _dimensions.x * 4 + i * 4 + 0] = colour.r;
			_manhattanData[j * _dimensions.x * 4 + i * 4 + 1] = colour.g;
			_manhattanData[j * _dimensions.x * 4 + i * 4 + 2] = colour.b;
			_manhattanData[j * _dimensions.x * 4 + i * 4 + 3] = colour.a;
		}
	}

	if (_euclideanData.empty() == false)
	{
		_euclideanTexture.update(&_euclideanData[0]);
	}

	if (_manhattanData.empty() == false)
	{
		_manhattanTexture.update(&_manhattanData[0]);
	}
}

void VoronoiDiagramTest::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true)
	{
		_shape.setTexture(&_euclideanTexture);
	}
	else
	{
		_shape.setTexture(&_manhattanTexture);
	}
}

void VoronoiDiagramTest::draw()
{
	_window.clear(sf::Color::Black);

	_window.draw(_shape);

	for (unsigned i = 0; i < _points.size(); i++)
	{
		_window.draw(_points[i]);
	}

	_window.display();
}