#include "Kinematic.h"

#include "SteeringOutput.h"
#include "glm/glm.hpp"

void Kinematic::Update(const DynamicSteeringOutput& inSteering, const float inDeltaTimeg)
{
	velocity += inSteering.mLinear * inDeltaTimeg;
	position += velocity * inDeltaTimeg;
	orientation = ComputeOrientation(position);
	rotation = 0;
}

void Kinematic::Update(const KinematicSteeringOutput& inSteering, const float inDeltaTime)
{
	velocity = inSteering.mVelocity;
	position += velocity * inDeltaTime;
	rotation = inSteering.mRotation;
	orientation += rotation * inDeltaTime;
}

float Kinematic::ComputeOrientation(const glm::vec2 & inPosition) 
{
	float length = inPosition.length();
	assert(length != 0);
	float orientation = acos(glm::normalize(inPosition).x);
	if (inPosition.y < 0)
		orientation = -orientation;

	return orientation;
}
