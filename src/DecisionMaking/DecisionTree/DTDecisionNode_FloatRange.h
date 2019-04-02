#pragma once

#include "DTDecisionNode.h"

#include <vector>
#include <functional>

class Context;

class DTDecisionNode_FloatRange : public DTDecisionNode
{
public:
	DTDecisionNode_FloatRange() = default;
	DTDecisionNode_FloatRange(const std::vector<std::pair<float, float>>& inRanges, const std::function<float(const Context* const)>& inFunction)
		: mRanges(inRanges), mFunction(inFunction) {}
	virtual ~DTDecisionNode_FloatRange() override = default;

	virtual uint8_t MakeDecision(const Context* const ipContext) override
	{
		float value = mFunction(ipContext);
		for(int i = 0; i < mRanges.size(); i++)
		{
			if (value >= mRanges[i].first && value <= mRanges[i].second)
				return i;
		}

		return 0;
	}

private:
	std::vector<std::pair<float, float>> mRanges;
	std::function<float(const Context* const)> mFunction;
};