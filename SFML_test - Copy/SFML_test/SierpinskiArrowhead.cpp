#include "SierpinskiArrowhead.hpp"

SierpinskiArrowhead::SierpinskiArrowhead()
{
	_depth = 0;

	_points.push_back(sf::Vector2f(0.0f, 0.0f));
	_points.push_back(sf::Vector2f(1.0f, 0.0f));
}

SierpinskiArrowhead::SierpinskiArrowhead(unsigned depth)
{
	_depth = 0;
	
	_points.push_back(sf::Vector2f(0.0f, 0.0f));
	_points.push_back(sf::Vector2f(1.0f, 0.0f));

	for (unsigned i = 0; i < depth; i++)
	{
		increaseDepth();
	}
}

SierpinskiArrowhead::SierpinskiArrowhead(sf::Vector2f start, sf::Vector2f end)
{
	_depth = 0;

	_points.push_back(start);
	_points.push_back(end);
}

SierpinskiArrowhead::SierpinskiArrowhead(sf::Vector2f start, sf::Vector2f end, unsigned depth)
{
	_depth = 0;

	_points.push_back(start);
	_points.push_back(end);

	for (unsigned i = 0; i < depth; i++)
	{
		increaseDepth();
	}
}

void SierpinskiArrowhead::increaseDepth()
{
	std::vector<sf::Vector2f> points;

	int expandLeft = _depth % 2;
	for (unsigned i = 1; i < _points.size(); i++)
	{
		//	Get p1 and p2
		sf::Vector2f p1 = _points[i - 1];
		sf::Vector2f p2 = _points[i];

		sf::Vector2f l1 = p2 - p1;

		sf::Vector2f p3 = p1 + (l1 / 2.0f);

		sf::Vector2f l2;
		if (expandLeft == 1)
		{
			l2 = sf::Vector2f(-l1.y, l1.x);
			expandLeft = 0;
		}
		else
		{
			l2 = sf::Vector2f(l1.y, -l1.x);
			expandLeft = 1;
		}

		float l2Mag = sqrt(l2.x * l2.x + l2.y * l2.y);
		//l2 /= l2Mag;
		//l2 *= l2Mag * sqrt(3.0f);
		l2 *= sqrt(3.0f) / 2.0f;

		sf::Vector2f p4 = p3 + l2;

		sf::Vector2f l3 = p4 - p1;
		sf::Vector2f l4 = p4 - p2;

		sf::Vector2f p5 = p1 + (l3 / 2.0f);
		sf::Vector2f p6 = p2 + (l4 / 2.0f);

		points.push_back(p1);
		points.push_back(p5);
		points.push_back(p6);
	}

	//	Push final point onto points
	points.push_back(*(_points.end() - 1));

	_points.clear();
	_points = points;

	_depth++;
}