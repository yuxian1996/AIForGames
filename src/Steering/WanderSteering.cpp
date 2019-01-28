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
		mpOutput->mVelocity.x = -mpOutput->mVelocity.x;
	if (nextPosition.y <= radius || nextPosition.y >= height - radius)
		mpOutput->mVelocity.y = -mpOutput->mVelocity.y;

	float randomBinomial = static_cast<float>(rand()) / RAND_MAX - static_cast<float>(rand()) / RAND_MAX;

	mpOutput->mRotation = maxRotation * randomBinomial;


	return mpOutput;
}

DynamicSteeringOutput * DynamicWanderSteering::GetSteeringOutput() const
{
	Kinematic target;
	Kinematic kinematic = mpBoid->mKinematic;
	float distance = mpBoid->mWanderDistance;
	float radius = mpBoid->mWanderRadius;

	glm::vec2 center = kinematic.position + distance * kinematic.ComputeDirection(kinematic.orientation);
	float random = static_cast<float>(rand()) / RAND_MAX * PI * 2;

	glm::vec2 direction = Kinematic::ComputeDirection(random);
	std::cout << direction.x << ", " << direction.y << std::endl;
	target.position = center + radius * direction;

	mpBoid->mpTarget = &target;
	
	return mDelegateSeekSteering.GetSteeringOutput();
}
