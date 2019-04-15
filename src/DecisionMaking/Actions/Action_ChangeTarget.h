#pragma once

#include "../Action.h"
#include "../../ofApp.h"

class Action_ChangeTarget : public Action
{
public:
	Action_ChangeTarget(const float inExpireTime, const float inExecuteTime, const uint8_t inPriority = 0)
		: Action(inExpireTime, inExecuteTime, inPriority) {}

		virtual ~Action_ChangeTarget() override = default;

	virtual void OnActionExecute(Context* ipContext)
	{
		Boid* boid = ipContext->GetOwner();

		Kinematic* target = const_cast<Kinematic*>(boid->mpTarget);
		if (target)
		{

			float x = (float)rand() / RAND_MAX * 800;
			float y = (float)rand() / RAND_MAX * 800;
			target->position = glm::vec2(x, y);

			std::vector<Kinematic> path = ofApp::GetPath(boid->GetKinematic()->position, target->position);
			if (path.size() == 0)
			{
				path.push_back(*boid->GetKinematic());
			}

			PathFollow* steering = dynamic_cast<PathFollow*>(boid->mpDynamicSteering);
			if (steering)
			{
				steering->SetPath(path);
			}

		}
	}
};