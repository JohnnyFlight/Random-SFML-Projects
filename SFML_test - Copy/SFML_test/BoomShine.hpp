#pragma once

#include "Application.hpp"

#include <vector>
#include "BoomParticle.hpp"
#include "BoomShineLevel.hpp"

#include "Button.hpp"

class BoomShine : public Application
{
public:
	BoomShine(unsigned width, unsigned height, std::string title);

	enum State { Start, Play, Pause, Win, Lose, End };

	void initialise();
	void update();
	void draw();

private:
	State _state;

	std::vector<BoomShineLevel> _levels;
	int _currentLevel;
	unsigned _clicks;

	std::vector<BoomParticle> _particles;
	unsigned _poppedParticles;

	sf::Font _font;

	sf::Text _clicksText;
	sf::Text _particlesText;

	Button _startButton;

	void spawnParticle(BoomParticle::State state = BoomParticle::State::Moving);

	bool _prevMouse;

	void loadLevels();
	void resetLevel();
	void nextLevel();
	
	void updateStart(float timeStep);
	void updatePlay(float timeStep);
	void updatePause(float timeStep);
	void updateWin(float timeStep);
	void updateLose(float timeStep);
	void updateEnd(float timeStep);

	void updateClicksText();
	void updateParticlesText();

	void collisionDetection();
	bool hasCollided(BoomParticle *particle1, BoomParticle *particle2);
};