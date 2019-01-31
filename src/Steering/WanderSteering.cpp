#include "WanderSteering.h"

#include "../Boid.h"
#include "../Kinematic.h"

#include "ofAppRunner.h"

KinematicSteeringOutput * KinematicWanderSteering::GetSteeringOutput() const
{
	Kinematic kinematic = mpBoid->mKinematic;
	float maxSpeed = mpBoid->mMaxSpeed;
	float maxRotation = mpBoid->mMaxRotation;

	float deltaTime = ofGetLastFrameTime();
	float width = ofGetWidth();
	float height = ofGetHeight();
	float radius = mpBoid->mRadius;

	mpOutput->mVelocity = Kinematic::ComputeDirection(kinematic.orientation) *maxSpeed;

	// boundary test
	glm::vec2 nextPosition = mpOutput->mVelocity * deltaTime + kinematic.position;
	if (nextPosition.x <= radius || nextPosition.x >= width - radius)
	{
		mpOutput->mVelocity.x = -mpOutput->mVelocity.x;
		mpBoid->mKinematic.orientation += PI;
	}
	if (nextPosition.y <= radius || nextPosition.y >= height - radius)
	{
		mpOutput->mVelocity.y = -mpOutput->mVelocity.y;
		mpBoid->mKinematic.orientation += PI;
	}

	float randomBinomial = static_cast<float>(rand()) / RAND_MAX - static_cast<float>(rand()) / RAND_MAX;
	mpOutput->mRotation = maxRotation * randomBinomial;

	return mpOutput;
}

DynamicSteeringOutput * DynamicWanderSteering::GetSteeringOutput() const
{
	mpBoid->mpTarget = &mWanderTarget;
	Kinematic* pKinematic = mpBoid->GetKinematic();
	float distance = mpBoid->mWanderDistance;
	float radius = mpBoid->mWanderRadius;

	// boundary detect
	float width = ofGetWidth();
	float height = ofGetHeight();

	glm::vec2 nextPosition = pKinematic->position + pKinematic->velocity * (float)ofGetLastFrameTime();
	float bias = 10;
	bool bIsOut = false;

	// boundary test
	if (pKinematic->position.x <= bias || pKinematic->position.x >= width - bias)
	{
		pKinematic->position.x = width - pKinematic->position.x;
	}
	if (pKinematic->position.y <= bias || pKinematic->position.y >= height - bias)
	{
		pKinematic->position.y = height - pKinematic->position.y;
	}

	glm::vec2 center = pKinematic->position + distance * pKinematic->ComputeDirection(pKinematic->orientation);

	float random = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * PI * 2;

	glm::vec2 direction = Kinematic::ComputeDirection(pKinematic->orientation + random);
	mWanderTarget.position = center + radius * direction;


	return mDelegateSeekSteering.GetSteeringOutput();
}
