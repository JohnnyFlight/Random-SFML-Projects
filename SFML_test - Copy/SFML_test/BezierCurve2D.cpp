#include "BezierCurve2D.hpp"

#include "VectorUtility.hpp"

namespace
{
	const unsigned kPreCalcDiscretization = 16384;
}

BezierCurve2D::BezierCurve2D()
{

}

void BezierCurve2D::addAnchor(sf::Vector2f anchor, int position)
{
	if (position < 0)
	{
		_anchors.push_back(anchor);
	}
	else
	{
		if (position >= _anchors.size())
		{
			_anchors.push_back(anchor);
		}
		else
		{
			_anchors.insert(_anchors.begin() + position, anchor);
		}
	}
}

sf::Vector2f BezierCurve2D::getAnchor(unsigned position)
{
	if (position < _anchors.size())
	{
		return _anchors[position];
	}
	else
	{
		return sf::Vector2f(0.0f, 0.0f);
	}
}

sf::Vector2f BezierCurve2D::getPoint(float position, bool preCalc)
{
	//	Cap position between 0 and 1
	if (position < 0.0f) position = 0.0f;
	if (position > 1.0f) position = 1.0f;

	if (preCalc == true)
	{
		//	Check if point not in list
		//	Add accuracy range
		std::map<unsigned, sf::Vector2f>::iterator iter = _preCalc.find(position * kPreCalcDiscretization);
		if (iter != _preCalc.end())
		{
			return iter->second;
		}
	}

	if (_anchors.size() == 0) return sf::Vector2f(0.0f, 0.0f);

	std::vector<sf::Vector2f> points = _anchors;

	while (points.size() > 1)
	{
		std::vector<sf::Vector2f> tempPoints;

		//	Go through lines
		for (unsigned i = 0; i < points.size() - 1; i++)
		{
			//	Get point along line
			sf::Vector2f start = points[i];
			sf::Vector2f line = points[i+1] - points[i];
			line *= position;

			tempPoints.push_back(start + line);
		}

		points = tempPoints;
	}

	if (preCalc == true)
	{
		//	Add points to precalc
		_preCalc.insert(std::pair<unsigned, sf::Vector2f>(position * kPreCalcDiscretization, points[0]));
	}

	return points[0];
}

float BezierCurve2D::getLength(unsigned segments)
{
	float length = 0.0f;

	std::vector<sf::Vector2f> points;

	for (unsigned i = 0; i < segments + 1; i++)
	{
		points.push_back(getPoint(i / (float)segments));
	}

	//	Get length for each line
	for (unsigned i = 0; i < segments; i++)
	{
		length += VectorUtility::magnitude(points[i+1] - points[i]);
	}

	return length;
}