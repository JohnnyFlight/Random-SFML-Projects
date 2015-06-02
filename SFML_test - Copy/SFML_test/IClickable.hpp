#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

#include <SFML\System.hpp>

class IClickable
{
public:
	virtual bool clicked(unsigned x, unsigned y) = 0;
};

#endif