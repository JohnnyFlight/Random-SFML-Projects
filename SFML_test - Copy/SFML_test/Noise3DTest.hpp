#pragma once

#include "Application.hpp"

#include "PerlinNoise3D.hpp"

class Noise3DTest : public Application
{
public:
	Noise3DTest(unsigned width, unsigned height, std::string title);

	void initialise();
	void update();
	void draw();

protected:
	PerlinNoise3D _noise;

	float _zPosition;
	float _zVelocity;

	void calculateNoise();
};