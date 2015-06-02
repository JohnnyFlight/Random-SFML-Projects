#include "DragonSpiralTest.hpp"

#include "VectorUtility.hpp"
#include "MathsUtility.hpp"

namespace
{
	const sf::Color kLineStartColour = sf::Color::Blue;
	const sf::Color kLineColourOffset = sf::Color(7, 7, 0);

	const float kDefaultLength = 200.0f;
	const unsigned kDefaultCurveNumber = 4;
}

DragonSpiralTest::DragonSpiralTest(unsigned width, unsigned height, std::string name)
	: Application(width, height, name)
{

}

void DragonSpiralTest::initialise()
{
	sf::Color colour = kLineStartColour;

	Line line;

	_length = kDefaultLength;
	_curveNumber = kDefaultCurveNumber;

	sf::Vector2f centre = sf::Vector2f(0.0f, 360.0f);
	sf::Vector2f offset = sf::Vector2f(1280.0f, 0.0f);
	
	//	Create line
	line.setStartPoint(centre);
	line.setEndPoint(centre + offset);
	line.setFillColor(colour);

	_dragonSpirals.push_back(std::vector<Line>(1, line));

	/*for (unsigned i = 0; i < _curveNumber; i++)
	{
		//	Create line
		line.setStartPoint(centre);
		line.setEndPoint(centre + offset);
		line.setFillColor(colour);

		_dragonSpirals.push_back(std::vector<Line>(1, line));

		//	Adjust offsets
		colour += kLineColourOffset;
		VectorUtility::rotate(offset, 360.0f / _curveNumber);
	}

	centre = sf::Vector2f(200.0f, 600.0f);

	for (unsigned i = 0; i < _curveNumber; i++)
	{
		//	Create line
		line.setStartPoint(centre);
		line.setEndPoint(centre + offset);
		line.setFillColor(colour);

		_dragonSpirals.push_back(std::vector<Line>(1, line));

		//	Adjust offsets
		colour += kLineColourOffset;
		VectorUtility::rotate(offset, 360.0f / _curveNumber);
	}

	centre = sf::Vector2f(600.0f, 200.0f);

	for (unsigned i = 0; i < _curveNumber; i++)
	{
		//	Create line
		line.setStartPoint(centre);
		line.setEndPoint(centre + offset);
		line.setFillColor(colour);

		_dragonSpirals.push_back(std::vector<Line>(1, line));

		//	Adjust offsets
		colour += kLineColourOffset;
		VectorUtility::rotate(offset, 360.0f / _curveNumber);
	}

	centre = sf::Vector2f(600.0f, 600.0f);

	for (unsigned i = 0; i < _curveNumber; i++)
	{
		//	Create line
		line.setStartPoint(centre);
		line.setEndPoint(centre + offset);
		line.setFillColor(colour);

		_dragonSpirals.push_back(std::vector<Line>(1, line));

		//	Adjust offsets
		colour += kLineColourOffset;
		VectorUtility::rotate(offset, 360.0f / _curveNumber);
	}

	centre = sf::Vector2f(400.0f, 400.0f);

	for (unsigned i = 0; i < _curveNumber; i++)
	{
		//	Create line
		line.setStartPoint(centre);
		line.setEndPoint(centre + offset);
		line.setFillColor(colour);

		_dragonSpirals.push_back(std::vector<Line>(1, line));

		//	Adjust offsets
		colour += kLineColourOffset;
		VectorUtility::rotate(offset, 360.0f / _curveNumber);
	}*/
}

void DragonSpiralTest::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_prevSpace)
	{
		iterate();
	}

	_prevSpace = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

void DragonSpiralTest::draw()
{
	_window.clear(sf::Color::Black);

	for (auto iteration = _dragonSpirals.begin(); iteration != _dragonSpirals.end(); iteration++)
	{
		for (auto line = iteration->begin(); line != iteration->end(); line++)
		{
			_window.draw(*line);
		}
	}

	_window.display();
}

void DragonSpiralTest::iterate()
{
	//	Create new list
	std::vector<Line> newList;

	//	Increase colour
	_lineColour += kLineColourOffset;

	sf::Color colour = kLineStartColour;

	for (auto last = _dragonSpirals.begin(); last != _dragonSpirals.end(); last++)
	{
		for (unsigned i = 0; i < last->size(); i++)
		{
			//	Create two new lines either to the left or right of the current line
			//	-Get line
			sf::Vector2f line = (*last)[i].end() - (*last)[i].start();
			//	-Create new point
			sf::Vector2f newPoint = line / sqrtf(2.0f);
			//	--Rotate line 45*
			VectorUtility::rotate(newPoint, 45.0f * (1.0f - 2.0f * (i % 2)) /*+ MathsUtility::randFloat(-1.0f, 1.0f)*/);

			newPoint += (*last)[i].start();

			//	Create two new lines
			//	s to n
			Line line1;
			line1.setFillColor(colour);

			//	n to e
			Line line2;
			line2.setFillColor(colour);

			line1.setStartPoint((*last)[i].start());
			line1.setEndPoint(newPoint);

			line2.setStartPoint(newPoint);
			line2.setEndPoint((*last)[i].end());

			newList.push_back(line1);
			newList.push_back(line2);
		}
		(*last) = newList;
		newList.clear();

		colour += kLineColourOffset;
	}

}