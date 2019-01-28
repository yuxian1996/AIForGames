#include "ArriveSteering.h"

#include "../Boid.h"
#include <glm/glm.hpp>

KinematicSteeringOutput * KinematicArriveSteering::GetSteeringOutput() const
{
	auto pTarget = mpBoid->mpTarget;
	Kinematic* pKinematic = mpBoid->GetKinematic();
	float targetRadius = mpBoid->mTargetRadius;

	mpOutput->mRotation = 0;
	float distance = glm::length(pTarget->position - pKinematic->position);
	if (distance <= targetRadius)
	{
		mpOutput->mVelocity = glm::vec2(0, 0);
		return mpOutput;
	}
	else
	{
		return nullptr;
	}

}

DynamicSteeringOutput * DynamicArriveSteering::GetSteeringOutput() const
{
	auto pTarget = mpBoid->mpTarget;
	Kinematic* pKinematic = mpBoid->GetKinematic();
	float targetRadius = mpBoid->mTargetRadius;
	float slowRadius = mpBoid->mSlowRadius;
	float maxSpeed = mpBoid->mMaxSpeed;
	float maxAcceleration = mpBoid->mMaxAcceleration;
	float timeToTarget = mpBoid->mTimeToTarget;

	//Arrive
	float distance = glm::length(pTarget->position - pKinematic->position);
	if (distance < targetRadius)
	{
		pKinematic->velocity = glm::vec2(0, 0);
		mpOutput->mAngular = 0;
		mpOutput->mLinear = glm::vec2(0, 0);
		return mpOutput;
	}

	// Max Speed
	if (distance > slowRadius)
	{
		glm::vec2 acceleration = glm::normalize(pTarget->position - pKinematic->position) * maxAcceleration;
		mpOutput->mLinear = glm::vec2(0, 0);
		return nullptr;
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
