#pragma once

#include "../Steering.h"

class PathFollow : public DynamicSteering
{
public:
	PathFollow(Boid* ipBoid, std::vector<int> inPath) : DynamicSteering(ipBoid)
	{

	}
	virtual ~PathFollow() = default;

	virtual DynamicSteeringOutput* GetSteeringOutput() const override
	{

	}

private:

};