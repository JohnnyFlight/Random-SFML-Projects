#ifndef MASK_HPP
#define MASK_HPP

#include <vector>

class Mask
{
protected:
	std::vector<std::vector<bool>> _mask;
	unsigned _width;
	unsigned _height;

public:
	Mask();
	Mask(unsigned width, unsigned height, bool invertValues = false);

	bool isValid(unsigned x, unsigned y);
	bool setState(unsigned x, unsigned y, bool state);

	inline unsigned getWidth() { return _width; }
	inline unsigned getHeight() { return _height; }

	//	Some static functions to create default masks
	static Mask create4PlayerMask(bool invertValues = false);
	static Mask create5PlayerMask(bool invertValues = false);
};

#endif