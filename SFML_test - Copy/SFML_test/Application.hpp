#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

class Application
{
protected:
	sf::RenderWindow _window;

	unsigned _windowHeight;
	unsigned _windowWidth;

	std::string _title;

public:
	Application(unsigned width, unsigned height, std::string title);

	virtual void initialise() = 0;
	void run();

protected:
	virtual void update() = 0;
	virtual void draw() = 0;

	sf::Clock _clock;

	inline sf::Rect<float> windowBounds() { return sf::Rect<float>(0.0f, 0.0f, (float)_windowWidth, (float)_windowHeight); }
};

#endif