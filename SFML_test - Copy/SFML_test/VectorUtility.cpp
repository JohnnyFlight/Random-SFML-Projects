#include "VectorUtility.hpp"

#include <cmath>
#include "MathsUtility.hpp"

namespace
{
	const float degToRad = atan(1.0f) / 45.0f;
	const float radToDeg = 45.0f / atan(1.0f);
}

/*
	Magnitude
*/

float VectorUtility::magnitude(sf::Vector3f vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float VectorUtility::magnitude(sf::Vector3i vector)
{
	return sqrt((float)vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float VectorUtility::magnitude(sf::Vector2f vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float VectorUtility::magnitude(sf::Vector2i vector)
{
	return sqrt((float)vector.x * vector.x + vector.y * vector.y);
}

float VectorUtility::magnitude(sf::Vector2u vector)
{
	return sqrt((float)vector.x * vector.x + vector.y * vector.y);
}

/*
	Square Magnitude
*/

float VectorUtility::sqrMagnitude(sf::Vector3f vector)
{
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

float VectorUtility::sqrMagnitude(sf::Vector3i vector)
{
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

float VectorUtility::sqrMagnitude(sf::Vector2f vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float VectorUtility::sqrMagnitude(sf::Vector2i vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float VectorUtility::sqrMagnitude(sf::Vector2u vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

/*
	Normalise
*/

void VectorUtility::normalise(sf::Vector2f &vector)
{
	//	Divide vector by magnitude
	float mag = VectorUtility::magnitude(vector);
	if (mag != 0.0f)
		vector /= mag;
}

void VectorUtility::normalise(sf::Vector3f &vector)
{
	//	Divide vector by magnitude
	float mag = VectorUtility::magnitude(vector);
	if (mag != 0.0f)
		vector /= mag;
}

/*
	Normalised
*/

sf::Vector2f VectorUtility::normalised(sf::Vector2f vector)
{
	//	Divide vector by magnitude
	return vector / VectorUtility::magnitude(vector);
}

sf::Vector3f VectorUtility::normalised(sf::Vector3f vector)
{
	//	Divide vector by magnitude
	return vector / VectorUtility::magnitude(vector);
}

/*
	Rotate
	Note: All rotations use degrees
*/

void VectorUtility::rotate(sf::Vector2f &vector, float angle)
{
	angle *= degToRad;

	float sine = sinf(angle);
	float cosine = cosf(angle);

	sf::Vector2f copy = vector;

	vector.x = copy.x * cosine - copy.y * sine;
	vector.y = copy.x * sine + copy.y * cosine;
}

void VectorUtility::rotate(sf::Vector2i &vector, float angle)
{
	angle *= degToRad;

	float sine = sinf(angle);
	float cosine = cosf(angle);

	sf::Vector2i copy = vector;

	vector.x = copy.x * cosine - copy.y * sine;
	vector.y = copy.x * sine + copy.y * cosine;
}

/*
	Rotated
*/

sf::Vector2f VectorUtility::rotated(sf::Vector2f vector, float angle)
{
	angle *= degToRad;

	float sine = sinf(angle);
	float cosine = cosf(angle);

	sf::Vector2f copy = vector;

	vector.x = copy.x * sine - copy.y * cosine;
	vector.y = copy.x * sine + copy.y * cosine;

	return vector;
}

sf::Vector2i VectorUtility::rotated(sf::Vector2i vector, float angle)
{
	angle *= degToRad;

	float sine = sinf(angle);
	float cosine = cosf(angle);

	sf::Vector2i copy = vector;

	vector.x = copy.x * sine - copy.y * cosine;
	vector.y = copy.x * sine + copy.y * cosine;

	return vector;
}

/*
	Reflection
*/

/*
	Cross Product
*/

/*
	Dot Product
*/

float VectorUtility::dot(sf::Vector2f vector1, sf::Vector2f vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y;
}

float VectorUtility::dot(sf::Vector3f vector1, sf::Vector3f vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

/*
	Random
*/

sf::Vector2f VectorUtility::randomInRectf(sf::Rect<float> rect)
{
	return sf::Vector2f(MathsUtility::randFloat(rect.left, rect.width + rect.left),
						MathsUtility::randFloat(rect.top, rect.height + rect.top));
}

/*
	Colours
*/

sf::Vector3f VectorUtility::HSLToRGB(sf::Vector3f colour)
{
	if (colour.x < 0.0f) colour.x = 0.0f;
	if (colour.x > 360.0f) colour.x = 0.0f;
	
	if (colour.y < 0.0f) colour.y = 0.0f;
	if (colour.y > 1.0f) colour.y = 1.0f;

	if (colour.z < 0.0f) colour.z = 0.0f;
	if (colour.z > 1.0f) colour.z = 1.0f;

	float c = (1.0f - abs(2.0f * colour.z - 1.0f)) * colour.y;
	float x = c * (1.0f - abs(fmodf(colour.x / 60.0f, 2.0f) - 1.0f));
	float m = colour.z - c / 2.0f;

	sf::Vector3f finalColour;
	if (colour.x < 60.0f)
	{
		finalColour = sf::Vector3f(c, x, 0.0f);
	}
	else if (colour.x < 120.0f)
	{
		finalColour = sf::Vector3f(x, c, 0.0f);
	}
	else if (colour.x < 180.0f)
	{
		finalColour = sf::Vector3f(0.0f, c, x);
	}
	else if (colour.x < 240.0f)
	{
		finalColour = sf::Vector3f(0.0f, x, c);
	}
	else if (colour.x < 300.0f)
	{
		finalColour = sf::Vector3f(x, 0.0f, c);
	}
	else if (colour.x < 360.0f)
	{
		finalColour = sf::Vector3f(c, 0.0f, x);
	}

	finalColour += sf::Vector3f(m, m, m);

	return finalColour;
}

sf::Color VectorUtility::vectorToColour(sf::Vector3f colour, float transparency)
{
	return sf::Color(colour.x * 255, colour.y * 255, colour.z * 255, transparency * 255);
}