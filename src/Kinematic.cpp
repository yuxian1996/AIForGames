#include "Kinematic.h"

#include "SteeringOutput.h"

void Kinematic::Update(const DynamicSteeringOutput& inSteering, const float inDeltaTimeg)
{
	velocity += inSteering.mLinear * inDeltaTimeg;
	position += velocity * inDeltaTimeg;
	orientation = atanf(position.y / position.x);
	if (position.y < 0)
		orientation = -orientation;
	rotation = 0;
}

void Kinematic::Update(const KinematicSteeringOutput& inSteering, const float inDeltaTime)
{
	velocity = inSteering.mVelocity;
	position += velocity * inDeltaTime;
	orientation = inSteering.mRotation;
	rotation = 0;
}
