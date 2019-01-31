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

	void SetTargetOrientation(float inOrientation) const { mTargetOrientation = inOrientation; }

private:
	mutable float mTargetOrientation;
};

class FaceToWhereYouGo : public DynamicSteering
{
public:
	FaceToWhereYouGo(Boid* ipBoid) : DynamicSteering(ipBoid), mAlign(ipBoid) {}
	virtual ~FaceToWhereYouGo() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;

private:
	DynamicAlignSteering mAlign;

};

class FaceTarget : public DynamicSteering
{
public:
	FaceTarget(Boid* ipBoid) : DynamicSteering(ipBoid), mAlign(ipBoid) {}
	virtual ~FaceTarget() override {}

	virtual DynamicSteeringOutput* GetSteeringOutput() const override;

private:
	DynamicAlignSteering mAlign;

};