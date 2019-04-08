#pragma once

#include "BTNode_Composite.h"
#include "../BTTick.h"
#include "../Blackboard.h"

class BTNode_Selector : public BTNode_Composite
{
public:
	BTNode_Selector() = default;
	virtual ~BTNode_Selector() override = default;


protected:
	virtual void OnOpen(BTTick inTick) override
	{
		inTick.GetBlackboard()->Set("runningChild", 0, ID);
	}

	virtual BT_State OnExecute(BTTick inTick) override
	{
		uint8_t runningChild = *reinterpret_cast<uint8_t*>(inTick.GetBlackboard()->Get("runningChild", ID));
		auto children = GetChildren();
		for (int i = runningChild; i < children.size(); i++)
		{
			BT_State state = children[i]->Run(inTick);
			if (state == BT_State::FAILURE)
			{
				if (state == BT_State::RUNNING)
					inTick.GetBlackboard()->Set("runningChild", i, ID);
				return state;
			}
		}

		return BT_State::FAILURE;
	}

};