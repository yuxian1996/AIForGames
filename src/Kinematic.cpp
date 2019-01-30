#include "Kinematic.h"

#include "SteeringOutput.h"
#include "glm/glm.hpp"

void Kinematic::UpdateVelocityRotation(const DynamicSteeringOutput & inSteering, const float inDeltaTime, float inMaxSpeed, float inMaxRotation)
{
	velocity += inSteering.mLinear * inDeltaTime;
	if (glm::length(velocity) >= inMaxSpeed)
		velocity = glm::normalize(velocity) * inMaxSpeed;

	rotation += inSteering.mAngular * inDeltaTime;
	if (abs(rotation) > inMaxRotation)
		rotation = rotation / abs(rotation) * inMaxRotation;

	//orientation = ComputeOrientation(position);
	//rotation = 0;
}

void Kinematic::UpdateVelocityRotation(const KinematicSteeringOutput& inSteering, const float inDeltaTime)
{
	velocity = inSteering.mVelocity;
	rotation = inSteering.mRotation;
}

void Kinematic::Update(const float inDeltaTime)
{
	position += velocity * inDeltaTime;
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

float Kinematic::GetMappedOrientation(const float inOrientation)
{
	if (inOrientation == 0)
		return 0;

	float absOrientation = abs(inOrientation);
	float direction = inOrientation / absOrientation;

	return direction * (absOrientation - floor(absOrientation / PI) * PI);
}
