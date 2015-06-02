#include "DragonSpiral.hpp"

#include "VectorUtility.hpp"

DragonSpiral::DragonSpiral()
{

}

DragonSpiral::DragonSpiral(sf::Vector2f start, sf::Vector2f end)
{
	_start = start;
	_end = end;

	_points.push_back(_start);
	_points.push_back(_end);
}

void DragonSpiral::iterate()
{
	if (_points.empty() == true) return;

	//	Create new vector
	std::vector<sf::Vector2f> newPoints;

	for (unsigned i = 0; i < _points.size() - 1; i++)
	{
		//	Add first point
		newPoints.push_back(_points[i]);

		//	Calculate new point
		//	-Calculate line
		sf::Vector2f line = _points[i + 1] - _points[i];
		line /= sqrtf(2.0f);

		VectorUtility::rotate(line, 45.0f * (1.0f - 2.0f * (i % 2)));

		//	Add new point
		newPoints.push_back(_points[i] + line);
	}

	//	Add end point
	newPoints.push_back(_end);

	_points = newPoints;
}

void DragonSpiral::clear()
{
	_points.clear();
	_points.push_back(_start);
	_points.push_back(_end);
}