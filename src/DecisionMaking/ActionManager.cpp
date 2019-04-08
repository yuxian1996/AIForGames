#include "ActionManager.h"

#include <algorithm>

void ActionManager::Init(DecisionTree * ipDecisionTree, Context * ipContext)
{
	mpDecisionTree = ipDecisionTree;
	mpContext = ipContext;
}

void ActionManager::Run(float inDeltaTime)
{
	auto action = mpDecisionTree->GetAction(mpContext);
	AddAction(action);

	RunAction(inDeltaTime);
}

void ActionManager::RunAction(float inDeltaTime)
{
	// move queued actions to current actions
	if (mpCurrentAction == nullptr && mQueuedActions.size() > 0)
	{
		auto nextAction = *mQueuedActions.begin();
		mpCurrentAction = nextAction;
		mQueuedActions.erase(nextAction);
	}

	// execute actions
	if (mpCurrentAction != nullptr)
	{
		mpCurrentAction->Execute(inDeltaTime, mpContext);
		if (mpCurrentAction->IsFinished())
		{
			mpCurrentAction->Reset();
			mpCurrentAction = nullptr;
		}
	}

	// queued actions wait
	for (auto action : mQueuedActions)
	{
		action->Wait(inDeltaTime);
		if (action->ShouldExpire())
		{
			mPendingExpiredActions.push_back(action);
		}
	}

	// remove expired actions
	std::sort(mPendingExpiredActions.begin(), mPendingExpiredActions.end());
	for (auto action : mPendingExpiredActions)
	{
		action->Reset();
		mQueuedActions.erase(action);
	}

}

void ActionManager::AddAction(std::shared_ptr<Action> ipAction)
{
	if(mQueuedActions.find(ipAction) == mQueuedActions.end())
		mQueuedActions.insert(ipAction);
}
