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
	float targetRadius = mpBoid->mTargetRadius;
	float slowRadius = mpBoid->mSlowRadius;
	float maxSpeed = mpBoid->mMaxSpeed;
	float maxAcceleration = mpBoid->mMaxAcceleration;
	float timeToTarget = mpBoid->mTimeToTarget;

	mpOutput->mLinear = glm::vec2(0, 0);
	mpOutput->mAngular = 0;

	//Arrival
	float distance = glm::length(pTarget->position - pKinematic->position);
	if (distance < targetRadius)
	{
		pKinematic->velocity = glm::vec2(0, 0);
		return mpOutput;
	}

	// Max Speed
	if (distance > slowRadius)
	{
		glm::vec2 acceleration = glm::normalize(pTarget->position - pKinematic->position) * maxAcceleration;
		mpOutput->mLinear = acceleration;
		return mpOutput;
	}

	// Slow down
	float targetSpeed = maxSpeed * distance / slowRadius;
	glm::vec2 targetAcc = (glm::normalize(pTarget->position - pKinematic->position) * targetSpeed - pKinematic->velocity) / timeToTarget;
	float accLength = glm::length(targetAcc);
	if (accLength > maxAcceleration)
		targetAcc = glm::normalize(targetAcc) * maxAcceleration;
	mpOutput->mLinear = targetAcc;

	return mpOutput;
}
