#pragma once

#include "Steering.h"

class KinematicSteeringOutput;

class BasicKinematicSteering : public KinematicSteering
{
public:
	BasicKinematicSteering(Boid* ipBoid) : KinematicSteering(ipBoid) {}
	virtual ~BasicKinematicSteering() override {}

	virtual KinematicSteeringOutput* GetSteeringOutput() const override;

};