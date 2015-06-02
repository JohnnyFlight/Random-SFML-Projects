#include "VoronoiDiagram.hpp"

#include "VectorUtility.hpp"

VoronoiDiagram::VoronoiDiagram()
{

}

void VoronoiDiagram::addPoint(sf::Vector2f point, sf::Color colour)
{
	//	Prevent duplicate colours
	for (unsigned i = 0; i < _colours.size(); i++)
	{
		if (colour == _colours[i])
		{
			return;
		}
	}

	_points.push_back(point);
	_colours.push_back(colour);
}

sf::Color VoronoiDiagram::colourManhattan(sf::Vector2f point)
{
	unsigned nearestPoint = 0;
	float shortestDistance = FLT_MAX;

	if (_points.empty() == true)
	{
		return sf::Color(0, 0, 0, 0);
	}

	for (unsigned i = 0; i < _points.size(); i++)
	{
		float dist = abs(point.x - _points[i].x) + abs(point.y - _points[i].y);
		if (dist < shortestDistance)
		{
			shortestDistance = dist;
			nearestPoint = i;
		}
	}

	return _colours[nearestPoint];
}

sf::Color VoronoiDiagram::colourEuclidean(sf::Vector2f point)
{
	unsigned nearestPoint = 0;
	float shortestDistance = 1e+10f;

	if (_points.empty() == true)
	{
		return sf::Color(0, 0, 0, 0);
	}

	for (unsigned i = 0; i < _points.size(); i++)
	{
		float dist = VectorUtility::magnitude(point - _points[i]);
		if (dist < shortestDistance)
		{
			shortestDistance = dist;
			nearestPoint = i;
		}
	}

	return _colours[nearestPoint];
}