#pragma once

#include "../Steering.h"
#include "../SeekSteering.h"
#include "../ArriveSteering.h"

class SeekKinematicArrive : public DynamicSteering
{
public:
	SeekKinematicArrive(Boid* ipBoid) : DynamicSteering(ipBoid), mSeek(ipBoid), mArrive(ipBoid) {}
	virtual ~SeekKinematicArrive() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;

private:
	DynamicSeekSteering mSeek;
	KinematicArriveSteering mArrive;
};

class SeekDynamicArrive : public DynamicSteering
{
public:
	SeekDynamicArrive(Boid* ipBoid) : DynamicSteering(ipBoid), mSeek(ipBoid), mArrive(ipBoid) {}
	virtual ~SeekDynamicArrive() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;

private:
	DynamicSeekSteering mSeek;
	DynamicArriveSteering mArrive;
};