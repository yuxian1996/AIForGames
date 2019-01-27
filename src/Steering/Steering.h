#pragma once

#include "../SteeringOutput.h"

class Kinematic;

class Steering
{
public:
	// Constructor
	Steering(Kinematic* ipKinematic, Kinematic* ipTarget, const float inMaxSpeed, const float inMaxRotation, const float inMaxAcceleration, 
		const float inRadius)
		: mpKinematic(ipKinematic), mpTarget(ipTarget), mMaxSpeed(inMaxSpeed), mMaxRotation(inMaxRotation), mMaxAcceleration(inMaxAcceleration),
		mRadius(inRadius)
	{}
	virtual ~Steering() {}

	// Get Steering Output
	virtual SteeringOutput* GetSteeringOutput() const = 0;

protected:
	Kinematic* mpKinematic;
	Kinematic* mpTarget;
	float mMaxSpeed;
	float mMaxRotation;
	float mMaxAcceleration;
	float mRadius;
};


class KinematicSteering : public Steering
{
public:
	KinematicSteering(Kinematic* ipKinematic, Kinematic* ipTarget, const float inMaxSpeed, const float inMaxRotation, const float inMaxAcceleration,
		const float inRadius)
	: Steering(ipKinematic, ipTarget, inMaxSpeed, inMaxRotation, inMaxAcceleration, inRadius) {}
	virtual ~KinematicSteering() override {}

	virtual KinematicSteeringOutput* GetSteeringOutput() const override = 0;
};

class DynamicSteering : public Steering
{
public:
	DynamicSteering(Kinematic* ipKinematic, Kinematic* ipTarget, const float inMaxSpeed, const float inMaxRotation, const float inMaxAcceleration,
		const float inRadius)
		: Steering(ipKinematic, ipTarget, inMaxSpeed, inMaxRotation, inMaxAcceleration, inRadius) {}
	virtual ~DynamicSteering() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override = 0;
};