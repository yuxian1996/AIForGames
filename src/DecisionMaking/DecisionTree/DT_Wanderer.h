#pragma once

#include "DecisionTree.h"
#include "DTDecisionNode_Bool.h"
#include "DTActionNode.h"
#include "../Actions/Action_OutputMessage.h"
#include "../Context.h"
#include "../../Boid.h"

bool TestFunc(const Context* ipContext)
{
	auto owner = ipContext->GetOwner();
	return owner->GetKinematic()->velocity.x >= 0;
}


class DT_Wanderer : public DecisionTree
{
public:
	DT_Wanderer() = default;
	virtual ~DT_Wanderer() override = default;

	virtual void Init() override
	{
		//mpRoot = new DTDecisionNode_Bool()
		std::shared_ptr<Action> falseAction(new Action_OutputMessage("False"));
		std::shared_ptr<Action> trueAction(new Action_OutputMessage("True"));

		auto falseNode = new DTActionNode(falseAction);
		auto trueNode = new DTActionNode(falseAction);

		//std::function<bool(const Context*)> func = ;
		mpRoot = new DTDecisionNode_Bool(falseNode, trueNode, TestFunc);
	}


};