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
	return mpOutput;
}
