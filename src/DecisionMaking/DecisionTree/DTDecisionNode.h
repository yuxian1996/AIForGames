#pragma once

#include "DTNode.h"

#include <vector>
#include <memory>

class DTDecisionNode : public DTNode
{
public:
	DTDecisionNode() = default;
	virtual ~DTDecisionNode() = default;

	virtual std::shared_ptr<Action> GetAction() override
	{
		return mChildren[MakeDecision()]->GetAction();
	}

	virtual int MakeDecision() = 0;

protected:
	std::vector<DTNode*> mChildren;
};