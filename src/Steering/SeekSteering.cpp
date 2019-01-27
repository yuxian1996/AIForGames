#include "SeekSteering.h"

#include "../Kinematic.h"
#include "glm/glm.hpp"


KinematicSteeringOutput * KinematicSeekSteering::GetSteeringOutput() const
{
	KinematicSteeringOutput* output = new KinematicSteeringOutput;
	
	// Arrive
	if (glm::length(mpTarget->position - mpKinematic->position) <= 5)
	{
		output->mVelocity = glm::vec2(0,0);
		output->mRotation = 0;
		return output;
	}

	// compute velocity
	glm::vec2 direction = glm::normalize(mpTarget->position - mpKinematic->position);
	output->mVelocity = direction * mMaxSpeed;

	// compute orientation
	mpKinematic->orientation = Kinematic::ComputeOrientation(direction);
	output->mRotation = 0;

	return output;
}

DynamicSteeringOutput * DynamicSeekSteering::GetSteeringOutput() const
{
	DynamicSteeringOutput* output = new DynamicSteeringOutput;
	output->mLinear = glm::vec2(0, 0);
	output->mAngular = 0;

	//Arrival
	float distance = glm::length(mpTarget->position - mpKinematic->position);
	if (distance < mTargetRadius)
		return output;

	// Max Speed
	if (distance > mSlowRadius)
	{
		glm::vec2 acceleration = glm::normalize(mpTarget->position - mpKinematic->position) * mMaxAcceleration;
		output->mLinear = acceleration;
		return output;
	}

	// Slow down
	float targetSpeed = mMaxSpeed * distance / mSlowRadius;
	glm::vec2 targetAcc = (glm::normalize(mpTarget->position - mpKinematic->position) * targetSpeed - mpKinematic->velocity) / mTimeToTarget;
	float accLength = glm::length(targetAcc);
	if (accLength > mMaxAcceleration)
		targetAcc = glm::normalize(targetAcc) * mMaxAcceleration;
	output->mLinear = targetAcc;

	return output;
}
