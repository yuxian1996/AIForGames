#include "SeekSteering.h"

#include "../Boid.h"
#include "../Kinematic.h"
#include "glm/glm.hpp"


KinematicSteeringOutput * KinematicSeekSteering::GetSteeringOutput() const
{
	auto pTarget = mpBoid->mpTarget;
	Kinematic* pKinematic = &(mpBoid->mKinematic);
	float maxSpeed = mpBoid->mMaxSpeed;

	// Arrive
	if (glm::length(pTarget->position - pKinematic->position) <= 5)
	{
		mpOutput->mVelocity = glm::vec2(0,0);
		mpOutput->mRotation = 0;
		return mpOutput;
	}

	// compute velocity
	glm::vec2 direction = glm::normalize(pTarget->position - pKinematic->position);
	mpOutput->mVelocity = direction * maxSpeed;

	// compute orientation
	pKinematic->orientation = Kinematic::ComputeOrientation(direction);
	mpOutput->mRotation = 0;

	return mpOutput;
}

DynamicSteeringOutput * DynamicSeekSteering::GetSteeringOutput() const
{
	auto pTarget = mpBoid->mpTarget;
	Kinematic* pKinematic = &(mpBoid->mKinematic);
	float maxAcceleration = mpBoid->mMaxAcceleration;

	glm::vec2 acceleration = glm::normalize(pTarget->position - pKinematic->position) * maxAcceleration;
	mpOutput->mLinear = acceleration;
	mpOutput->mAngular = 0;

	return mpOutput;
}
