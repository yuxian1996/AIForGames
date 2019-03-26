#include "ActionManager.h"

#include <algorithm>

void ActionManager::Run(float inDeltaTime)
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
		mpCurrentAction->Execute(inDeltaTime);
		if (mpCurrentAction->IsFinished())
		{
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
		mQueuedActions.erase(action);
	}

}

void ActionManager::AddAction(std::shared_ptr<Action> ipAction)
{
	mQueuedActions.insert(ipAction);
}
