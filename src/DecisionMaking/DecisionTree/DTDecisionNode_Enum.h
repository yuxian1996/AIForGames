#pragma once

#include "DTDecisionNode.h"

#include <vector>
#include <functional>

class Context;

class DTDecisionNode_Enum : public DTDecisionNode
{
public:
	DTDecisionNode_Enum() = default;
	DTDecisionNode_Enum(const std::vector<DTNode*> & inChildren, const std::function<uint8_t(const Context* const)> inFunction)
		: DTDecisionNode(inChildren), mFunction(inFunction) {}
	virtual	~DTDecisionNode_Enum() override = default;

	virtual uint8_t MakeDecision(const Context* const ipContext) { return mFunction(ipContext); }

private:
	std::function<uint8_t(const Context* const)> mFunction;
};