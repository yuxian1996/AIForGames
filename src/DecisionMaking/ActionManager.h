#pragma once

#include "Action.h"

#include <set>
#include <vector>
#include <memory>

class ActionCompare
{
public:
	bool operator() (const std::shared_ptr<Action> lhs, const std::shared_ptr<Action> rhs)
	{
		return lhs->GetPriority() < rhs->GetPriority();
	}
};

class ActionManager
{
public:
	ActionManager() = default;
	~ActionManager() = default;

	void Run(float inDeltaTime);
	void AddAction(std::shared_ptr<Action>);

	std::set<std::shared_ptr<Action>, ActionCompare> mQueuedActions;
	std::shared_ptr<Action> mpCurrentAction;
	std::vector<std::shared_ptr<Action>> mPendingExpiredActions;
};