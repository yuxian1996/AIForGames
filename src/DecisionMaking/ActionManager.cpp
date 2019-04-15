#include "ActionManager.h"
#include "Learning/ID3.h"

#include <chrono>
#include <algorithm>

void ActionManager::Init(DecisionTree * ipDecisionTree, Context * ipContext, BehaviorTree* ipBehaviorTree)
{
	mpDecisionTree = ipDecisionTree;
	mpContext = ipContext;
	mpBehaviorTree = ipBehaviorTree;

	//id3 = new ID3;
	//id3->Init();
}

void ActionManager::Run(float inDeltaTime)
{
	static int DTTime = 0;
	static int BTTime = 0;
	static int BTCount = 0;
	static int DTCount = 0;
	std::shared_ptr<Action> action = nullptr;
	if (mpDecisionTree != nullptr)
	{
		auto beginClock = std::chrono::high_resolution_clock::now();
		action = mpDecisionTree->GetAction(mpContext);
		auto endClock = std::chrono::high_resolution_clock::now();
		DTTime += std::chrono::duration_cast<std::chrono::microseconds>(endClock - beginClock).count();
		DTCount++;

		std::cout << "DTTime: " << (float)DTTime / DTCount << std::endl;

	}
	else if (mpBehaviorTree != nullptr)
	{
		auto beginClock = std::chrono::high_resolution_clock::now();
		action = mpBehaviorTree->GetAction(mpContext);
		auto endClock = std::chrono::high_resolution_clock::now();
		BTTime += std::chrono::duration_cast<std::chrono::microseconds>(endClock - beginClock).count();
		BTCount++;

		std::cout << "BTTime: " << (float)BTTime / BTCount << std::endl;

	}


	if (action != nullptr)
	{
		AddAction(action);
		id3->SaveAttribute(mpContext);
		id3->SaveAction(action);
	}

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
