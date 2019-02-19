#pragma once

#include <cmath>

class Node
{
public:
	Node(float ix, float iy) : x(ix), y(iy) {}
	float x, y;

	static float Distance(const Node& a, const Node& b)
	{
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}
};