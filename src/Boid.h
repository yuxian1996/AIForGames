#pragma once

#include "Kinematic.h"
#include "Notation/Notation.h"

class KinematicSteering;
class DynamicSteering;

class Boid
{
public:
	// Constructor / Desctructor
	Boid() {}
	Boid(const Kinematic& inKinematic) : mKinematic(inKinematic) {};
	~Boid();

	// Getter & Setter
	Kinematic* GetKinematic() { return &mKinematic; }
	void SetKinematic(const Kinematic& inKinematic) { mKinematic = inKinematic; }

	// Add Steering
	void AddSteering(KinematicSteering* ipSteering) { mpKinematicSteering.push_back(ipSteering); }
	void AddSteering(DynamicSteering* ipSteering) { mpDynamicSteering.push_back(ipSteering); }

	// Draw
	void Draw() const;

	// Update Boid
	void Update(float inDeltaTime);

private:
	Kinematic mKinematic;
	float mRadius = 10.0f;
	std::vector<KinematicSteering*> mpKinematicSteering;
	std::vector<DynamicSteering*> mpDynamicSteering;
	Notation mFootprint;
	const float mFoorPrinttInterval = 0.2f;
	float mTime = mFoorPrinttInterval;
};