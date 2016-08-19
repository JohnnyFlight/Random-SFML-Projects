#pragma once

#include <SFML/sfml.hpp>
#include <map>
#include <tuple>

class InputManager
{
public:
	static InputManager* get();

	inline bool keyDown(sf::Keyboard::Key key) { return std::get<0>(_keys[key]); }
	inline bool keyUp(sf::Keyboard::Key key) { return !keyDown(key); }

	inline bool keyPressed(sf::Keyboard::Key key) { return keyDown(key) && !std::get<1>(_keys[key]); }
	inline bool keyReleased(sf::Keyboard::Key key) { return keyUp(key) && std::get<1>(_keys[key]); }

	void update();

protected:
	static InputManager* _instance;

	std::map<sf::Keyboard::Key, std::tuple<bool, bool>> _keys;

private:
	InputManager();

	static void initialise();
};