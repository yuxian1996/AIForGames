#pragma once

#include "Steering.h"

class KinematicAlignSteering : public KinematicSteering
{
public:
	KinematicAlignSteering(Boid* ipBoid) : KinematicSteering(ipBoid) {}
	virtual ~KinematicAlignSteering() override {}

	virtual KinematicSteeringOutput* GetSteeringOutput() const override;
};

class DynamicAlignSteering : public DynamicSteering
{
public:
	DynamicAlignSteering(Boid* ipBoid) : DynamicSteering(ipBoid) {}
	virtual ~DynamicAlignSteering() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;
};