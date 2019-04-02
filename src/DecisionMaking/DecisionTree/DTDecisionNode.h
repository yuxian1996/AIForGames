#pragma once

#include "DTNode.h"

#include <vector>
#include <memory>
#include <cassert>

class Context;

class DTDecisionNode : public DTNode
{
public:
	DTDecisionNode() = default;
	DTDecisionNode(const std::vector<DTNode*> & inChildren): mChildren(inChildren) {}
	virtual ~DTDecisionNode() = default;

	virtual std::shared_ptr<Action> GetAction(const Context* const ipContext) override
	{
		uint8_t index = MakeDecision(ipContext);
		if (index < 0 || index >= mChildren.size())
			assert(false);
		return mChildren[index]->GetAction(ipContext);
	}

	virtual uint8_t MakeDecision(const Context* const ipContext) = 0;

protected:
	std::vector<DTNode*> mChildren;
};