#include "Boid.h"

#include "Steering/Steering.h"
#include "SteeringOutput.h"

#include <glm/glm.hpp>
#include <ofGraphics.h>

Boid::~Boid()
{
	if (mpDynamicSteering != nullptr)
		delete mpDynamicSteering;
	if (mpKinematicSteering != nullptr)
		delete mpKinematicSteering;

	mpDynamicSteering = nullptr;
	mpKinematicSteering = nullptr;
}

void Boid::Draw() const
{
	// draw footprint
	mFootprint.Draw();

	// draw circle
	ofSetColor(255);
	ofDrawCircle(mKinematic.position, mRadius);

	// draw triangle
	glm::vec2 point1, point2, point3;
	point1 = glm::vec2(mKinematic.position.x + cos(mKinematic.orientation) * 2 * mRadius, mKinematic.position.y + sin(mKinematic.orientation) * 2 * mRadius);
	point2 = glm::vec2(mKinematic.position.x + sin(mKinematic.orientation) * mRadius, mKinematic.position.y - cos(mKinematic.orientation) * mRadius);
	point3 = glm::vec2(mKinematic.position.x - sin(mKinematic.orientation) * mRadius, mKinematic.position.y + cos(mKinematic.orientation) * mRadius);
	ofDrawTriangle(point1, point2, point3);

}

void Boid::Update(float inDeltaTime)
{	
	auto oldOri = mKinematic.orientation;
	// update dynamic steering only if it has dynamic steering
	if (mpDynamicSteering != nullptr)
	{
		DynamicSteeringOutput* dynamicOutput = mpDynamicSteering->GetSteeringOutput();
		mKinematic.Update(*dynamicOutput, inDeltaTime, mMaxSpeed, mMaxRotation);

		// orientation match steering
		if (glm::length(mKinematic.velocity) >= 0.001f)
		{
			mKinematic.orientation = Kinematic::ComputeOrientation(mKinematic.velocity);
		}
	}
	else if (mpKinematicSteering != nullptr)
	{
		KinematicSteeringOutput* kinematicOutput = mpKinematicSteering->GetSteeringOutput();
		mKinematic.Update(*kinematicOutput, inDeltaTime);
	}

	// update footprint
	mTime -= inDeltaTime;
	if (mTime <= 0)
	{
		mFootprint.AddPoints(mKinematic.position);
		mTime = mFoorPrinttInterval;
	}
	mFootprint.Update(inDeltaTime);

}
