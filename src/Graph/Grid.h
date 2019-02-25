#pragma once

#include "NodeRecord.h"

#include "ofImage.h"

#include <unordered_map>
#include <string>
#include <functional>

class Grid
{
public:
	Grid(float** ipMap, int inWidth, int inHeight);
	Grid(int inWidth, int inHeight);
	Grid(const char* const inPath, int inGridSize, int inImageWidth = 0, int inImageHeight = 0);

	// Static
	static Grid* LoadFromImage(const char* const inPath);

	// Getter & Setter
	void SetCost(int x, int y, float cost);
	float GetCost(int x, int y);
	float GetCost(int index);
	void SetCost(int index, float inCost);
	void SetImage(ofShortPixels inPixels) { mImage.loadImage("download.png"); }
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	int GetGridWidth() { return mGridWidth; }
	int GetGridHeight() { return mGridHeight; }
	ofImage& GetImage() { return mImage; }
	int GetGridSize() { return mGridSize; }
	const std::vector<int> GetPath() { return mPath; }

	Direction GetDirection(int inSource, int inDest);
	Direction GetDirection(int ix1, int iy1, int ix2, int iy2);
	int GetNext(int inSource, Direction inDirection);
	int GetLast(int inDest, Direction inDirection);

	void GirdIndexToXY(int index, int& oX, int& oY);

	// Find Path
	bool FindPath(int inSource, int inDest, std::function<float(int, int)> inFunction);

	// Draw Grid
	void Draw();
	// Draw Path
	void DrawPath();

	// Const
	static const float MaxCost;

private:
	float** mMap;		// cost of each grid
	int mWidth, mHeight;
	int mGridSize = 1;
	int mGridWidth, mGridHeight;
	std::unordered_map<int, GridRecord> mRecords;
	ofImage mImage;
	std::vector<int> mPath;
};