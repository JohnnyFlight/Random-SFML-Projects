#include "ParticleEmitter.h"

#include "MathsUtility.hpp"
#include "VectorUtility.hpp"

namespace
{
	const float kDefaultEmissionRadius = 1.0f;
	const float kDefaultEmissionRate = 0.01f;

	const sf::Vector2f kDefaultEmissionDirection = sf::Vector2f(0.0f, 1.0f);
	const float kDefaultEmissionDirectionVariance = 30.0f;

	const float kDefaultEmissionConcentration = 2.0f;

	const float kDefaultParticleRadius = 5.0f;
	const sf::Color kDefaultParticleColour = sf::Color::Magenta;

	const float kDefaultParticleAlphaDecay = 100.0f;
	const float kDefaultParticleAlphaDecayVariance = 20.0f;

	const float kDefaultParticleScaleDecay = -2.0f;
	const float kDefaultParticleScaleDecayVariance = -0.2f;

	const sf::Vector2f kDefaultParticleVelocityDirection = sf::Vector2f(0.0f, 1.0f);
	const float kDefaultParticleVelocity = 100.0f;
}

ParticleEmitter::ParticleEmitter()
{
	_emissionRadius = kDefaultEmissionRadius;
	_emissionRate = kDefaultEmissionRate;

	_emissionConcentration = kDefaultEmissionConcentration;

	_emissionDirection = kDefaultEmissionDirection;
	_emissionDirectionVariance = kDefaultEmissionDirectionVariance;

	_particleRadius = kDefaultParticleRadius;
	_particleColour = kDefaultParticleColour;
	
	_particleAlphaDecay = kDefaultParticleAlphaDecay;
	_particleAlphaDecayVariance = kDefaultParticleAlphaDecayVariance;

	_particleScaleDecay = kDefaultParticleScaleDecay;
	_particleScaleDecayVariance = kDefaultParticleScaleDecayVariance;

	_particleVelocityDirection = kDefaultParticleVelocityDirection;
	_particleVelocity = kDefaultParticleVelocity;
}

bool ParticleEmitter::readyToSpawn()
{
	return _emissionTimer.getElapsedTime().asSeconds() > _emissionRate;
}

Particle ParticleEmitter::spawnParticle()
{
	_emissionTimer.restart();

	//	Select a random angle and distance
	float angle = MathsUtility::randFloat(0.0f, _emissionDirectionVariance) - _emissionDirectionVariance / 2.0f;
	float radius = MathsUtility::randFloat(0.0f, _emissionRadius);

	//	Create offset
	float radiusMultiplier =  MathsUtility::randFloat(0.0f, 1.0f);
	//sf::Vector2f positionOffset(0.0f, powf(radiusMultiplier, _emissionConcentration));
	sf::Vector2f positionOffset = _emissionDirection;
	positionOffset *= powf(radiusMultiplier, _emissionConcentration);
	VectorUtility::rotate(positionOffset, angle);
	positionOffset *= radius;
	
	float scaleDecayVariance = MathsUtility::randFloat(-_particleScaleDecayVariance, _particleScaleDecayVariance);
	float alphaDecayVariance = MathsUtility::randFloat(-_particleAlphaDecayVariance, _particleAlphaDecayVariance);

	//	Create particle
	Particle particle(_particleRadius, _position + positionOffset);
	particle.setFillColor(_particleColour);

	particle.setScaleDecay(_particleScaleDecay + scaleDecayVariance);
	particle.setAlphaDecay(_particleAlphaDecay + alphaDecayVariance);

	particle.setVelocityDirection(VectorUtility::normalised(positionOffset));
	particle.setVelocity(_particleVelocity);

	return particle;
}