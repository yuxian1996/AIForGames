#pragma once

#include "../Action.h"

class Action_Wait : public Action
{
public:
	Action_Wait(const float inExpireTime, const float inExecuteTime, const uint8_t inPriority = 0)
		: Action(inExpireTime, inExecuteTime, inPriority) {}
	virtual ~Action_Wait() override = default;

	virtual void OnActionExecute(Context* ipContext)
	{
		//do nothing
		Boid* boid = ipContext->GetOwner();
		if (boid->mpDynamicSteering)
		{
			delete boid->mpDynamicOrientationSteering;
			boid->mpDynamicSteering = nullptr;
		}
	}

};