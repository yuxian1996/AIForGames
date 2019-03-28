#pragma once

#include "DTDecisionNode.h"

#include <vector>
#include <functional>

class DTDecisionNode_Enum : public DTDecisionNode
{
public:
	DTDecisionNode_Enum() = default;
	DTDecisionNode_Enum(const std::vector<DTNode*> & inChildren, const std::function<uint8_t()> inFunction)
		: DTDecisionNode(inChildren), mFunction(inFunction) {}
	virtual	~DTDecisionNode_Enum() override = default;

	virtual uint8_t MakeDecision() { return mFunction(); }

private:
	std::function<uint8_t()> mFunction;
};