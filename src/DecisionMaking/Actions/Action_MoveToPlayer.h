#pragma once

#include "../Action.h"
#include "../../ofApp.h"
#include "../../Steering/ComplexSteering/PathFollow.h"

class Action_MoveToPlayer : public Action
{
public:
	Action_MoveToPlayer(const float inExpireTime, const float inExecuteTime, const uint8_t inPriority = 0)
		: Action(inExpireTime, inExecuteTime, inPriority) {}
	virtual ~Action_MoveToPlayer() override = default;

	virtual void OnActionExecute(Context* ipContext) override
	{
		auto owner = ipContext->GetOwner();

		std::vector<Kinematic> path = ofApp::GetPath(owner->GetKinematic()->position, owner->mpPlayer->GetKinematic()->position);
		PathFollow* steering = dynamic_cast<PathFollow*>(owner->mpDynamicSteering);
		if (steering)
		{
			steering->SetPath(path);
		}
	}
};