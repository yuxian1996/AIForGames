#pragma once
#pragma once

#include "DecisionTree.h"
#include "DTDecisionNode_Bool.h"
#include "DTActionNode.h"
#include "../Actions/Action_OutputMessage.h"
#include "../Actions/Action_ChangeTarget.h"
#include "../Actions/Action_StartMoving.h"
#include "../Actions/Action_MoveToPlayer.h"
#include "../Actions/Action_Wait.h"
#include "../Context.h"
#include "../../Boid.h"
#include "DT_Wanderer.h"


class DT_Learning : public DecisionTree
{
public:
	DT_Learning() = default;
	virtual ~DT_Learning() override = default;

	virtual void Init() override
	{
		//mpRoot = new DTDecisionNode_Bool()
		std::shared_ptr<Action> changeTargetAction(new Action_ChangeTarget(100.0f, 0));
		std::shared_ptr<Action> moveToTargetAction(new Action_StartMoving(100.0f, 0));
		std::shared_ptr<Action> moveToPlayerAction(new Action_MoveToPlayer(100.0f, 0));

		auto changeTargetNode = new DTActionNode(changeTargetAction);
		auto moveToTargetNode = new DTActionNode(moveToTargetAction);
		auto moveToPlayerNode = new DTActionNode(moveToPlayerAction);

		//std::function<bool(const Context*)> func = ;
		auto bottomNode = new DTDecisionNode_Bool(moveToTargetNode, changeTargetNode, DT_Action::ReachTarget);
		mpRoot = new DTDecisionNode_Bool(bottomNode, moveToPlayerNode, DT_Action::IsPlayerNear);
	}

};