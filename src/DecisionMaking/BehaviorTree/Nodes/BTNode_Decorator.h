#pragma once

#include "../BTNode.h"
#include <functional>

class Context;

class BTNode_Decorator : public BTNode
{
public:
	BTNode_Decorator() = default;
	virtual ~BTNode_Decorator() override = default;

	void SetChild(BTNode* ipNode) { mChildren.push_back(ipNode); }
	void SetFunction(std::function<bool(const Context*)> inFunction) { mFunction = inFunction; }

protected:
	virtual BT_State OnExecute(BTTick inTick) override
	{
		if (mChildren.size() <= 0)
			return BT_State::BTERROR;
		
		if (mFunction(inTick.GetContext()))
		{
			return mChildren[0]->Run(inTick);
		}
		else
			return BT_State::FAILURE;
	}

private:
	std::function<bool(const Context*)> mFunction;
};