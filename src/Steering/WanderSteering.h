#pragma once

#include "Steering.h"
#include "SeekSteering.h"
#include "../Kinematic.h"

class KinematicWanderSteering : public KinematicSteering
{
public:
	KinematicWanderSteering(Boid* ipBoid) : KinematicSteering(ipBoid) {}
	virtual ~KinematicWanderSteering() override {}

	virtual KinematicSteeringOutput* GetSteeringOutput() const override;
};

class DynamicWanderSteering : public DynamicSteering
{
public:
	DynamicWanderSteering(Boid* ipBoid) : DynamicSteering(ipBoid), mDelegateSeekSteering(ipBoid){}
	virtual ~DynamicWanderSteering() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;

	void SetWanderTarget(const Kinematic& inWanderTarget) { mWanderTarget = inWanderTarget; }

private:
	mutable Kinematic mWanderTarget;
	DynamicSeekSteering mDelegateSeekSteering;
};