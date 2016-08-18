#include "Navigation.hpp"

namespace
{
	const sf::Keyboard::Key kDefaultMoveUpKey = sf::Keyboard::W;
	const sf::Keyboard::Key kDefaultMoveDownKey = sf::Keyboard::A;
	const sf::Keyboard::Key kDefaultMoveLeftKey = sf::Keyboard::S;
	const sf::Keyboard::Key kDefaultMoveRightKey = sf::Keyboard::D;

	const sf::Keyboard::Key kDefaultZoomInKey = sf::Keyboard::Q;
	const sf::Keyboard::Key kDefaultZoomOutKey = sf::Keyboard::E;

	const float kDefaultMoveSpeed = 100.0f;
	const float kDefaultZoomSpeed = 1.0f;

	const Navigation::NavigationType kDefaultMoveType = Navigation::Keys;
	const Navigation::NavigationType kDefaultZoomType = Navigation::Keys;
}

Navigation::Navigation()
{
	//	Stuff equals defaults
	_moveUpKey = kDefaultMoveUpKey;
	_moveDownKey = kDefaultMoveDownKey;
	_moveLeftKey = kDefaultMoveLeftKey;
	_moveRightKey = kDefaultMoveRightKey;

	_zoomInKey = kDefaultZoomInKey;
	_zoomOutKey = kDefaultZoomOutKey;

	_moveSpeed = kDefaultMoveSpeed;
	_zoomSpeed = kDefaultZoomSpeed;

	_moveType = kDefaultMoveType;
	_zoomType = kDefaultZoomType;
}

Navigation::~Navigation()
{

}

void Navigation::moveCamera(sf::Transform* camera, float deltaTime)
{
	if (_moveType == Keys)
	{
		if (sf::Keyboard::isKeyPressed(_moveDownKey))
		{
			camera->translate(-_moveSpeed * deltaTime, 0.0f);
		}
	
		if (sf::Keyboard::isKeyPressed(_moveRightKey))
		{
			camera->translate(_moveSpeed * deltaTime, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(_moveLeftKey))
		{
			camera->translate(0.0f, _moveSpeed * deltaTime);
		}
	
		if (sf::Keyboard::isKeyPressed(_moveUpKey))
		{
			camera->translate(0.0f, -_moveSpeed * deltaTime);
		}
	}
	
	if (_zoomType == Keys)
	{
		if (sf::Keyboard::isKeyPressed(_zoomInKey))
		{
			float scale = _zoomSpeed * deltaTime;
			camera->scale(1.0f + scale, 1.0f + scale);
		}
	
		if (sf::Keyboard::isKeyPressed(_zoomOutKey))
		{
			float scale = _zoomSpeed * deltaTime;
			camera->scale(1.0f - scale, 1.0f - scale);
		}
	}
}