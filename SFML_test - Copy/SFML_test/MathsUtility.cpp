#include "MathsUtility.hpp"

#include <cstdlib>

float MathsUtility::randFloat(float min, float max)
{
	return min + (rand() / (float)RAND_MAX) * (max - min);
}

int MathsUtility::randInt(int min, int max)
{
	return min + (rand() % (max - min)) + min + 1;
}

unsigned MathsUtility::randUnsigned(unsigned min, unsigned max)
{
	if (max == min) return min;
	return min + (rand() % (max - min)) + min + 1;
}

float MathsUtility::linearInterpolate(float start, float end, float position)
{
	return start + position * (end - start);
}

float MathsUtility::cosineInterpolate(float start, float end, float position)
{
	position *= pi();

	float working = (1.0f - cosf(position)) * 0.5f;
	return start + position * (end - start);
}

float MathsUtility::cubicInterpolate(float v0, float v1, float v2, float v3, float position)
{
	float cubic = (v3 - v2) - (v0 - v1);
	float quadratic = (v0 - v1) - cubic;
	float linear = v2 - v0;
	float intercept = v1;

	return cubic * position * position * position +
		   quadratic * position * position +
		   linear * position +
		   intercept;
}