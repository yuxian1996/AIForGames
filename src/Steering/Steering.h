#pragma once

#include "../SteeringOutput.h"

class Kinematic;
class Boid;
class KinematicSteeringOutput;
class DynamicSteeringOutput;

class Steering
{
public:
	// Constructor
	Steering(Boid* ipBoid) :mpBoid(ipBoid) {}
	virtual ~Steering() {}

	// Get Steering Output
	virtual SteeringOutput* GetSteeringOutput() const = 0;

protected:
	Boid* mpBoid;
};


class KinematicSteering : public Steering
{
public:
	KinematicSteering(Boid* ipBoid) : Steering(ipBoid) { mpOutput = new KinematicSteeringOutput; }
	virtual ~KinematicSteering() override { if (mpOutput != nullptr) delete mpOutput; mpOutput = nullptr; }

	virtual KinematicSteeringOutput* GetSteeringOutput() const override = 0;
	
protected:
	KinematicSteeringOutput* mpOutput = nullptr;
};

class DynamicSteering : public Steering
{
public:
	DynamicSteering(Boid* ipBoid) : Steering(ipBoid) { mpOutput = new DynamicSteeringOutput; }
	virtual ~DynamicSteering() override { if (mpOutput != nullptr) delete mpOutput; mpOutput = nullptr; }

	virtual DynamicSteeringOutput* GetSteeringOutput() const override = 0;

protected:
	DynamicSteeringOutput* mpOutput = nullptr;

};