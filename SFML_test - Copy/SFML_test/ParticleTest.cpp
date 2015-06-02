#include "ParticleTest.hpp"

#include <iostream>
#include "MathsUtility.hpp"

namespace
{
	const unsigned kNumberParticles = 1000;

	const float kDefaultEmitterVelocity = 200.0f;
	const float kDefaultConcentrationVelocity = 1.0f;
}

ParticleTest::ParticleTest(unsigned width, unsigned height, std::string title)
	: Application(width, height, title)
{

}

void ParticleTest::initialise()
{
	ParticleEmitter emitter;
	emitter.setPosition(sf::Vector2f(200.0f, 200.0f));
	emitter.setParticleColour(sf::Color::Magenta);
	_emitters.push_back(emitter);

	emitter.setPosition(sf::Vector2f(200.0f, 200.0f));
	emitter.setParticleColour(sf::Color::Cyan);
	_emitters.push_back(emitter);

	emitter.setPosition(sf::Vector2f(200.0f, 200.0f));
	emitter.setParticleColour(sf::Color::Yellow);
	_emitters.push_back(emitter);

	_emitterVelocity = kDefaultEmitterVelocity;
	_concentrationVelocity = kDefaultConcentrationVelocity;

	for (unsigned i = 0; i < kNumberParticles; i++)
	{
		spawnParticle();
	}

	_clock.restart();
}

void ParticleTest::update()
{
	float timeStep = _clock.restart().asSeconds();

	updateInput(timeStep);

	for (std::vector<ParticleEmitter>::iterator i = _emitters.begin(); i != _emitters.end(); i++)
	{
		if (i->readyToSpawn() == true)
		{
			_particles.push_back(i->spawnParticle());
		}
	}

	for (std::list<Particle>::iterator i = _particles.begin(); i != _particles.end();)
	{
		i->update(timeStep);
		i->move(timeStep);
		//	If particle is to be removed
		if (i->alpha() == 0.0f)
		{
			//	Remove particle
			i = _particles.erase(i);
		}
		else
		{
			//	Else update iterator
			++i;
		}
	}
}

void ParticleTest::updateInput(float timeStep)
{
	sf::Vector2f movement(0.0f, 0.0f);
	float concentration = 1.0f;

	if (_emitters.empty() == false)
	{
		sf::Vector2f mousePosf(sf::Mouse::getPosition(_window));
		movement = mousePosf - _emitters.begin()->position();
		VectorUtility::normalise(movement);
		concentration = _emitters.begin()->emissionConcentration();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true)
	{
		concentration += _concentrationVelocity * timeStep;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		concentration -= _concentrationVelocity * timeStep;
	}

	std::cout << "Concentration: " << concentration << std::endl;

	for (std::vector<ParticleEmitter>::iterator i = _emitters.begin(); i != _emitters.end(); i++)
	{
		i->move(movement * _emitterVelocity * timeStep);
		i->setEmissionConcentration(concentration);
	}
}

void ParticleTest::draw()
{
	_window.clear(sf::Color::Black);

	for (auto iter = _particles.begin(); iter != _particles.end(); iter++)
	{
		_window.draw(*iter);
	}

	_window.display();
}

void ParticleTest::spawnParticle()
{
	//	Create particle
}