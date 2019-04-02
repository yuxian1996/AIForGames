#pragma once

#include "DTDecisionNode.h"

#include <functional>

class Context;

class DTDecisionNode_Bool : public DTDecisionNode
{
public:
	DTDecisionNode_Bool() = default;
	DTDecisionNode_Bool(DTNode* ipFalseChild, DTNode* ipTrueChild, std::function<bool(const Context* const)> inFunction)
		: mDecisionFunction(inFunction)
	{
		mChildren.push_back(ipFalseChild);
		mChildren.push_back(ipTrueChild);
	}

	virtual ~DTDecisionNode_Bool() = default;
	virtual uint8_t MakeDecision(const Context* const ipContext) { return mDecisionFunction(ipContext) ? 1 : 0; };

private:
	std::function<bool(const Context* const)> mDecisionFunction;

};