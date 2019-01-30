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
	Kinematic target;
	Kinematic* pKinematic = mpBoid->GetKinematic();
	float distance = mpBoid->mWanderDistance;
	float radius = mpBoid->mWanderRadius;


	// boundary detect
	float width = ofGetWidth();
	float height = ofGetHeight();

	// boundary test
	if (pKinematic->position.x <= radius || pKinematic->position.x >= width - radius)
	{
		pKinematic->velocity.x = -pKinematic->velocity.x;
		pKinematic->orientation += PI;
		pKinematic->rotation = 0;
	}
	if (pKinematic->position.y <= radius || pKinematic->position.y >= height - radius)
	{
		pKinematic->velocity.y = -pKinematic->velocity.y;
		pKinematic->orientation += PI;
		pKinematic->rotation = 0;
	}

	glm::vec2 center = pKinematic->position + distance * pKinematic->ComputeDirection(pKinematic->orientation);

	float random = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * PI * 2;
	//float random = (static_cast<float>(rand()) / RAND_MAX - static_cast<float>(rand()) / RAND_MAX) * PI;

	glm::vec2 direction = Kinematic::ComputeDirection(pKinematic->orientation + random);
	target.position = center + radius * direction;

	mpBoid->mpTarget = &target;

	return mDelegateSeekSteering.GetSteeringOutput();
}
