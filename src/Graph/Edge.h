#pragma once

class Edge
{
public:
	Edge(int inSource, int inDest, float inCost) : mSource(inSource), mDest(inDest), mCost(inCost){}
	Edge() = default;
	float GetCost() const { return mCost; }
	int GetSource() const { return mSource; }
	int GetDest() const { return mDest; }

private:
	int mSource;
	int mDest;
	float mCost;
};