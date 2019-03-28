#pragma once

#include "DTDecisionNode.h"

#include <functional>

class DTDecisionNode_Bool : public DTDecisionNode
{
public:
	DTDecisionNode_Bool() = default;
	DTDecisionNode_Bool(DTNode* ipFalseChild, DTNode* ipTrueChild, std::function<bool()> inFunction)
		: mDecisionFunction(inFunction)
	{
		mChildren.push_back(ipFalseChild);
		mChildren.push_back(ipTrueChild);
	}

	virtual ~DTDecisionNode_Bool() = default;
	virtual uint8_t MakeDecision() { return mDecisionFunction() ? 1 : 0; };

private:
	std::function<bool()> mDecisionFunction;

};