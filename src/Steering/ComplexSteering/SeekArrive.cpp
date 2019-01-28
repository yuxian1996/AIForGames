#include "SeekArrive.h"

#include "../../Boid.h"
#include <glm/glm.hpp>

DynamicSteeringOutput * SeekKinematicArrive::GetSteeringOutput() const
{
	Kinematic* pKinematic = mpBoid->GetKinematic();

	auto seekOutput = mSeek.GetSteeringOutput();
	auto arriveOutput = mArrive.GetSteeringOutput();

	if (arriveOutput == nullptr)
		return seekOutput;

	pKinematic->velocity = arriveOutput->mVelocity;
	pKinematic->rotation = arriveOutput->mRotation;

	seekOutput->mAngular = 0;
	seekOutput->mLinear = glm::vec2(0, 0);

	return seekOutput;
}

DynamicSteeringOutput * SeekDynamicArrive::GetSteeringOutput() const
{
	Kinematic* pKinematic = mpBoid->GetKinematic();

	auto seekOutput = mSeek.GetSteeringOutput();
	auto arriveOutput = mArrive.GetSteeringOutput();

	if (arriveOutput == nullptr)
		return seekOutput;

	return arriveOutput;
}
