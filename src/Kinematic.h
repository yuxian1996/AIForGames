#pragma once

#include "math/ofVec3f.h"

#include <limits>

class DynamicSteeringOutput;
class KinematicSteeringOutput;

struct Kinematic
{
	glm::vec2 position;
	float orientation;
	glm::vec2 velocity;
	float rotation;

	Kinematic() {}
	Kinematic(const glm::vec2& inPosition, const float inOrientation, const glm::vec2& inVelocity, const float inRotation)
		: position(inPosition), orientation(inOrientation), velocity(inVelocity), rotation(inRotation)
	{}

	void Update(const DynamicSteeringOutput& inSteering, const float inDeltaTime, float inMaxSpeed = std::numeric_limits<float>::max(), 
		float inMaxRotation = std::numeric_limits<float>::max());
	void Update(const KinematicSteeringOutput& inSteering, const float inDeltaTime);

	static float ComputeOrientation(const glm::vec2& inVector);
	static glm::vec2 ComputeDirection(const float inOrientation);
};

