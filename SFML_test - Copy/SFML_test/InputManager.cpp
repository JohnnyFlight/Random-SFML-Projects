#include "InputManager.hpp"

InputManager *InputManager::_instance = 0;

InputManager::InputManager()
{

}

void InputManager::update()
{
	bool prev;
	for (unsigned i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		prev = std::get<0>(_keys[(sf::Keyboard::Key)i]);
		std::get<1>(_keys[(sf::Keyboard::Key)i]) = prev;
		std::get<0>(_keys[(sf::Keyboard::Key)i]) = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
	}
}

InputManager* InputManager::get()
{
	if (!_instance)
	{
		initialise();
	}

	return _instance;
}

void InputManager::initialise()
{
	_instance = new InputManager;
}