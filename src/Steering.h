#pragma once

class Kinematic;
class SteeringOutput;

class Steering
{
public:
	// Constructor
	Steering(Kinematic* ipKinematic, Kinematic* ipTarget, float inMaxSpeed, float inMaxRotation, float inMaxAcceleration);

	// Get Steering Output
	virtual SteeringOutput* GetSteeringOutput() const = 0;

private:
	Kinematic* mpKinematic;
	Kinematic* mpTarget;
	float mMaxSpeed;
	float mMaxRotation;
	float mMaxAcceleration;
};