#pragma once

#include "Edge.h"

class NodeRecord
{
public:
	NodeRecord(int inNode, Edge inIncomingEdge, float inCostSoFar, float inEstimatedTotal) :
		mNode(inNode), mIncomingEdge(inIncomingEdge), mCostSoFar(inCostSoFar), mEstimatedTotal(inEstimatedTotal)
	{}

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