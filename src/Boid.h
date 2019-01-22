#pragma once

#include "Kinematic.h"

class Steering;

class Boid
{
public:
	// Constructor
	Boid() {}
	Boid(const Kinematic& inKinematic) : mKinematic(inKinematic) {};

	// Getter & Setter
	Kinematic GetKinematic() const { return mKinematic; }
	void SetKinematic(const Kinematic& inKinematic) { mKinematic = inKinematic; }

	// Draw
	void Draw() const;

	// Update Boid
	void Update(float inDeltaTime);

private:
	//ofCairoRenderer* mRenderer;
	Kinematic mKinematic;
	float mRadius = 5.0f;
	std::vector<Steering*> mpSteerings;
};