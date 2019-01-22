#include "Steering.h"

Steering::Steering(Kinematic * ipKinematic, Kinematic * ipTarget, float inMaxSpeed, float inMaxRotation, float inMaxAcceleration)
	: mpKinematic(ipKinematic), mpTarget(ipTarget), mMaxSpeed(inMaxSpeed), mMaxRotation(inMaxRotation), mMaxAcceleration(inMaxAcceleration)
{
}
