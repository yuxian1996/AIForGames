#pragma once

#include "Edge.h"

enum class Direction
{
	Up,
	Down,
	Left,
	Right,
	Count
};

class NodeRecord
{
public:
	NodeRecord(int inNode, Edge inIncomingEdge, float inCostSoFar, float inEstimatedTotal) :
		mNode(inNode), mIncomingEdge(inIncomingEdge), mCostSoFar(inCostSoFar), mEstimatedTotal(inEstimatedTotal)
	{}
	NodeRecord() = default;
	Edge GetInComingEdge() const { return mIncomingEdge; }
	float GetCostSoFar() const { return mCostSoFar; }
	float GetEstimatedTotal() const { return mEstimatedTotal; }

	void SetIncomingEdge(const Edge& inEdge) { mIncomingEdge = inEdge; }
	void SetCostSoFar(const float inCostSoFar) {mCostSoFar = inCostSoFar; }
	void SetEstimatedTotal(const float inEstimatedTotal) { mEstimatedTotal = inEstimatedTotal; }

private:
	int mNode;
	Edge mIncomingEdge;
	float mCostSoFar;
	float mEstimatedTotal;
};

class GridRecord
{
public:
	GridRecord(int inNode, Direction inDirection, float inCostSoFar, float inEstimatedTotal) :
		mNode(inNode), mDirection(inDirection), mCostSoFar(inCostSoFar), mEstimatedTotal(inEstimatedTotal)
	{}
	GridRecord() = default;
	Direction GetDirection() const { return mDirection; }
	float GetCostSoFar() const { return mCostSoFar; }
	float GetEstimatedTotal() const { return mEstimatedTotal; }

	void SetDirection(const Direction inDirection) { mDirection = inDirection; }
	void SetCostSoFar(const float inCostSoFar) { mCostSoFar = inCostSoFar; }
	void SetEstimatedTotal(const float inEstimatedTotal) { mEstimatedTotal = inEstimatedTotal; }

private:
	int mNode;
	Direction mDirection;
	float mCostSoFar;
	float mEstimatedTotal;
};