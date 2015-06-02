#include "LinePath.hpp"

#include "VectorUtility.hpp"

LinePath::LinePath()
{
	_length = 0.0f;
	_recalcLength = true;
}

sf::Vector2f LinePath::getPosition(float distance)
{
	if (_points.empty() == true)
		return sf::Vector2f(0.0f, 0.0f);
	
	if (_points.size() == 1)
		return _points[0];

	//	Get cumulative lengths
	for (unsigned i = 1; i < _points.size(); i++)
	{
		//	If distance < length between points
		float length = VectorUtility::magnitude(_points[i] - _points[i-1]);
		if (distance <= length)
		{
			//	Find difference and lerp
			float lerpValue = distance / length;

			return _points[i-1] + (_points[i] - _points[i-1]) * lerpValue;
		}
		else
		{
			//	Else remove length from distance
			distance -= length;
		}
	}

	return sf::Vector2f(0.0f, 0.0f);
}

float LinePath::getLength()
{
	if (_recalcLength == true)
	{
		_length = 0.0f;
		for (unsigned i = 1; i < _points.size(); i++)
		{
			_length += VectorUtility::magnitude(_points[i] - _points[i-1]);
		}
		_recalcLength = false;
	}

	return _length;
}