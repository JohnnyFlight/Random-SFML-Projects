#include <SFML/Graphics.hpp>

class Navigation
{
public:
	Navigation();
	~Navigation();

	enum NavigationType { None, Keys, Mouse };

	void moveCamera(sf::Transform* camera, float deltaTime);

	void update();

	//	Getters and setters go here

private:
	sf::Keyboard::Key _moveUpKey;
	sf::Keyboard::Key _moveDownKey;
	sf::Keyboard::Key _moveLeftKey;
	sf::Keyboard::Key _moveRightKey;
	
	sf::Keyboard::Key _zoomInKey;
	sf::Keyboard::Key _zoomOutKey;

	float _moveSpeed;
	NavigationType _moveType;

	float _zoomSpeed;
	NavigationType _zoomType;

	//	0 is left, 1 is middle, 2 is right
	//	0 is most recent, 1 is previous
	bool _mouseState[3][2];
};