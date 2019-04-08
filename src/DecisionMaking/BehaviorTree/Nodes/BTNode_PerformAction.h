#pragma once

#include "../BTNode.h"
#include "../../Action.h"

#include <memory>

class BTNode_PerformAction : public BTNode
{
public:
	BTNode_PerformAction() = default;
	virtual ~BTNode_PerformAction() override = default;

	virtual BT_State OnExecute(BTTick inTick) override
	{
		inTick.GetBlackboard()->Set("Action", mAction);
		return BT_State::SUCCESS;
	}

private:
	std::shared_ptr<Action> mAction;
};