#pragma once

#include <vector>

class Noise
{
public:
	Noise();

	float calculateNoise(float x);

	inline std::vector<std::vector<float> > *initialNoise() { return &_initialNoise; }

	enum Interpolation { Linear, Cosine, Cubic };

	inline unsigned octaves() { return _octaves; }

	void generateInitialNoise();

protected:
	//	One vector for each octave
	std::vector<std::vector<float> > _initialNoise;
	float _persistence;
	unsigned _octaves;
	unsigned _octave;
	unsigned _initialValues;

	Interpolation _interpolation;

	float smoothNoise(float x);
	float interpolatedNoise(float x);

private:

};