#pragma once

#include "DecisionTree.h"
#include "DTDecisionNode_Bool.h"
#include "DTActionNode.h"
#include "../Actions/Action_OutputMessage.h"
#include "../Actions/Action_ChangeTarget.h"
#include "../Actions/Action_MoveToTarget.h"
#include "../Actions/Action_MoveToPlayer.h"
#include "../Actions/Action_Wait.h"
#include "../Context.h"
#include "../../Boid.h"

bool TestFunc(const Context* ipContext)
{
	auto owner = ipContext->GetOwner();
	return owner->GetKinematic()->velocity.x >= 0;
}

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

	if (glm::distance(owner->GetKinematic()->position, player->GetKinematic()->position) <= 100.0f)
		return true;
	return false;
}


class DT_Wanderer : public DecisionTree
{
public:
	DT_Wanderer() = default;
	virtual ~DT_Wanderer() override = default;

	virtual void Init() override
	{
		//mpRoot = new DTDecisionNode_Bool()
		std::shared_ptr<Action> changeTargetAction(new Action_ChangeTarget(100.0f, 0));
		std::shared_ptr<Action> moveToTargetAction(new Action_MoveToTarget(100.0f, 0));
		std::shared_ptr<Action> moveToPlayerAction(new Action_MoveToPlayer(100.0f, 0));

		auto changeTargetNode = new DTActionNode(changeTargetAction);
		auto moveToTargetNode = new DTActionNode(moveToTargetAction);
		auto moveToPlayerNode = new DTActionNode(moveToPlayerAction);

		//std::function<bool(const Context*)> func = ;
		auto bottomNode = new DTDecisionNode_Bool(moveToTargetNode, changeTargetNode, ReachTarget);
		mpRoot = new DTDecisionNode_Bool(bottomNode, moveToPlayerNode, IsPlayerNear);
	}


};