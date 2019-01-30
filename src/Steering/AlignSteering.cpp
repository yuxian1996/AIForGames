#include "AlignSteering.h"
#include "../Boid.h"
#include <glm/glm.hpp>
#include "../Kinematic.h"
#include "ofAppRunner.h"

KinematicSteeringOutput * KinematicAlignSteering::GetSteeringOutput() const
{
	Kinematic* pKinematic = mpBoid->GetKinematic();
	float oldOrientation = pKinematic->orientation;

	// orientation match steering
	if (glm::length(pKinematic->velocity) >= 0.001f)
	{
		mpOutput->mRotation = (Kinematic::ComputeOrientation(pKinematic->velocity) - oldOrientation) / ofGetLastFrameTime();
	}
	mpOutput->mVelocity = pKinematic->velocity;

	return mpOutput;
}

DynamicSteeringOutput * DynamicAlignSteering::GetSteeringOutput() const
{

	auto pTarget = mpBoid->mpTarget;
	Kinematic* pKinematic = mpBoid->GetKinematic();
	float targetRadiance = mpBoid->mTargetAngleThreshold;
	float slowRadiance = mpBoid->mSlowAngleThreshold;
	float maxRotation = mpBoid->mMaxRotation;
	float maxAngularAcc = mpBoid->mMaxAngularAcc;
	float timeToTarget = mpBoid->mTimeToAngleTarget;

	float radiance = Kinematic::ComputeOrientation(pKinematic->velocity) - pKinematic->orientation;
	// map to [-PI, PI]
	radiance = Kinematic::GetMappedOrientation(radiance);
	float radianceSize = abs(radiance);

	// Arrive
	if (radianceSize < targetRadiance)
	{
		pKinematic->rotation = 0;
		mpOutput->mAngular = 0;
		mpOutput->mLinear = glm::vec2(0, 0);
		return mpOutput;
	}

	float direction = radiance / radianceSize;
	// Max Speed
	if (radianceSize > slowRadiance)
	{
		mpOutput->mAngular = direction * maxAngularAcc;
		mpOutput->mLinear = glm::vec2(0, 0);
		return mpOutput;
	}

	// Slow down
	float targetRotation = maxRotation * radianceSize / slowRadiance;
	float targetAcc = (direction * targetRotation - Kinematic::GetMappedOrientation(pKinematic->orientation)) / timeToTarget;
	if (abs(targetAcc) > maxAngularAcc)
		targetAcc = direction * maxAngularAcc;
	mpOutput->mAngular = targetAcc;
	mpOutput->mLinear = glm::vec2(0, 0);

	return mpOutput;
}
