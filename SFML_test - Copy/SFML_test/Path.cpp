#include "Path.hpp"

Path::Path()
{

}

float Path::getRadius(float position)
{
	//	Normalise to 0 <= p <= 1
	if (position < 0.0f) position = 0.0f;
	if (position > 1.0f) position = 1.0f;

	return _startRadius + (_endRadius - _startRadius) * position;
}