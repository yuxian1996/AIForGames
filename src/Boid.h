#pragma once

#include "Kinematic.h"
#include "Notation/Notation.h"

class KinematicSteering;
class DynamicSteering;

class Boid
{
public:
	// Constructor 
	Boid() {}
	Boid(const Kinematic& inKinematic, Kinematic* ipTarget, float inMaxSpeed, float inMaxRotation, float inMaxAcceleration, float inMaxAngular, float inTargetRadius = 0,
		float inSlowRadius = 0, float inTimeToTarget = 0, float inWanderDistance = 0, float inWanderRadius = 0) : mKinematic(inKinematic), mpTarget(ipTarget), mMaxSpeed(inMaxSpeed),
		mMaxRotation(inMaxRotation), mMaxAcceleration(inMaxAcceleration), mMaxAngular(inMaxAngular), mTargetRadius(inTargetRadius), mSlowRadius(inSlowRadius), 
		mTimeToTarget(inTimeToTarget), mWanderDistance(inWanderDistance), mWanderRadius(inWanderRadius) {};
	~Boid();

	// Getter & Setter
	Kinematic* GetKinematic() { return &mKinematic; }
	void SetKinematic(const Kinematic& inKinematic) { mKinematic = inKinematic; }

	// Draw
	void Draw() const;

	// Update Boid
	void Update(float inDeltaTime);

public:
	Kinematic mKinematic;
	Kinematic* mpTarget;
	float mMaxSpeed;
	float mMaxRotation;
	float mMaxAcceleration;
	float mMaxAngular;
	float mTargetRadius;
	float mSlowRadius;
	float mTimeToTarget;
	float mWanderDistance;
	float mWanderRadius;
	float mRadius = 10.0f;

	KinematicSteering* mpKinematicSteering = nullptr;
	DynamicSteering* mpDynamicSteering = nullptr;

private:
	Notation mFootprint;
	const float mFoorPrinttInterval = 0.2f;
	float mTime = mFoorPrinttInterval;
};