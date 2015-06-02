#pragma once

#include "Application.hpp"

#include <list>
#include <vector>
#include "Particle.hpp"
#include "ParticleEmitter.h"

class ParticleTest : public Application
{
public:
	ParticleTest(unsigned width, unsigned height, std::string title);

	void initialise();
	void update();

	void updateInput(float timeStep);

	void draw();

protected:
	std::list<Particle> _particles;
	std::vector<ParticleEmitter> _emitters;
	float _emitterVelocity;

	float _concentrationVelocity;

	sf::Clock _clock;

	void spawnParticle();
private:
};