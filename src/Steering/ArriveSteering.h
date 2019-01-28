#pragma once

#include "Steering.h"

class KinematicArriveSteering : public KinematicSteering
{
public:
	KinematicArriveSteering(Boid* ipBoid) : KinematicSteering(ipBoid) {}
	virtual ~KinematicArriveSteering() override {}

	virtual KinematicSteeringOutput* GetSteeringOutput() const override;
};

class DynamicArriveSteering : public DynamicSteering
{
public:
	DynamicArriveSteering(Boid* ipBoid) : DynamicSteering(ipBoid) {}
	virtual ~DynamicArriveSteering() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;
};