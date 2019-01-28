#include "Kinematic.h"

#include "SteeringOutput.h"
#include "glm/glm.hpp"

void Kinematic::Update(const DynamicSteeringOutput & inSteering, const float inDeltaTime, float inMaxSpeed, float inMaxRotation)
{
	velocity += inSteering.mLinear * inDeltaTime;
	if (glm::length(velocity) >= inMaxSpeed)
		velocity = glm::normalize(velocity) * inMaxSpeed;
	position += velocity * inDeltaTime;
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

float Kinematic::ComputeOrientation(const glm::vec2 & inVector) 
{
	float length = inVector.length();
	assert(length != 0);
	float orientation = atan2(inVector.y, inVector.x);

	return orientation;
}

glm::vec2 Kinematic::ComputeDirection(const float inOrientation)
{
	return glm::vec2(cos(inOrientation), sin(inOrientation));
}
