#pragma once

class Domino
{
public:
	Domino(unsigned left = 0, unsigned right = 0);

	inline unsigned left() { return _left; }
	inline unsigned right() { return _right; }

	inline bool isDouble() { return _left == _right; }
	inline bool contains(unsigned pip) { return _left == pip || _right == pip; }

	inline bool operator == (Domino& other)
	{
		return (_left == other.left()) && (_right == other.right());
	}

private:
	unsigned _left;
	unsigned _right;
};