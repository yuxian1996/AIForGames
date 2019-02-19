#include "Grid.h"

#include "Node.h"
#include "NodeRecord.h"

#include <iostream>
#include <unordered_set>
#include <algorithm>

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
	return mMap[index / mWidth][index % mWidth];
}

void Grid::SetCost(int index, float inCost)
{
	mMap[index / mWidth][index % mWidth] = inCost;
}

Direction Grid::GetDirection(int inSource, int inDest)
{
	int diff = inDest - inSource;
	if (diff == 1)
		return Direction::Right;
	if (diff == -1)
		return Direction::Left;
	if (diff == mWidth)
		return Direction::Down;
	if (diff == -mWidth)
		return Direction::Up;
	
	return Direction::Count;
}

Direction Grid::GetDirection(int ix1, int iy1, int ix2, int iy2)
{
	return GetDirection(iy1 * mWidth + ix1, iy2 * mWidth + ix2);
}

int Grid::GetNext(int inSource, Direction inDirection)
{
	switch (inDirection)
	{
	case Direction::Up:
		return inSource - mWidth;
	case Direction::Down:
		return inSource + mWidth;
	case Direction::Left:
		return inSource - 1;
	case Direction::Right:
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
		return inDest + mWidth;
	case Direction::Down:
		return inDest - mWidth;
	case Direction::Left:
		return inDest + 1;
	case Direction::Right:
		return inDest - 1;
	default:
		return inDest;
	}
}

bool Grid::FindPath(int inSource, int inDest, std::function<float(int, int)> inFunction)
{
	if (inSource == inDest)
	{
		std::cout << "[" << inSource % mWidth << ", " << inSource / mWidth << "]" << std::endl;
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
		int x = inSource % mWidth;
		int y = inSource / mWidth;

		for (int i = 0; i < (int)Direction::Count; i++)
		{
			int next = GetNext(currentNode, (Direction)i);
			if (closeList.find(next) != closeList.end())
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
		std::vector<int> path;
		int last = GetLast(currentNode, mRecords[currentNode].GetDirection());
		while (last != inSource)
		{
			last = GetLast(currentNode, mRecords[currentNode].GetDirection());
			path.push_back(currentNode);
			currentNode = last;
		}
		std::reverse(path.begin(), path.end());

		std::cout << "[" << last % mWidth << ", " << last / mWidth << "]";
		for (auto i : path)
		{
			std::cout << "->" << "[" << i % mWidth << ", " << i / mWidth << "]";
		}
		std::cout << std::endl;
		return true;
	}
}


