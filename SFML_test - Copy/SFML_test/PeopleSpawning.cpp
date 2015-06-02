#include "PeopleSpawning.hpp"

#include "VectorUtility.hpp"
#include <iostream>
#include <sstream>

namespace
{
	const float kNoiseWidth = 5.0f;
	const float kNoiseHeight = 5.0f;

	const float kThresholdStep = 0.0001f;

	const float kAgentDimensions = 10.0f;
}

PeopleSpawning::PeopleSpawning(unsigned width, unsigned height, std::string title)
	: Application(width, height, title)
{

}

void PeopleSpawning::initialise()
{
	_perlin = PerlinNoise(kNoiseWidth, kNoiseHeight);
	_perlin.initialise();

	_spawnWidth = 80;
	_spawnHeight = 70;

	_spawnNumber = 2000;

	_camera = sf::Transform::Identity;
	_cameraVelocity = 300.0f;

	//_spawnThreshold = 0.3462f;

	if (_font.loadFromFile("comic.ttf") == false)
	{
		std::cout << "Font not found." << std::endl;
	}

	_infoText.setFont(_font);
	_infoText.setColor(sf::Color::White);
	_infoText.setPosition(10.0f * _spawnWidth, 0.0f);

	for (unsigned i = 0; i < _spawnWidth; i++)
	{
		_noiseValues.push_back(std::vector<float>(_spawnHeight, 0.0f));
		for (unsigned j = 0; j < _spawnHeight; j++)
		{
			_noiseValues[i][j] = powf((_perlin.getNoise(i / kNoiseWidth * 3.0f, j / kNoiseHeight * 3.0f) + 1.0f) / 2.0f, 2);
		}
	}

	findSpawnThreshold(10);
	initialiseAgents();

	_clock.restart();
}

void PeopleSpawning::update()
{
	float timeStep = _clock.restart().asSeconds();

	updateInput(timeStep);

	unsigned spawnCount = 0;

	for (unsigned i = 0; i < _spawnWidth; i++)
	{
		for (unsigned j = 0; j < _spawnHeight; j++)
		{
			if (_noiseValues[i][j] > _spawnThreshold)
			{
				spawnCount++;
			}
		}
	}

	std::stringstream infoString;
	infoString << "Spawn count: " << spawnCount << std::endl;
	infoString << "Spawn threshold: " << _spawnThreshold << std::endl;

	_infoText.setString(infoString.str());

	//updateAgents(timeStep);
}

void PeopleSpawning::updateInput(float timeStep)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true)
	{
		movement.y = -1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true)
	{
		movement.x = -1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		movement.y = 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true)
	{
		movement.x = 1.0f;
	}

	VectorUtility::normalise(movement);
	movement *= _cameraVelocity * timeStep;
	_camera.translate(-movement);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (_spawnThreshold < 1.0f)
			_spawnThreshold += kThresholdStep;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (_spawnThreshold > 0.0f)
			_spawnThreshold -= kThresholdStep;
	}
}

void PeopleSpawning::updateAgents(float timeStep)
{
	//	Update
	for (unsigned i = 0; i < _agents.size(); i++)
	{
		_agents[i].update(&_agents);
	}

	//	Move
	for (unsigned i = 0; i < _agents.size(); i++)
	{
		_agents[i].move(0.1f);
	}
}

void PeopleSpawning::draw()
{
	_window.clear(sf::Color::Black);

	for (unsigned i = 0; i < _agents.size(); i++)
	{
		_window.draw(_agents[i], _camera);
	}

	_window.draw(_infoText, _camera);

	_window.display();
}

bool PeopleSpawning::findSpawnThreshold(unsigned attempts)
{
	//	Set threshold to a medium
	_spawnThreshold = 0.5f;

	float spawnGap = 0.25f;
	
	unsigned spawnCount = 0;

	for (unsigned attempt = 0; attempt < attempts; attempt++)
	{
		//	Check if spawn count is above or below goal
		for (unsigned i = 0; i < _spawnWidth; i++)
		{
			for (unsigned j = 0; j < _spawnHeight; j++)
			{
				if (_noiseValues[i][j] > _spawnThreshold)
				{
					spawnCount++;
				}
			}
		}

		if (spawnCount == _spawnNumber)
		{
			return true;
		}
		else if (spawnCount > _spawnNumber)
		{
			//	Increase threshold
			_spawnThreshold += spawnGap;
		}
		else
		{
			//	Decrease threshold
			_spawnThreshold -= spawnGap;
		}

		spawnGap /= 2.0f;
		spawnCount = 0;
	}

	return false;
}

void PeopleSpawning::initialiseAgents()
{
	float spacing = 5.0f;

	//	Assumes appropriate spawn threshold has been found
	for (unsigned i = 0; i < _spawnWidth; i++)
	{
		for (unsigned j = 0; j < _spawnHeight; j++)
		{
			if (_noiseValues[i][j] > _spawnThreshold)
			{
				Agent agent(kAgentDimensions, kAgentDimensions);;
				agent.setPosition((float)i * spacing * 2.0f + spacing * 5 * _noiseValues[_spawnWidth - i- 1][_spawnHeight - j - 1],
								  (float)j * spacing * 2.0f + spacing * 5 * (1.0f - _noiseValues[_spawnWidth - i - 1][_spawnHeight - j - 1]));
				_agents.push_back(agent);
			}
		}
	}
}