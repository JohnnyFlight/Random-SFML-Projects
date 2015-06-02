#pragma once

#include "Application.hpp"

#include "PerlinNoise.hpp"
#include <vector>
#include "Agent.hpp"

class PeopleSpawning : public Application
{
public:
	PeopleSpawning(unsigned width, unsigned height, std::string title);

	void initialise();
	void update();
	void draw();

protected:
	PerlinNoise _perlin;

	unsigned _spawnWidth;
	unsigned _spawnHeight;

	unsigned _spawnNumber;

	float _spawnThreshold;

	sf::Font _font;
	sf::Text _infoText;

	sf::Clock _clock;
	sf::Transform _camera;
	float _cameraVelocity;

	std::vector<std::vector<float> > _noiseValues;
	std::vector<Agent> _agents;

	void updateInput(float timeStep);

	bool findSpawnThreshold(unsigned attempts);
	void initialiseAgents();
	void updateAgents(float timeStep);

private:

};