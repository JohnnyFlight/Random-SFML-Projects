#include "BoomShine.hpp"

#include <iostream>
#include <sstream>

#include "MathsUtility.hpp"
#include "VectorUtility.hpp"

namespace
{
	const unsigned kParticleNumber = 100;
}

BoomShine::BoomShine(unsigned width, unsigned height, std::string title)
	: Application(width, height, title)
{

}

void BoomShine::initialise()
{
	if (_font.loadFromFile("comic.ttf") == false)
	{
		std::cout << "Font not loaded." << std::endl;
	}

	_clicksText.setFont(_font);
	_clicksText.setColor(sf::Color::White);
	_clicksText.setPosition(1000.0f, 0.0f);

	_particlesText.setFont(_font);
	_particlesText.setColor(sf::Color::White);
	_particlesText.setPosition(1000.0f, 200.0f);

	//	Create particles
	for (unsigned i = 0; i < kParticleNumber; i++)
	{
		spawnParticle();
	}

	_startButton = Button(400.0f, 200.0f);
	_startButton.setFillColor(sf::Color::Blue);

	_currentLevel = -1;
	_state = State::Start;
	_poppedParticles = 0;

	loadLevels();

	_clock.restart();
}

void BoomShine::update()
{
	float timeStep = _clock.restart().asSeconds();

	switch (_state)
	{
	case State::Start:
		updateStart(timeStep);
		break;
	case State::Play:
		updatePlay(timeStep);
		break;
	case State::Pause:
		updatePause(timeStep);
		break;
	case State::Win:
		updateWin(timeStep);
		break;
	case State::Lose:
		updateLose(timeStep);
		break;
	case State::End:
		updateEnd(timeStep);
		break;
	}

	_prevMouse = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void BoomShine::updateStart(float timeStep)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && _prevMouse == false)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		if (_startButton.clicked(mousePos.x, mousePos.y))
		{
			nextLevel();
			_state = State::Play;
		}
	}

	for (unsigned i = 0; i < _particles.size(); i++)
	{
		_particles[i].update(timeStep);
	}

	collisionDetection();
}

void BoomShine::updatePlay(float timeStep)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && _prevMouse == false)
	{
		//	Click to add new particle
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		if (_clicks < _levels[_currentLevel].clicks())
		{
			//	Create new particle in expanded state
			if (mousePos.x > 0) if (mousePos.x < _windowWidth)
			if (mousePos.y > 0) if (mousePos.y < _windowHeight)
			{
				_clicks++;
				updateClicksText();
				spawnParticle(BoomParticle::State::Expanding);
				_particles[_particles.size() - 1].setPosition(mousePos.x, mousePos.y);
			}
		}
	}

	unsigned nonMovingParticles = 0;
	unsigned movingParticles = 0;

	for (std::vector<BoomParticle>::iterator iter = _particles.begin(); iter != _particles.end();)
	{
		//	Update particle
		iter->update(timeStep);

		if (iter->state() != BoomParticle::State::Moving)
		{
			nonMovingParticles++;
		}
		else
		{
			movingParticles++;
		}

		//	If particle is expired
		if (iter->expired() == true)
		{
			//	Remove particle
			iter = _particles.erase(iter);
		}
		else
		{
			//	Else increase iterator
			++iter;
		}
	}

	if (nonMovingParticles == 0)
	if (_poppedParticles > _levels[_currentLevel].goal())
	{
		_state = State::Win;
	}
	else
	{
		if (_clicks == _levels[_currentLevel].clicks())
		{
			_state = State::Lose;
		}
	}

	collisionDetection();
}

void BoomShine::updatePause(float timeStep)
{

}

void BoomShine::updateWin(float timeStep)
{
	_startButton.setFillColor(sf::Color::Green);
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && _prevMouse == false)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		if (_startButton.clicked(mousePos.x, mousePos.y))
		{
			nextLevel();
			_state = State::Play;
		}
	}
	
	for (unsigned i = 0; i < _particles.size(); i++)
	{
		_particles[i].update(timeStep);
	}

	collisionDetection();
}

void BoomShine::updateLose(float timeStep)
{
	_startButton.setFillColor(sf::Color::Red);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && _prevMouse == false)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		if (_startButton.clicked(mousePos.x, mousePos.y))
		{
			resetLevel();
			_state = State::Play;
		}
	}
	
	for (unsigned i = 0; i < _particles.size(); i++)
	{
		_particles[i].update(timeStep);
	}

	collisionDetection();
}

void BoomShine::updateEnd(float timeStep)
{

}

void BoomShine::updateClicksText()
{
	std::stringstream stream;
	stream << "Clicks: " << _clicks << " / " << _levels[_currentLevel].clicks();
	_clicksText.setString(stream.str());
}

void BoomShine::updateParticlesText()
{
	std::stringstream stream;
	stream << "Particles: " << _poppedParticles << " / " << _levels[_currentLevel].goal();
	_particlesText.setString(stream.str());
}

void BoomShine::draw()
{
	_window.clear(sf::Color::Black);

	for (unsigned i = 0; i < _particles.size(); i++)
	{
		_window.draw(_particles[i]);
	}

	switch (_state)
	{
	case State::Start:
		_window.draw(_startButton);
		break;
	case State::Play:
		_window.draw(_clicksText);
		_window.draw(_particlesText);
		break;
	case State::Pause:

		break;
	case State::Win:
		_window.draw(_startButton);
		break;
	case State::Lose:
		_window.draw(_startButton);
		break;
	case State::End:

		break;
	}

	_window.display();
}

void BoomShine::spawnParticle(BoomParticle::State state)
{
	//	Create particle
	BoomParticle particle;

	particle.setState(state);

	//	Place particle randomly in window
	particle.setPosition(VectorUtility::randomInRectf(windowBounds()));

	//	Give particle random diagonal movement direction
	sf::Vector2f direction = VectorUtility::normalised(sf::Vector2f(1.0f, 1.0f));
	VectorUtility::rotate(direction, 90.0f * MathsUtility::randInt(1, 4));

	particle.setMovementDirection(direction);

	//	Create particle colour
	float particleHue = MathsUtility::randFloat(0.0f, 360.0f);
	particle.setFillColor(VectorUtility::vectorToColour(VectorUtility::HSLToRGB(sf::Vector3f(particleHue, 0.5f, 0.5f)), 0.75f));

	_particles.push_back(particle);
}

void BoomShine::loadLevels()
{
	_levels.push_back(BoomShineLevel(20, 3, 15));
}

void BoomShine::resetLevel()
{
	//	Reset clicks
	_clicks = 0;
	_poppedParticles = 0;

	_particles.clear();

	for (unsigned i = 0; i < _levels[_currentLevel].particles(); i++)
	{
		spawnParticle();
	}

	updateClicksText();
	updateParticlesText();
}

void BoomShine::nextLevel()
{
	//	Reset clicks
	_clicks = 0;
	_poppedParticles = 0;

	if (_currentLevel < (int)_levels.size())
	{
		_currentLevel++;
	}

	if (_currentLevel == _levels.size())
	{
		_state = State::End;
	}
	else
	{
		_particles.clear();

		for (unsigned i = 0; i < _levels[_currentLevel].particles(); i++)
		{
			spawnParticle();
		}
	}

	updateClicksText();
	updateParticlesText();
}

void BoomShine::collisionDetection()
{
	for (unsigned i = 0; i < _particles.size(); i++)
	{
		if (_particles[i].state() == BoomParticle::State::Shrinking)
		{
			continue;
		}

		//	Check if particles has collided with other particles
		for (unsigned j = i; j < _particles.size(); j++)
		{
			if (_particles[j].state() == BoomParticle::State::Shrinking)
			{
				break;
			}

			if (_particles[i].state() != _particles[j].state())
			{
				if (hasCollided(&_particles[i], &_particles[j]))
				{
					_particles[i].hit();
					_particles[j].hit();

					_poppedParticles++;
					updateParticlesText();
				}
			}
		}

		//	Check if particle has collided with walls
		if (_particles[i].state() != BoomParticle::State::Moving)
		{
			continue;
		}
		else
		{
			sf::Rect<float> gameSize = windowBounds();

			//	Top wall
			if (_particles[i].getPosition().y - _particles[i].getRadius() < 0.0f)
			{
				_particles[i].setPosition(_particles[i].getPosition().x, _particles[i].getRadius());
				_particles[i].bounce(BoomParticle::BOUNCE_DOWN);
			}
			
			//	Right wall
			if (_particles[i].getPosition().x + _particles[i].getRadius() > gameSize.width)
			{
				_particles[i].setPosition(_particles[i].getPosition().x - _particles[i].getRadius(), _particles[i].getPosition().y);
				_particles[i].bounce(BoomParticle::BOUNCE_LEFT);
			}

			//	Bottom wall
			if (_particles[i].getPosition().y + _particles[i].getRadius() > gameSize.height)
			{
				_particles[i].setPosition(_particles[i].getPosition().x, gameSize.height - _particles[i].getRadius());
				_particles[i].bounce(BoomParticle::BOUNCE_UP);
			}

			//	Left wall
			if (_particles[i].getPosition().x - _particles[i].getRadius() < 0.0f)
			{
				_particles[i].setPosition(_particles[i].getRadius(), _particles[i].getPosition().y);
				_particles[i].bounce(BoomParticle::BOUNCE_RIGHT);
			}
		}
	}
}

bool BoomShine::hasCollided(BoomParticle *particle1, BoomParticle *particle2)
{
	float cumulativeRadius = particle1->getRadius() + particle2->getRadius();
	float sqrDistance = VectorUtility::sqrMagnitude(particle1->getPosition() - particle2->getPosition());

	return sqrDistance <= cumulativeRadius * cumulativeRadius;
}