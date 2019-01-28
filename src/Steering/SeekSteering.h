#pragma once

#include "Steering.h"

class KinematicSeekSteering : public KinematicSteering
{
public:
	KinematicSeekSteering(Boid* ipBoid) : KinematicSteering(ipBoid) {}
	virtual ~KinematicSeekSteering() override {}

	virtual KinematicSteeringOutput* GetSteeringOutput() const override;
};

class DynamicSeekSteering : public DynamicSteering
{
public:
	DynamicSeekSteering(Boid* ipBoid) : DynamicSteering(ipBoid) {}
	virtual ~DynamicSeekSteering() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;
};
