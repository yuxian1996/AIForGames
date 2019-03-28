#pragma once

#include "DTDecisionNode.h"

#include <vector>
#include <functional>

class DTDecisionNode_FloatRange : public DTDecisionNode
{
public:
	DTDecisionNode_FloatRange() = default;
	DTDecisionNode_FloatRange(const std::vector<std::pair<float, float>>& inRanges, const std::function<float()>& inFunction)
		: mRanges(inRanges), mFunction(inFunction) {}
	virtual ~DTDecisionNode_FloatRange() override = default;

	virtual uint8_t MakeDecision() override
	{
		float value = mFunction();
		for(int i = 0; i < mRanges.size(); i++)
		{
			if (value >= mRanges[i].first && value <= mRanges[i].second)
				return i;
		}

		return 0;
	}

private:
	std::vector<std::pair<float, float>> mRanges;
	std::function<float()> mFunction;
};