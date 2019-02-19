#pragma once

#include "NodeRecord.h"

#include <unordered_map>
#include <string>
#include <functional>

class Grid
{
public:
	Grid(float** ipMap, int inWidth, int inHeight);
	Grid(int inWidth, int inHeight);

	// Getter & Setter
	void SetCost(int x, int y, float cost);
	float GetCost(int x, int y);
	float GetCost(int index);
	void SetCost(int index, float inCost);

	Direction GetDirection(int inSource, int inDest);
	Direction GetDirection(int ix1, int iy1, int ix2, int iy2);
	int GetNext(int inSource, Direction inDirection);
	int GetLast(int inDest, Direction inDirection);

	// Find Path
	bool FindPath(int inSource, int inDest, std::function<float(int, int)> inFunction);

private:
	float** mMap;		// cost of each grid
	int mWidth, mHeight;
	std::unordered_map<int, GridRecord> mRecords;
};