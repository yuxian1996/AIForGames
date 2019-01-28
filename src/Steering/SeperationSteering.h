#pragma once

#include "Steering.h"

class DynamicSeperationSteering : public DynamicSteering
{
public:
	DynamicSeperationSteering(Boid* ipBoid) : DynamicSteering(ipBoid) {}
	virtual ~DynamicSeperationSteering() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;
};