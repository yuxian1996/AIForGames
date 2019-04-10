#pragma once

#include "BTNode.h"
#include "BTTick.h"
#include "../Action.h"
#include "Blackboard.h"

#include <memory>

class Context;

class BehaviorTree
{
public:
	BehaviorTree() = default;
	virtual ~BehaviorTree()
	{
		for (auto node : mNodes)
		{
			delete node;
		}
		mNodes.clear();
		mpRoot = nullptr;

		if (mpBlackboard != nullptr)
		{
			delete mpBlackboard;
			mpBlackboard = nullptr;
		}
	}

	virtual void Init() = 0;

	void SetBlackboard(Blackboard* ipBlackboard) { mpBlackboard = ipBlackboard; }
	Blackboard* GetBlackboard() { return mpBlackboard; }

	std::shared_ptr<Action> GetAction(const Context* ipContext) 
	{
		BTTick tick(mpBlackboard, this, ipContext);
		mpRoot->Run(tick);
		return *reinterpret_cast<std::shared_ptr<Action>*>(mpBlackboard->Get("Action"));
	}


protected:
	BTNode* mpRoot;
	Blackboard* mpBlackboard;
	std::vector<BTNode*> mNodes;
};