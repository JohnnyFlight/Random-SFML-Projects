#include "Spline.hpp"

Spline::Spline()
{

}

Spline::Spline(sf::Vector3f start, sf::Vector3f end, sf::Vector3f anchor)
{
	_start = start;
	_end = end;
	_anchor = anchor;
}

sf::Vector3f Spline::getPoint(float position)
{
	//	Cap the value of position to between 0 and 1
	if (position < 0.0f) position = 0.0f;
	if (position > 1.0f) position = 1.0f;

	//	Get primary lines
	sf::Vector3f sToA = _anchor - _start;
	sf::Vector3f aToE = _end - _anchor;

	//	Get primary points
	sf::Vector3f sToAP = _start + sToA * position;
	sf::Vector3f aToEP = _anchor + aToE * position;

	//	Get secondary line
	sf::Vector3f secondaryLine = aToEP - sToAP;

	//	Return secondary point
	return sToAP + secondaryLine * position;
}

sf::Vector3f Spline::getNormal(float position)
{
	//	Cap the value of position to between 0 and 1
	if (position < 0.0f) position = 0.0f;
	if (position > 1.0f) position = 1.0f;

	//	Get primary lines
	sf::Vector3f sToA = _anchor - _start;
	sf::Vector3f aToE = _end - _anchor;

	//	Get primary points
	sf::Vector3f sToAP = _start + sToA * position;
	sf::Vector3f aToEP = _anchor + aToE * position;

	//	Return secondary line
	return (aToEP - sToAP);
}