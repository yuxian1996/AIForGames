#pragma once

#include "../Steering.h"
#include "../SeperationSteering.h"
#include "SeekArrive.h"

class FlockingSteering : public DynamicSteering
{
public:
	FlockingSteering(Boid* ipBoid, float inSeperationWeight, float inSeekLeaderWeight, float inSeekCenterWeight) : DynamicSteering(ipBoid), 
		mSeperation(ipBoid), mSeekLeader(ipBoid), mSeekCenter(ipBoid), mSeperationWeight(inSeperationWeight), mSeekLeaderWeight(inSeekLeaderWeight),
	mSeekCenterWeight(inSeekCenterWeight) {}
	virtual ~FlockingSteering() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;

private:
	DynamicSeperationSteering mSeperation;
	SeekDynamicArrive mSeekLeader;
	SeekDynamicArrive mSeekCenter;
	float mSeperationWeight;
	float mSeekLeaderWeight;
	float mSeekCenterWeight;
};