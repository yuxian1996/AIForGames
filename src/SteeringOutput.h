#pragma once

#include "math/ofVec3f.h"

class SteeringOutput
{
public:
	virtual ~SteeringOutput() {}
};


class KinematicSteeringOutput : public SteeringOutput
{
public: 
	virtual ~KinematicSteeringOutput() override {} 

	glm::vec2 mVelocity;
	float mRotation;
};

class DynamicSteeringOutput : public SteeringOutput
{
public:
	virtual ~DynamicSteeringOutput() override {}

	glm::vec2 mLinear;
	float mAngular;
};