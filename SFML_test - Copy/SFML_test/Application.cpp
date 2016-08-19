#include "Application.hpp"

Application::Application(unsigned width, unsigned height, std::string title)
{
	//	Not sure if I want this to do anything
	_windowWidth = width;
	_windowHeight = height;
	
	_screenCentre.translate(sf::Vector2f(width / 2.0f, height / 2.0f));

	_title = title;

	_window.create(sf::VideoMode(_windowWidth, _windowHeight), _title);

	_quit = false;
}

void Application::run()
{
	while (_window.isOpen() && !_quit)
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

		update();
		draw();
    }
}