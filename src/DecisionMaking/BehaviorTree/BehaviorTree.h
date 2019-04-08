#pragma once

#include "BTNode.h"
#include "BTTick.h"
#include "../Action.h"
#include "Blackboard.h"

#include <memory>

class BehaviorTree
{
public:
	BehaviorTree() = default;
	virtual ~BehaviorTree() = default;

	virtual void Init() = 0;

	std::shared_ptr<Action> GetAction() 
	{
		BTTick tick(mpBlackboard, this);
		mpRoot->Run(tick);
		return *reinterpret_cast<std::shared_ptr<Action>*>(mpBlackboard->Get("Action"));
	}


private:
	BTNode* mpRoot;
	Blackboard* mpBlackboard;
};