#include "Mask.hpp"

namespace
{
	const unsigned k4PlayerBoardWidth = 7;
}

Mask::Mask()
{
	
}

Mask::Mask(unsigned width, unsigned height, bool invertValues)
{
	_width = width;
	_height = height;

	_mask = std::vector<std::vector<bool>>(width);
	for (unsigned i = 0; i < _mask.size(); i++)
	{
		_mask[i] = std::vector<bool>(height, !invertValues);
	}
}

bool Mask::isValid(unsigned x, unsigned y)
{
	if (x >= _mask.size()) return false;
	if (_mask.empty()) return false;
	if (y >= _mask[0].size()) return false;

	return _mask[x][y];
}

bool Mask::setState(unsigned x, unsigned y, bool state)
{
	if (x >= _mask.size()) return false;
	if (_mask.empty()) return false;
	if (y >= _mask[0].size()) return false;

	_mask[x][y] = state;

	return true;
}

Mask Mask::create4PlayerMask(bool invertValues)
{
	Mask mask = Mask(5, 5, invertValues);

	mask.setState(0, 0, invertValues);
	mask.setState(0, 4, invertValues);
	mask.setState(4, 0, invertValues);
	mask.setState(4, 1, invertValues);
	mask.setState(4, 3, invertValues);
	mask.setState(4, 4, invertValues);

	return mask;
}

Mask Mask::create5PlayerMask(bool invertValues)
{
	Mask mask = Mask();

	return mask;
}