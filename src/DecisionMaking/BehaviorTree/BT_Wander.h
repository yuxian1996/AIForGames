#pragma once

#include "BehaviorTree.h"
#include "Nodes/BTNode_Selector.h"
#include "Nodes/BTNode_Sequence.h"
#include "Nodes/BTNode_PerformAction.h"
#include "Nodes/BTNode_Decorator.h"
#include "../Actions/Action_ChangeTarget.h"
#include "../Actions/Action_MoveToPlayer.h"
#include "../Actions/Action_Wait.h"
#include "../Actions/Action_StartMoving.h"
#include "Blackboard.h"

namespace BT_Action
{
	bool ReachTarget(const Context* ipContext)
	{
		auto owner = ipContext->GetOwner();
		PathFollow* steering = dynamic_cast<PathFollow*>(owner->mpDynamicSteering);

		if (owner->mpTarget == nullptr || steering == nullptr)
			return false;
		auto corners = steering->GetCorners();
		if (
			glm::distance(owner->GetKinematic()->position, corners[corners.size() - 1].position) <= 10.0f)
			return true;
		return false;
	}

	bool IsPlayerNear(const Context* ipContext)
	{
		auto owner = ipContext->GetOwner();
		auto player = owner->mpPlayer;

		if (glm::distance(owner->GetKinematic()->position, player->GetKinematic()->position) <= 200.0f)
			return true;
		return false;
	}

}


class BT_Wander : public BehaviorTree
{
public:
	BT_Wander() = default;
	virtual ~BT_Wander() override = default;

	virtual void Init() override
	{
		auto selector = new BTNode_Selector();
		auto isPlayerNear = new BTNode_Decorator();
		isPlayerNear->SetFunction(BT_Action::IsPlayerNear);
		auto isReachTarget = new BTNode_Decorator();
		isReachTarget->SetFunction(BT_Action::ReachTarget);
		auto sequence = new BTNode_Sequence();
		auto changeTarget = new BTNode_PerformAction();
		changeTarget->SetAction(std::shared_ptr<Action>((new Action_ChangeTarget(100, 0))));
		auto startMoving = new BTNode_PerformAction();
		startMoving->SetAction(std::shared_ptr<Action>(new Action_StartMoving(100, 0)));
		auto moveToPlayer = new BTNode_PerformAction();
		moveToPlayer->SetAction(std::shared_ptr<Action>(new Action_MoveToPlayer(100, 0)));
		//auto wait = new BTNode_PerformAction();
		//wait->SetAction(std::make_shared<Action>(new Action_Wait(100, 3)));

		mNodes.push_back(selector);
		mNodes.push_back(isPlayerNear);
		mNodes.push_back(isReachTarget);
		mNodes.push_back(sequence);
		mNodes.push_back(changeTarget);
		mNodes.push_back(startMoving);
		mNodes.push_back(moveToPlayer);
		//mNodes.push_back(wait);

		mpRoot = selector;

		for (int i = 0; i < mNodes.size(); i++)
			mNodes[i]->SetID(i);

		selector->SetChildren({ isPlayerNear, isReachTarget, startMoving });
		isPlayerNear->SetChild(sequence);
		isReachTarget->SetChild(changeTarget);
		//sequence->SetChildren({ moveToPlayer, wait });
		sequence->SetChildren({ moveToPlayer });

		Blackboard* BB = new Blackboard();
		BB->Init(
			{
				{"Action", sizeof(std::shared_ptr<Action>)}
			},
			{
				{"isOpen", 0, sizeof(bool)},
				{"isOpen", 1, sizeof(bool)},
				{"isOpen", 2, sizeof(bool)},
				{"isOpen", 3, sizeof(bool)},
				{"isOpen", 4, sizeof(bool)},
				{"isOpen", 5, sizeof(bool)},
				{"isOpen", 6, sizeof(bool)},
				{"runningChild", 0, sizeof(uint8_t)},
				{"runningChild", 3, sizeof(uint8_t)},
			});

		mpBlackboard = BB;
	}
};