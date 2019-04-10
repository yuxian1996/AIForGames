#pragma once

#include "Action.h"
#include "DecisionTree/DecisionTree.h"
#include "BehaviorTree/BehaviorTree.h"

#include <set>
#include <vector>
#include <memory>

class ActionCompare
{
public:
	bool operator() (const std::shared_ptr<Action> lhs, const std::shared_ptr<Action> rhs) const
	{
		return lhs->GetPriority() < rhs->GetPriority();
	}
};

class ActionManager
{
public:
	ActionManager() = default;
	~ActionManager() = default;

	void Init(DecisionTree* ipDecisionTree, Context* ipContext, BehaviorTree* ipBehaviorTree);
	void Run(float inDeltaTime);
	void AddAction(std::shared_ptr<Action>);

	std::set<std::shared_ptr<Action>, ActionCompare> mQueuedActions;
	std::shared_ptr<Action> mpCurrentAction;
	std::vector<std::shared_ptr<Action>> mPendingExpiredActions;

private:
	void RunAction(float inDeltaTime);

	DecisionTree* mpDecisionTree;
	Context* mpContext;
	BehaviorTree* mpBehaviorTree;

};