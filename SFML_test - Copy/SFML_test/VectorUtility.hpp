#pragma once

#include <SFML/Graphics.hpp>

namespace
{
	//	2D float vectors
	const sf::Vector2f kUp2f = sf::Vector2f(0.0f, 1.0f);
	const sf::Vector2f kDown2f = sf::Vector2f(0.0f, -1.0f);
	const sf::Vector2f kLeft2f = sf::Vector2f(-1.0f, 0.0f);
	const sf::Vector2f kRight2f = sf::Vector2f(1.0f, 0.0f);
	
	//	2D int vectors
	const sf::Vector2i kUp2i = sf::Vector2i(0, 1);
	const sf::Vector2i kDown2i = sf::Vector2i(0, -1);
	const sf::Vector2i kLeft2i = sf::Vector2i(-1, 0);
	const sf::Vector2i kRight2i = sf::Vector2i(1, 0);

	//	2D unsigned vectors
	const sf::Vector2u kUp2u = sf::Vector2u(0, 1);
	const sf::Vector2u kRight2u = sf::Vector2u(1, 0);

	//	3D float vectors
	const sf::Vector3f kUp3f = sf::Vector3f(0.0f, 1.0f, 0.0f);
	const sf::Vector3f kDown3f = sf::Vector3f(0.0f, -1.0f, 0.0f);
	const sf::Vector3f kLeft3f = sf::Vector3f(-1.0f, 0.0f, 0.0f);
	const sf::Vector3f kRight3f = sf::Vector3f(1.0f, 0.0f, 0.0f);
	const sf::Vector3f kForward3f = sf::Vector3f(0.0f, 0.0f, 1.0f);
	const sf::Vector3f kBack3f = sf::Vector3f(0.0f, 0.0f, -1.0f);
	
	//	3D int vectors
	const sf::Vector3i kUp3i = sf::Vector3i(0, 1, 0);
	const sf::Vector3i kDown3i = sf::Vector3i(0, -1, 0);
	const sf::Vector3i kLeft3i = sf::Vector3i(-1, 0, 0);
	const sf::Vector3i kRight3i = sf::Vector3i(1, 0, 0);
	const sf::Vector3i kForward3i = sf::Vector3i(0, 0, 1);
	const sf::Vector3i kBack3i = sf::Vector3i(0, 0, -1);
}

class VectorUtility
{
public:
	//	Magnitude
	static float magnitude(sf::Vector3f vector);
	static float magnitude(sf::Vector3i vector);

	static float magnitude(sf::Vector2f vector);
	static float magnitude(sf::Vector2i vector);
	static float magnitude(sf::Vector2u vector);
	
	static float sqrMagnitude(sf::Vector3f vector);
	static float sqrMagnitude(sf::Vector3i vector);

	static float sqrMagnitude(sf::Vector2f vector);
	static float sqrMagnitude(sf::Vector2i vector);
	static float sqrMagnitude(sf::Vector2u vector);

	//	Distance

	//	Normalise
	static void normalise(sf::Vector3f &vector);
	static void normalise(sf::Vector2f &vector);

	static sf::Vector2f normalised(const sf::Vector2f vector);
	static sf::Vector3f normalised(const sf::Vector3f vector);

	//	Rotation
	static void rotate(sf::Vector2f &vector, float angle);
	static void rotate(sf::Vector2i &vector, float angle);

	static void rotate(sf::Vector3f &vector, sf::Vector3f axis, float angle);
	static void rotate(sf::Vector3i &vector, sf::Vector3f axis, float angle);
	
	static sf::Vector2f rotated(sf::Vector2f vector, float angle);
	static sf::Vector2i rotated(sf::Vector2i vector, float angle);

	static sf::Vector3f rotated(sf::Vector3f vector, sf::Vector3f axis, float angle);
	static sf::Vector3f rotated(sf::Vector3i vector, sf::Vector3f axis, float angle);

	//	Reflection
	static void reflect(sf::Vector2f &vector, sf::Vector2f normal);
	static void reflect(sf::Vector2i &vector, sf::Vector2f normal);

	static void reflect(sf::Vector3f &vector, sf::Vector3f normal);
	static void reflect(sf::Vector3i &vector, sf::Vector3f normal);
	
	static sf::Vector2f reflected(sf::Vector2f vector, sf::Vector2f normal);
	static sf::Vector2f reflected(sf::Vector2i vector, sf::Vector2f normal);

	static sf::Vector3f reflected(sf::Vector3f vector, sf::Vector3f normal);
	static sf::Vector3f reflected(sf::Vector3i vector, sf::Vector3f normal);

	//	Cross Product
	static sf::Vector3f cross(sf::Vector3f vector1, sf::Vector3f vector2);

	//	Dot Product
	static float dot(sf::Vector2f vector1, sf::Vector2f vector2);
	static float dot(sf::Vector3f vector1, sf::Vector3f vector2);

	//	Random
	static sf::Vector3f random3f(float maxLength, float minLength);
	static sf::Vector3f randomUnit3f();

	static sf::Vector3i random3i(int maxLength, int minLength);

	static sf::Vector2f random2f(float maxLength, float minLength);
	static sf::Vector2f randomInRectf(sf::Rect<float> rect);
	static sf::Vector2f randomUnit2f();

	static sf::Vector2i random2i(int maxLength, int minLength);
	static sf::Vector2i randomInRecti(sf::Rect<int> rect);

	static sf::Vector2u random2u(int maxLength, int minLength);
	static sf::Vector2u randomInRectu(sf::Rect<unsigned> rect);

	//	Colours
	static sf::Vector3f RGBToHSL(sf::Vector3f colour);
	static sf::Vector3f HSLToRGB(sf::Vector3f colour);

	//	Note: Loses transparency
	static sf::Vector3i colourToVectori(sf::Color colour);
	static sf::Color vectorToColour(sf::Vector3i colour, int transparency);

	//	Between 0 and 1
	static sf::Vector3i colourToVectorf(sf::Color colour);
	static sf::Color vectorToColour(sf::Vector3f colour, float transparency);
};