#pragma once

#include "Steering.h"

class KinematicSeekSteering : public KinematicSteering
{
public:
	KinematicSeekSteering(Kinematic* ipKinematic, Kinematic* ipTarget, const float inMaxSpeed, const float inMaxRotation, const float inMaxAcceleration,
		const float inRadius)
		: KinematicSteering(ipKinematic, ipTarget, inMaxSpeed, inMaxRotation, inMaxAcceleration, inRadius) {}
	virtual ~KinematicSeekSteering() override {}

	virtual KinematicSteeringOutput* GetSteeringOutput() const override;

};

class DynamicSeekSteering : public DynamicSteering
{
public:
	DynamicSeekSteering(Kinematic* ipKinematic, Kinematic* ipTarget, const float inMaxSpeed, const float inMaxRotation, const float inMaxAcceleration,
		const float inRadius, const float inTargetRadius, const float inSlowRadius, const float inTimeToTarget)
		: DynamicSteering(ipKinematic, ipTarget, inMaxSpeed, inMaxRotation, inMaxAcceleration, inRadius), mTargetRadius(inTargetRadius),
		mSlowRadius(inSlowRadius), mTimeToTarget(inTimeToTarget)
	{}
	virtual ~DynamicSeekSteering() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;

private:
	float mTargetRadius;
	float mSlowRadius;
	float mTimeToTarget;
};
