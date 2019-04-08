#pragma once

#include "../Action.h"
#include "../../Steering/ComplexSteering/PathFollow.h"
#include "../../ofApp.h"

class Action_MoveToTarget : public Action
{
public:
	Action_MoveToTarget(const float inExpireTime, const float inExecuteTime, const uint8_t inPriority = 0) 
		: Action(inExpireTime, inExecuteTime, inPriority) {}
	virtual ~Action_MoveToTarget() override = default;

	virtual void OnActionExecute(Context* ipContext) override
	{
		Boid* owner = ipContext->GetOwner();
		PathFollow* steering = dynamic_cast<PathFollow*>(owner->mpDynamicSteering);
		if (steering == nullptr)
		{
			glm::vec2 target = owner->mpTarget->position;
			auto steering = new PathFollow(ipContext->GetOwner(), ofApp::GetPath(owner->GetKinematic()->position, target));
			owner->mpDynamicSteering = steering;

		}
	}
};