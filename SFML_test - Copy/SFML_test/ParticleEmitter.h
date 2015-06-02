#pragma once

#include <SFML\Graphics.hpp>
#include "Particle.hpp"

class ParticleEmitter
{
public:
	ParticleEmitter();

	bool readyToSpawn();

	Particle spawnParticle();

	//	Setters

	inline void setPosition(sf::Vector2f position) { _position = position; }
	inline void move(sf::Vector2f direction) { _position += direction; }
	
	inline void setEmissionRadius(float emissionRadius) { _emissionRadius = emissionRadius; }
	inline void setEmissionRate(float emissionRate) { _emissionRate = emissionRate; }

	inline void setEmissionConcentration(float emissionConcentration) { _emissionConcentration = emissionConcentration; }

	inline void setEmissionDirection(sf::Vector2f emissionDirection) { _emissionDirection = emissionDirection; }
	inline void setEmissionDirectionVariance(float emissionDirectionVariance) { _emissionDirectionVariance = emissionDirectionVariance; }

	inline void setParticleRadius(float particleRadius) { _particleRadius = particleRadius; }
	inline void setParticleColour(sf::Color particleColour) { _particleColour = particleColour; }
	
	inline void setParticleAlphaDecay(float particleAlphaDecay) { _particleAlphaDecay = particleAlphaDecay; }
	inline void setParticleAlphaDecayVariance(float particleAlphaDecayVariance) { _particleAlphaDecayVariance = particleAlphaDecayVariance; }

	inline void setParticleScaleDecay(float particleScaleDecay) { _particleScaleDecay = particleScaleDecay; }
	inline void setParticleScaleDecayVariance(float particleScaleDecayVariance) { _particleScaleDecayVariance = particleScaleDecayVariance; }

	//	Getters

	inline sf::Vector2f position() { return _position; }
	
	inline float emissionRadius() { return _emissionRadius; }
	inline float emissionRate() { return _emissionRate; }

	inline float emissionConcentration() { return _emissionConcentration; }

	inline sf::Vector2f emissionDirection() { return _emissionDirection; }
	inline float emissionDirectionVariance() { return _emissionDirectionVariance; }

	inline float particleRadius() { return _particleRadius; }
	inline sf::Color particleColour() { return _particleColour; }
	
	inline float particleAlpaDecay() { return _particleAlphaDecay; }
	inline float particleAlpaDecayVariance() { return _particleAlphaDecayVariance; }

	inline float particlScaleDecay() { return _particleScaleDecay; }
	inline float particlScaleDecayVariance() { return _particleScaleDecayVariance; }

protected:
	sf::Vector2f _position;

	sf::Clock _emissionTimer;

	float _emissionRadius;
	float _emissionRate;

	float _emissionConcentration;

	sf::Vector2f _emissionDirection;
	float _emissionDirectionVariance;

	float _particleRadius;
	sf::Color _particleColour;

	float _particleAlphaDecay;
	float _particleAlphaDecayVariance;

	float _particleScaleDecay;
	float _particleScaleDecayVariance;

	sf::Vector2f _particleVelocityDirection;
	float _particleVelocity;

private:

};