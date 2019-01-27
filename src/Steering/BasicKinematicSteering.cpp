#include "BasicKinematicSteering.h"

#include "../SteeringOutput.h"
#include "../Kinematic.h"

#include "ofAppRunner.h"

#define PI 3.1415927

KinematicSteeringOutput * BasicKinematicSteering::GetSteeringOutput() const
{
	KinematicSteeringOutput* kinematicOutput = new KinematicSteeringOutput;
	float height = ofGetWindowHeight() - mRadius;
	float width = ofGetWindowWidth() - mRadius;

	kinematicOutput->mVelocity = mpKinematic->velocity;
	kinematicOutput->mRotation = 0;

	glm::vec2 nextPosition = mpKinematic->position + (float)ofGetLastFrameTime() * mpKinematic->velocity;

	if (nextPosition.x > width)
	{
		kinematicOutput->mVelocity = glm::vec2(0, -mMaxSpeed);
		mpKinematic->orientation = -PI / 2;
	}
	if (nextPosition.x < mRadius)
	{
		kinematicOutput->mVelocity = glm::vec2(0, mMaxSpeed);
		mpKinematic->orientation = PI / 2;
	}
	if (nextPosition.y > height)
	{
		kinematicOutput->mVelocity = glm::vec2(mMaxSpeed, 0);
		mpKinematic->orientation = 0;
	}
	if (nextPosition.y < mRadius)
	{
		kinematicOutput->mVelocity = glm::vec2(-mMaxSpeed, 0);
		mpKinematic->orientation = PI;
	}

	return kinematicOutput;
}
