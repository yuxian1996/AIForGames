#pragma once

#include "DTNode.h"

#include <vector>
#include <memory>
#include <cassert>

class DTDecisionNode : public DTNode
{
public:
	DTDecisionNode() = default;
	DTDecisionNode(const std::vector<DTNode*> & inChildren): mChildren(inChildren) {}
	virtual ~DTDecisionNode() = default;

	virtual std::shared_ptr<Action> GetAction() override
	{
		uint8_t index = MakeDecision();
		if (index < 0 || index >= mChildren.size())
			assert(false);
		return mChildren[index]->GetAction();
	}

	virtual uint8_t MakeDecision() = 0;

protected:
	std::vector<DTNode*> mChildren;
};