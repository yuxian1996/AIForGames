#pragma once

#include "Kinematic.h"
#include "Notation/Notation.h"

class KinematicSteering;
class DynamicSteering;
class Group;

class Boid
{
public:
	// Constructor 
	Boid() {}
	Boid(const Kinematic& inKinematic, Kinematic* ipTarget, float inMaxSpeed, float inMaxRotation, float inMaxAcceleration, float inMaxAngular,
		float inTargetRadius = 0, float inSlowRadius = 0, float inTimeToTarget = 0, float inWanderDistance = 0, float inWanderRadius = 0,
		float inSlowAngleThreshold = 0, float inTargetAngleThreshold = 0, float inTimeToAngleTarget = 0, float k = 15000) : mKinematic(inKinematic), mpTarget(ipTarget),
		mMaxSpeed(inMaxSpeed), mMaxRotation(inMaxRotation), mMaxAcceleration(inMaxAcceleration), mMaxAngularAcc(inMaxAngular), mTargetRadius(inTargetRadius), 
		mSlowRadius(inSlowRadius), mTimeToTarget(inTimeToTarget), mWanderDistance(inWanderDistance), mWanderRadius(inWanderRadius),
		mSlowAngleThreshold(inSlowAngleThreshold), mTargetAngleThreshold(inTargetAngleThreshold), mTimeToAngleTarget(inTimeToAngleTarget), K(k),
		mColor(0, 200, 200, 255){};
	~Boid();

	// Getter & Setter
	Kinematic* GetKinematic() { return &mKinematic; }
	void SetKinematic(const Kinematic& inKinematic) { mKinematic = inKinematic; }

	// Draw
	void Draw() const;

	// Update Boid
	void Update(float inDeltaTime);

	void SetGroup(const Group* inGroup) { mpGroup = inGroup; }
	void SetLeader(const Boid* ipLeader) { mpLeader = ipLeader; }

	void SetColor(ofColor inColor) { mColor = inColor; }

public:
	Kinematic mKinematic;
	const Kinematic* mpTarget;

	const Group* mpGroup;
	const Boid* mpLeader;
	float mMaxSpeed;
	float mMaxRotation;
	float mMaxAcceleration;
	float mMaxAngularAcc;
	float mTargetRadius;
	float mSlowRadius;
	float mTimeToTarget;
	float mWanderDistance;
	float mWanderRadius;
	float mSlowAngleThreshold;
	float mTargetAngleThreshold;
	float mTimeToAngleTarget;
	float K;
	float mRadius = 10.0f;

	KinematicSteering* mpKinematicSteering = nullptr;
	DynamicSteering* mpDynamicSteering = nullptr;

	KinematicSteering* mpKinematicOrientationSteering = nullptr;
	DynamicSteering* mpDynamicOrientationSteering = nullptr;

private:
	Notation mFootprint;
	const float mFoorPrinttInterval = 0.2f;
	float mTime = mFoorPrinttInterval;
	ofColor mColor;
};