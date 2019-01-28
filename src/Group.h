#pragma once

#include "Boid.h"

#include <vector>

class Group
{
public:
	std::vector<Boid*> mpBoids;
	Kinematic mKinematic;

	void Update()
	{
		glm::vec2 velocity;
		glm::vec2 center;
		for (auto pBoid : mpBoids)
		{
			center += pBoid->mKinematic.position;
			velocity += pBoid->mKinematic.velocity;
		}

		center /= mpBoids.size();
		velocity /= mpBoids.size();
		mKinematic.position = center;
		mKinematic.velocity = velocity;
	}
};