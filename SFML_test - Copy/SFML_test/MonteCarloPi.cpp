#include "MonteCarloPi.hpp"

#include "MathsUtility.hpp"
#include "VectorUtility.hpp"

#include <sstream>

namespace
{
	const sf::Vector2f kStartPoint = sf::Vector2f(50.0f, 50.0f);
	const sf::Vector2f kAreaDimensions = sf::Vector2f(600.0f, 600.0f);

	const sf::Vector2f kDeviationPosition = sf::Vector2f(650.0f, 360.0f);
	const sf::Vector2f kDeviationDimensions = sf::Vector2f(600.0f, 300.0f);
	const float kDeviationZeroHeight = (kPi / (1.0f + kPi)) * kDeviationDimensions.y;
	const sf::Vertex kDeviationLines[] =
	{
		sf::Vertex(sf::Vector2f(1.0f, 1.0f)),
		sf::Vertex(sf::Vector2f(1.0f, kDeviationZeroHeight)),
		sf::Vertex(sf::Vector2f(kDeviationDimensions.x, kDeviationZeroHeight)),
		sf::Vertex(sf::Vector2f(1.0f, kDeviationZeroHeight)),
		sf::Vertex(sf::Vector2f(1.0f, kDeviationDimensions.y - 1.0f)),
		sf::Vertex(sf::Vector2f(kDeviationDimensions.x - 1.0f, kDeviationDimensions.y - 1.0f)),
		sf::Vertex(sf::Vector2f(kDeviationDimensions.x - 1.0f, 1.0f)),
		sf::Vertex(sf::Vector2f(1.0f, 1.0f))
	};
	const unsigned kPointsInDeviationLines = 8;

	const sf::Color kSquareColour = sf::Color::White;
	const sf::Color kCircleColour = sf::Color(64, 64, 64);
	const sf::Color kDotColour = sf::Color::Magenta;

	const float kDotRadius = 1.0f;
	const unsigned kDefaultDotsToAdd = 100;
	const unsigned kIncrementValue = 100;

	const unsigned kDotsPerDeviationMeasurement = 1;
}

MonteCarloPi::MonteCarloPi(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void MonteCarloPi::initialise()
{
	//	Seed rand()
	srand(time(NULL));

	_dotsToAdd = kDefaultDotsToAdd;

	Nc = Ns = 0;

	_circle = sf::CircleShape(kAreaDimensions.x / 2.0f);
	_circle.setPosition(kStartPoint + kAreaDimensions);
	_circle.setOrigin(kAreaDimensions);
	_circle.setFillColor(kCircleColour);

	_square = sf::RectangleShape(kAreaDimensions);
	_square.setPosition(kStartPoint);
	_square.setFillColor(kSquareColour);

	_dotsTexture.create(kAreaDimensions.x, kAreaDimensions.y);

	_dotsSprite.setTexture(_dotsTexture.getTexture());
	_dotsSprite.setPosition(kStartPoint);

	_deviationTexture.create(kDeviationDimensions.x, kDeviationDimensions.y);
	_deviationSprite.setTexture(_deviationTexture.getTexture());
	_deviationSprite.setPosition(kDeviationPosition);

	addDeviation();
	updateDeviations();

	//	Load font
	if (_font.loadFromFile("comic.ttf"))
	{
		_text.setFont(_font);
		_text.setColor(sf::Color::White);
		_text.setPosition(kStartPoint.x + kAreaDimensions.x, 0.0f);
		_text.setString("HJKHKJHKJHJKHJKHKJ");
		_text.setCharacterSize(20);
	}
}

void MonteCarloPi::update()
{
	bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool r = sf::Keyboard::isKeyPressed(sf::Keyboard::R);

	if (space && !_prevSpace)
	{
		addNewDot(_dotsToAdd);
	}

	if (up && !_prevUp)
	{
		_dotsToAdd += kIncrementValue;
	}

	if (down && !_prevDown)
	{
		if (_dotsToAdd >= kIncrementValue)
		{
			_dotsToAdd -= kIncrementValue;
		}
	}

	if (r && !_prevR)
	{
		reset();
	}

	recalculatePi();

	std::stringstream stream;
	stream << "Theory:" << std::endl;
	stream << "Area of circle = pi * radius ^ 2" << std::endl;
	stream << "Area of square = (2 * radius) ^ 2" << std::endl;
	stream << "Ratio of two areas is 4 / pi" << std::endl;
	stream << "Where Nc is dots in circle and Ns is dots in square" << std::endl;
	stream << "pi ~= 4 * Nc / Ns" << std::endl;
	stream << "So with Nc = " << Nc << " and Ns = " << Ns << std::endl;
	stream << "Our approximation of pi = " << _piApproximation << std::endl;
	stream << "Actual value of pi = " << kPi << std::endl;
	stream << "Difference from pi = " << (_piApproximation - kPi) << std::endl;
	stream << "Press space to add " << _dotsToAdd << " dots." << std::endl;
	stream << "Press up and down to add " << kIncrementValue << " more or fewer dots." << std::endl;
	stream << "The graph shows the deviation over time (-pi up to 1)" << std::endl;

	_text.setString(stream.str());

	_prevSpace = space;
	_prevUp = up;
	_prevDown = down;
	_prevR = r;
}

void MonteCarloPi::updateDeviations()
{
	//	Clear texture
	_deviationTexture.clear(sf::Color::Black);

	//	Create shape to use
	sf::CircleShape dot = sf::CircleShape(1.0f);
	dot.setFillColor(sf::Color::Magenta);

	//	Draw marking lines
	_deviationTexture.draw(kDeviationLines, kPointsInDeviationLines, sf::Lines);

	//	For every n times larger that Ns is compared to devWidth, draw only every nth dot
	//	Ideally I would just remove those dots
	unsigned drawNth = Ns / kDeviationDimensions.x + 1;

	//	Loop through deviations
	for (unsigned i = 0,  n = _deviations.size(); i < n; i++)
	{
		if (i && i % drawNth) continue;

		//	Position dot
		dot.setPosition((kDeviationDimensions.x / static_cast<float>(n)) * i, kDeviationDimensions.y * ((_deviations[i] + kPi) / (1 + kPi)));

		//	Draw dot
		_deviationTexture.draw(dot);
	}
}

void MonteCarloPi::draw()
{
	_window.clear(sf::Color::Black);

	_window.draw(_square);
	_window.draw(_circle);

	_window.draw(_dotsSprite);
	_window.draw(_deviationSprite);

	_window.draw(_text);

	_window.display();
}

void MonteCarloPi::reset()
{
	//	Reset values
	Nc = 0;
	Ns = 0;
	
	_piApproximation = 0;

	_dotsToAdd = kDefaultDotsToAdd;

	//	Clear texture
	_dotsTexture.clear(sf::Color::Transparent);
}

void MonteCarloPi::addNewDot(unsigned dots)
{
	sf::CircleShape dot(kDotRadius, 6);
	dot.setOrigin(kDotRadius, kDotRadius);
	dot.setFillColor(kDotColour);

	sf::Vector2f position;
	
	for (unsigned i = 0; i < dots; i++)
	{
		//	Move dot
		dot.setPosition(VectorUtility::randomInRectf(sf::Rect<float>(sf::Vector2f(0, 0), kAreaDimensions)));

		//	Draw dot to texture
		_dotsTexture.draw(dot);

		Ns++;
		if (VectorUtility::magnitude(dot.getPosition() - _circle.getPosition() + kStartPoint) < kAreaDimensions.x)
		{
			Nc++;
		}

		if (!(Ns % kDotsPerDeviationMeasurement))
		{
			addDeviation();
		}
	}

	updateDeviations();
}

void MonteCarloPi::addDeviation()
{
	recalculatePi();

	float dev = _piApproximation - kPi;
	
	if (dev < _deviationLimits.x)
	{
		_deviationLimits.x = dev;
	}
	
	if (dev > _deviationLimits.y)
	{
		_deviationLimits.y = dev;
	}

	_deviations.push_back(dev);
}

void MonteCarloPi::recalculatePi()
{
	_piApproximation = ((Ns==0)?(0.0f):(4.0f * Nc / Ns));
}