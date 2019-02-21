#include "Grid.h"

#include "Node.h"
#include "NodeRecord.h"

#include "ofPixels.h"
#include "ofGraphics.h"

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <fstream>

const float Grid::MaxCost = 255.0f;

Grid::Grid(float ** ipMap, int inWidth, int inHeight) : mWidth(inWidth), mHeight(inHeight)
{
	mMap = new float*[inHeight];
	for (int i = 0; i < inHeight; i++)
	{
		mMap[i] = new float[inWidth];
		for (int j = 0; j < inWidth; j++)
		{
			mMap[i][j] = ipMap[i][j];
		}
	}
}

Grid::Grid(int inWidth, int inHeight) : mWidth(inWidth), mHeight(inHeight)
{
	mMap = new float*[inHeight];
	for (int i = 0; i < inHeight; i++)
	{
		mMap[i] = new float[inWidth];
		for (int j = 0; j < inWidth; j++)
		{
			mMap[i][j] = 1;		// default cost is 1
		}
	}
}

Grid::Grid(const char * const inPath, int inGridSize, int inImageWidth, int inImageHeight)
	: mGridSize(inGridSize)
{
	mImage.loadImage(inPath);
	if (inImageWidth > 0 && inImageHeight > 0)
	{
		mImage.resize(inImageWidth + inImageWidth % mGridSize, inImageHeight + inImageHeight % mGridSize);
	}
	mWidth = mImage.getWidth();
	mHeight = mImage.getHeight();

	mGridWidth = mWidth / mGridSize;
	mGridHeight = mHeight / mGridSize;
	mMap = new float*[mGridHeight];
	for (int i = 0; i < mGridHeight; i++)
	{
		mMap[i] = new float[mGridWidth];
		for (int j = 0; j < mGridWidth; j++)
		{
			// get num of blocks
			int blockCount = 0;
			int numGridPixels = mGridSize * mGridSize;
			for (int k = 0; k < numGridPixels; k++)
			{
				auto color = mImage.getColor(j * mGridSize + k % mGridSize, i * mGridSize + k / mGridSize);
				if (color.getBrightness() < 100)
					blockCount++;
			}
			// set the grid a obstacle
			if (blockCount > numGridPixels / 4)
			{
				mMap[i][j] = 256;
			}
			else
				mMap[i][j] = 1;
		}
	}
}

Grid * Grid::LoadFromImage(const char * const inPath)
{
	Grid* grid = new Grid(inPath, 10, 800, 800);
	return grid;
}

void Grid::SetCost(int x, int y, float cost)
{
	mMap[y][x] = cost;
}

float Grid::GetCost(int x, int y)
{
	return mMap[y][x];
}

float Grid::GetCost(int index)
{
	return mMap[index / mGridWidth][index % mGridWidth];
}

void Grid::SetCost(int index, float inCost)
{
	mMap[index / mGridWidth][index % mGridWidth] = inCost;
}

Direction Grid::GetDirection(int inSource, int inDest)
{
	int diff = inDest - inSource;
	if (diff == 1)
		return Direction::Right;
	if (diff == -1)
		return Direction::Left;
	if (diff == mGridWidth)
		return Direction::Down;
	if (diff == -mGridWidth)
		return Direction::Up;
	
	return Direction::Count;
}

Direction Grid::GetDirection(int ix1, int iy1, int ix2, int iy2)
{
	return GetDirection(iy1 * mGridWidth + ix1, iy2 * mGridWidth + ix2);
}

int Grid::GetNext(int inSource, Direction inDirection)
{
	switch (inDirection)
	{
	case Direction::Up:
		if (inSource / mGridWidth == 0)
			return -1;
		return inSource - mGridWidth;
	case Direction::Down:
		if (inSource / mGridWidth == mGridHeight - 1)
			return -1;
		return inSource + mGridWidth;
	case Direction::Left:
		if (inSource % mGridWidth == 0)
			return -1;
		return inSource - 1;
	case Direction::Right:
		if (inSource % mGridWidth == mGridWidth - 1)
			return -1;
		return inSource + 1;
	default:
		return inSource;
	}
}

int Grid::GetLast(int inDest, Direction inDirection)
{
	switch (inDirection)
	{
	case Direction::Up:
		if (inDest / mGridWidth == mGridHeight - 1)
			return -1;
		return inDest + mGridWidth;
	case Direction::Down:
		if (inDest / mGridWidth == 0)
			return -1;
		return inDest - mGridWidth;
	case Direction::Left:
		if (inDest % mGridWidth == mGridWidth - 1)
			return -1;
		return inDest + 1;
	case Direction::Right:
		if (inDest % mGridWidth == 0)
			return -1;
		return inDest - 1;
	default:
		return inDest;
	}
}

bool Grid::FindPath(int inSource, int inDest, std::function<float(int, int)> inFunction)
{
	mPath.clear();
	mRecords.clear();
	if (inSource < 0 || inSource >= mGridWidth * mGridHeight || inDest < 0 || inDest >= mGridWidth * mGridHeight)
		return false;
	if (inSource == inDest)
	{
		//std::cout << "[" << inSource % mWidth << ", " << inSource / mWidth << "]" << std::endl;
		mPath.push_back(inSource);
		return true;
	}
	std::unordered_set<int> closeList;
	std::vector<int> openList;
	openList.push_back(inSource);

	int currentNode = -1;

	while (openList.size() != 0)
	{
		currentNode = openList.front();
		openList.erase(openList.begin());

		if (currentNode == inDest)
			break;

		// get all children
		int x = inSource % mGridWidth;
		int y = inSource / mGridWidth;

		for (int i = 0; i < (int)Direction::Count; i++)
		{
			int next = GetNext(currentNode, (Direction)i);
			if (next < 0 || closeList.find(next) != closeList.end() || GetCost(next) > MaxCost)
				continue;

			float h = inFunction(next, inDest);
			float g = mRecords[currentNode].GetCostSoFar() + GetCost(next);
			float f = h + g;

			if (mRecords.find(next) == mRecords.end())
			{
				// add new record
				mRecords[next] = GridRecord(next, GetDirection(currentNode, next), g, f);
				openList.push_back(next);
			}
			else if (mRecords[next].GetEstimatedTotal() > f)
			{
				// replace old record
				mRecords[next].SetCostSoFar(g);
				mRecords[next].SetEstimatedTotal(f);
				mRecords[next].SetDirection(GetDirection(currentNode, next));
			}
		}
		// resort
		auto& records = mRecords;
		std::sort(openList.begin(), openList.end(), [&records](int a, int b)
		{
			return records[a].GetEstimatedTotal() < records[b].GetEstimatedTotal();
		});
		closeList.insert(currentNode);
	}

	if (currentNode != inDest)
	{
		std::cout << "Can't find a valid path!" << std::endl;
		return false;
	}
	else
	{
		// output path
		//std::vector<int> path;
		int last = GetLast(currentNode, mRecords[currentNode].GetDirection());
		while (last != inSource)
		{
			last = GetLast(currentNode, mRecords[currentNode].GetDirection());
			mPath.push_back(currentNode);
			currentNode = last;
		}

		mPath.push_back(last);
		std::reverse(mPath.begin(), mPath.end());

		if (mPath.size() == 1)
			return true;

		// reset path to corners
		std::vector<int> corners;
		int x = mPath[0] % mGridWidth;
		int y = mPath[0] / mGridWidth;
		corners.push_back(mPath[0]);
		corners.push_back(mPath[1]);
		bool isHorizontal = abs(corners[0] - corners[1]) == 1;
		for(int i = 2; i < mPath.size(); i++)
		{
			if (isHorizontal)
			{
				if(abs(mPath[i] - corners[corners.size() - 1]) == 1)
					corners[corners.size() - 1] = mPath[i];
				else
				{
					corners.push_back(mPath[i]);
					isHorizontal = false;
				}
			}
			else
			{
				if (abs(mPath[i] - corners[corners.size() - 1]) == mGridWidth)
					corners[corners.size() - 1] = mPath[i];
				else
				{
					corners.push_back(mPath[i]);
					isHorizontal = true;
				}
			}
		}

		mPath.swap(corners);
		/*for (auto point : mPath)
		{
			std::cout << "[" << point % mGridWidth << ", " << point / mGridWidth << "] -> ";
		}
		std::cout << std::endl;*/

		return true;
	}
}

void Grid::Draw()
{
	ofSetColor(255);
	mImage.draw(0, 0);
}

void Grid::DrawPath()
{
	ofSetColor(255, 0, 0, 255);
	if (mPath.size() == 0)
		return;
	if(mPath.size() == 1)
		ofDrawCircle(glm::vec2((mPath[0] % mGridWidth + 0.5) * mGridSize, (mPath[0] / mGridWidth + 0.5) * mGridSize), mGridSize / 2);
	else
	{
		for(int i = 0; i < mPath.size() - 1; i++)
		{
			ofSetLineWidth(mGridSize / 2);
			ofDrawLine(glm::vec2((mPath[i] % mGridWidth + 0.5) * mGridSize, (mPath[i] / mGridWidth + 0.5) * mGridSize),
				glm::vec2((mPath[i + 1] % mGridWidth + 0.5) * mGridSize, (mPath[i + 1] / mGridWidth + 0.5) * mGridSize));
		}
	}
	
}


