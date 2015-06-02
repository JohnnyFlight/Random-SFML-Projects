#include "Noise.hpp"

#include "MathsUtility.hpp"

Noise::Noise()
{
	_persistence = 0.75f;
	_octaves = 5;
	_initialValues = 10;
}

float Noise::calculateNoise(float x)
{
	float total = 0.0f;
	
	for (unsigned i = 0; i < _octaves; i++)
	{
		_octave = i;

		float frequency = powf(2.0f, i);
		float amplitude = powf(_persistence, i);

		total += interpolatedNoise(x * frequency) * amplitude;
	}

	return total;
}

void Noise::generateInitialNoise()
{
	//	Populate initial noise with 10 values between 0 and 1
	//	For each octave

	_initialNoise = std::vector<std::vector<float> >(_octaves, std::vector<float>());

	for (unsigned i = 0; i < _octaves; i++)
	{
		float frequency = powf(2.0f, i);
		float amplitude = powf(_persistence, i);
		for (unsigned j = 0; j < _initialValues; j++)
		{
			_initialNoise[i].push_back(MathsUtility::randFloat(0.0f, 1.0f) * amplitude);
		}
	}
}

float Noise::smoothNoise(float x)
{
	return 0.0f;
}

float Noise::interpolatedNoise(float x)
{
	//	Limit 0 <= x <= 1
	if (x < 0.0f) x = 0.0f;
	if (x > 1.0f) x = 1.0f;

	//	Scale x up to number of values
	x *= (_initialValues - 2);

	//	Get int x and remainder
	unsigned intX = (int)x;
	float remainder = x - intX;
	
	float v0 = _initialNoise[_octave][intX];
	float v1 = _initialNoise[_octave][intX + 1];

	return MathsUtility::linearInterpolate(v0, v1, remainder);
}