#include "PixelBuffer.hpp"

#include "VectorUtility.hpp"

namespace
{
	const sf::Color kDefaultColour = sf::Color::Magenta;
}

PixelBuffer::PixelBuffer()
{
	_dimensions = sf::Vector3<unsigned>(0, 0, 0);

	initialise();
}

PixelBuffer::PixelBuffer(unsigned width, unsigned height, unsigned depth)
{
	_dimensions = sf::Vector3<unsigned>(width, height, depth);

	initialise();
}

void PixelBuffer::initialise()
{
	_data.resize(_dimensions.x * _dimensions.y * _dimensions.z * 4, 0);
}

sf::Uint8 *PixelBuffer::getPointer(unsigned layer)
{
	if (layer < _dimensions.z)
		return &_data[_dimensions.x * _dimensions.y * 4 * layer];
	else
		return NULL;
}

bool PixelBuffer::matches(sf::Color colour, unsigned x, unsigned y, unsigned z, bool matchAlpha)
{
	//	Check if pixel is in bounds
	if (x >= _dimensions.x) return false;
	if (y >= _dimensions.y) return false;
	if (z >= _dimensions.z) return false;

	unsigned position = z * _dimensions.x * _dimensions.y * 4 + y * _dimensions.x * 4 + x * 4;

	//	Check if colour matches
	if (colour.r != _data[position + 0]) return false;
	if (colour.g != _data[position + 1]) return false;
	if (colour.b != _data[position + 2]) return false;
	if (matchAlpha == true)
		if (colour.a != _data[position + 3]) return false;

	return true;
}

sf::Color PixelBuffer::getColour(unsigned x, unsigned y, unsigned z)
{
	//	Check if pixel is in bounds
	if (x >= _dimensions.x) return kDefaultColour;
	if (y >= _dimensions.y) return kDefaultColour;
	if (z >= _dimensions.z) return kDefaultColour;
	
	//	Create colour
	unsigned position = z * _dimensions.x * _dimensions.y * 4 + y * _dimensions.x * 4 + x * 4;

	sf::Color colour;
	colour.r = _data[position + 0];
	colour.r = _data[position + 1];
	colour.r = _data[position + 2];
	colour.r = _data[position + 3];

	//	Return colour
	return colour;
}

void PixelBuffer::setColour(sf::Color colour, unsigned x, unsigned y, unsigned z)
{
	//	Check if pixel is in bounds
	if (x >= _dimensions.x) return;
	if (y >= _dimensions.y) return;
	if (z >= _dimensions.z) return;

	unsigned position = z * _dimensions.x * _dimensions.y * 4 + y * _dimensions.x * 4 + x * 4;
	
	_data[position + 0] = colour.r;
	_data[position + 1] = colour.g;
	_data[position + 2] = colour.b;
	_data[position + 3] = colour.a;
}

void PixelBuffer::fill(sf::Color colour)
{
	for (unsigned i = 0; i < _data.size() / 4; i++)
	{
		_data[i * 4 + 0] = colour.r;
		_data[i * 4 + 1] = colour.g;
		_data[i * 4 + 2] = colour.b;
		_data[i * 4 + 3] = colour.a;
	}
}

void PixelBuffer::drawLine(sf::Color colour, sf::Vector3<unsigned> start, sf::Vector3<unsigned> end, float thickness)
{
	//	Check if each point is within boundaries
	if (start.x > _dimensions.x) return;
	if (start.y > _dimensions.y) return;
	if (start.z > _dimensions.z) return;
	
	if (end.x > _dimensions.x) return;
	if (end.y > _dimensions.y) return;
	if (end.z > _dimensions.z) return;

	//	Find top-left-front point
	sf::Vector3i point;
	if (start.x < end.x) point.x = start.x;
	else point.x = end.x;

	if (start.y < end.y) point.y = start.y;
	else point.y = end.y;

	if (start.x < end.x) point.x = start.x;
	else point.x = end.x;

	//	Create line
	sf::Vector3<int> line = sf::Vector3i(end - start);

	//	Check distance from line of each point
	//	d = ||(a - p)  - ((a - p) . n) * n||
	for (unsigned i = 0; i <= abs(line.x); i++)
	{
		for (unsigned j = 0; j <= abs(line.y); j++)
		{
			for (unsigned k = 0; k <= abs(line.z); k++)
			{
				sf::Vector3i position = sf::Vector3i(i, j, k) + point;
				float distanceSqr = VectorUtility::sqrMagnitude((sf::Vector3f(sf::Vector3i(start) - position)) - (VectorUtility::dot(sf::Vector3f(sf::Vector3i(start) - position), VectorUtility::normalised(sf::Vector3f(line)))) * VectorUtility::normalised(sf::Vector3f(line)));
				if (distanceSqr < thickness * thickness)
				{
					setColour(colour, position.x, position.y, position.z);
				}
			}
		}
	}
}