#pragma once

#include "Spline.hpp"

class Path : public Spline
{
public:
	Path();

	float getRadius (float position);

	inline float startRadius() { return _startRadius; }
	inline float endRadius() { return _endRadius; }

	inline void setStartRadius (float radius) { _startRadius = radius; }
	inline void setEndRadius (float radius) { _endRadius = radius; }

protected:
	float _startRadius;
	float _endRadius;

private:

};