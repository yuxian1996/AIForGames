#pragma once

#include "Steering.h"

class KinematicSteeringOutput;

class BasicKinematicSteering : public KinematicSteering
{
public:
	BasicKinematicSteering(Kinematic* ipKinematic, Kinematic* ipTarget, const float inMaxSpeed, const float inMaxRotation, const float inMaxAcceleration,
		const float inRadius)
		: KinematicSteering(ipKinematic, ipTarget, inMaxSpeed, inMaxRotation, inMaxAcceleration, inRadius)
	{ mpOutput = new KinematicSteeringOutput; }
	virtual ~BasicKinematicSteering() override {}

	virtual KinematicSteeringOutput* GetSteeringOutput() const override;

private:
	KinematicSteeringOutput* mpOutput;
};