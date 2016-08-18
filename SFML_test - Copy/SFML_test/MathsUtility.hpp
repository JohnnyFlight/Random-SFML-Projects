#pragma once

#include <cmath>

namespace
{
	const float kPi = atan(1.0f) * 4.0f;
	const float kRoot2 = sqrtf(2.0f);
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

	static unsigned factorial(unsigned value);

	static inline const float pi() { return kPi; }
	static inline const float root2() { return kRoot2; }

protected:

private:

};