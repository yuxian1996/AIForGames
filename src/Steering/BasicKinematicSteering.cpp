#include "BasicKinematicSteering.h"

#include "../Boid.h"
#include "../SteeringOutput.h"
#include "../Kinematic.h"

#include "ofAppRunner.h"

#define PI 3.1415927

KinematicSteeringOutput * BasicKinematicSteering::GetSteeringOutput() const
{
	auto pTarget = mpBoid->mpTarget;
	Kinematic* pKinematic = &(mpBoid->mKinematic);
	float maxSpeed = mpBoid->mMaxSpeed;
	float radius = mpBoid->mRadius;

	float height = ofGetWindowHeight() - radius;
	float width = ofGetWindowWidth() - radius;

	mpOutput->mVelocity = pKinematic->velocity;
	mpOutput->mRotation = 0;

	glm::vec2 nextPosition = pKinematic->position + (float)ofGetLastFrameTime() * pKinematic->velocity;

	if (nextPosition.x > width)
	{
		mpOutput->mVelocity = glm::vec2(0, -maxSpeed);
		pKinematic->orientation = -PI / 2;
	}
	if (nextPosition.x < radius)
	{
		mpOutput->mVelocity = glm::vec2(0, maxSpeed);
		pKinematic->orientation = PI / 2;
	}
	if (nextPosition.y > height)
	{
		mpOutput->mVelocity = glm::vec2(maxSpeed, 0);
		pKinematic->orientation = 0;
	}
	if (nextPosition.y < radius)
	{
		mpOutput->mVelocity = glm::vec2(-maxSpeed, 0);
		pKinematic->orientation = PI;
	}

	return mpOutput;
}
