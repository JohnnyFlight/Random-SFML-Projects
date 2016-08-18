#include "DominosAITest.hpp"

#include <iostream>
#include <sstream>

namespace
{
	const std::string kFont = "comic.ttf";

	const unsigned kMaxPip = 6;
	const unsigned kShuffleNumber = 3;
	const unsigned kStartingHandSize = 7;
}

DominosAITest::DominosAITest(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void DominosAITest::initialise()
{
	//	Load font
	if (_font.loadFromFile("comic.ttf") == false)
	{
		std::cout << "Font " << kFont << " not loaded." << std::endl;
	}
	else
	{
		_fps.setFont(_font);
	}

	//	Add dominos to boneyard
	for (unsigned i = 0; i <= kMaxPip; i++)
	{
		for (unsigned j = i; j <= kMaxPip; j++)
		{
			_boneyard.push_back(Domino(i, j));
		}
	}

	//	Shuffle boneyard
	for (unsigned i = 0; i < kShuffleNumber; i++)
	{
		for (unsigned j = 0; j < _boneyard.size(); j++)
		{
			std::swap(_boneyard[j], _boneyard[rand()%_boneyard.size()]);
		}
	}

	//	Player and opponent draw hand
	for (unsigned i = 0; i < kStartingHandSize; i++)
	{
		playerDraw();
		opponentDraw();
	}

	_AI.makePrediction();
}

void DominosAITest::update()
{
	float elapsedTime = _clock.restart().asSeconds();

	std::stringstream stream;
	stream << "fps: " << 1.0f / elapsedTime;

	_fps.setString(stream.str());
}

void DominosAITest::draw()
{
	_window.clear(sf::Color::Black);

	_window.draw(_fps);

	_window.display();
}

void DominosAITest::playerDraw()
{
	if (_boneyard.size() > 0)
	{
		_playerHand.push_back(_boneyard.back());
		_AI.playerDrew(_boneyard.back());
		_boneyard.pop_back();
	}
}

void DominosAITest::opponentDraw()
{
	if (_boneyard.size() > 0)
	{
		_opponentHand.push_back(_boneyard.back());
		_AI.opponentDrew();
		_boneyard.pop_back();
	}
}