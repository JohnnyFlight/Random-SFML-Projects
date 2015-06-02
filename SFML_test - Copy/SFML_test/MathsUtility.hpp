#pragma once

#include <cmath>

namespace
{
	const float kPi = atan(1.0f) * 4.0f;
}

class MathsUtility
{
public:
	static float randFloat(float min, float max);
	static int randInt(int min, int max);
	static unsigned randUnsigned(unsigned min, unsigned max);

	static float linearInterpolate(float start, float end, float position);
	static float cosineInterpolate(float start, float end, float position);
	static float cubicInterpolate(float v0, float v1, float v2, float v3, float position);

	static inline const float pi() { return kPi; }

protected:

private:

};