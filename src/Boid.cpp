#include "Boid.h"

#include "Steering/Steering.h"
#include "SteeringOutput.h"

#include <ofGraphics.h>

Boid::~Boid()
{
	// delete every steering behavior
	for (auto steering : mpKinematicSteering)
	{
		delete steering;
	}
	for (auto steering : mpDynamicSteering)
	{
		delete steering;
	}

	mpKinematicSteering.clear();
	mpDynamicSteering.clear();
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
	const auto& oldOrientation = mKinematic.orientation;
	
	// update dynamic steering only if it has dynamic steering
	if (mpDynamicSteering.size() != 0)
	{
		DynamicSteeringOutput* dynamicOutput = mpDynamicSteering[0]->GetSteeringOutput();
		mKinematic.Update(*dynamicOutput, inDeltaTime);
		delete dynamicOutput;

		// orientation match steering
		mKinematic.orientation = acos(mKinematic.position.x / mKinematic.position.length());
		if (mKinematic.position.y < 0)
			mKinematic.orientation = -mKinematic.orientation;

	}
	else if (mpKinematicSteering.size() != 0)
	{
		KinematicSteeringOutput* kinematicOutput = mpKinematicSteering[0]->GetSteeringOutput();
		mKinematic.Update(*kinematicOutput, inDeltaTime);
		delete kinematicOutput;
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
