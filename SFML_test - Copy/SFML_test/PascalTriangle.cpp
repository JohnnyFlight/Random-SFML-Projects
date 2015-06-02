#include "PascalTriangle.hpp"

PascalTriangle::PascalTriangle()
{
	_values.push_back(std::vector<long long unsigned>(1, 1));
	_depth = 1;
}

PascalTriangle::PascalTriangle(unsigned depth)
{
	_values.push_back(std::vector<long long unsigned>(1, 1));
	_depth = 1;

	for (unsigned i = 0; i < depth; i++)
	{
		addRow();
	}
}

long long unsigned PascalTriangle::getValue(unsigned x, unsigned y)
{
	//	Return 0 if invalid
	if (y > x) return 0;
	while (y > _depth)
	{
		addRow();
	}

	return _values[x][y];
}

void PascalTriangle::addRow()
{
	unsigned rowLength = _values.size() + 1;

	std::vector<long long unsigned> topRow = _values[_values.size() - 1];
	std::vector<long long unsigned> row = std::vector<long long unsigned>(rowLength, 0);

	for (unsigned i = 0; i < rowLength; i++)
	{
		if (i == 0)
		{
			row[i] = 1;
			continue;
		}

		if (i == rowLength - 1)
		{
			row[i] = 1;
			continue;
		}

		row[i] = topRow[i - 1] + topRow[i];
	}

	_values.push_back(row);
	_depth++;
}