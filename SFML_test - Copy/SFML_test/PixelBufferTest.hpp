#pragma once

#include "Application.hpp"
#include "PixelBuffer.hpp"

#include "DragonSpiral.hpp"

class PixelBufferTest : public Application
{
public:
	PixelBufferTest(unsigned width, unsigned height, std::string name);

	void initialise();

private:
	void update();
	void draw();

	DragonSpiral _dragon;

	sf::RectangleShape _shape;
	sf::Texture _texture;
	PixelBuffer _buffer;
};