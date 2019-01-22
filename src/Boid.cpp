#include "Boid.h"

#include "Steering.h"
#include "SteeringOutput.h"

#include <ofGraphics.h>

void Boid::Draw() const
{
	ofDrawCircle(mKinematic.position.x, mKinematic.position.y, 0, mRadius);

	glm::vec3 point1, point2, point3;
	point1 = glm::vec3(mKinematic.position.x + cos(mKinematic.orientation) * 2 * mRadius, mKinematic.position.y + sin(mKinematic.orientation) * 2 * mRadius, 0);
	point2 = glm::vec3(mKinematic.position.x + sin(mKinematic.orientation) * mRadius, mKinematic.position.y + cos(mKinematic.orientation) * mRadius, 0);
	point3 = glm::vec3(mKinematic.position.x + sin(mKinematic.orientation) * mRadius, mKinematic.position.y - cos(mKinematic.orientation) * mRadius, 0);
	ofDrawTriangle(point1, point2, point3);
}

void Boid::Update(float inDeltaTime)
{
	for (const auto& steering : mpSteerings)
	{
		auto steeringOutput = steering->GetSteeringOutput();
		if (DynamicSteeringOutput* dynamicOutput = dynamic_cast<DynamicSteeringOutput*>(steeringOutput))
		{
			mKinematic.Update(*dynamicOutput, inDeltaTime);
		}
		else if (KinematicSteeringOutput* kinematicOutput = dynamic_cast<KinematicSteeringOutput*>(steeringOutput))
		{
			mKinematic.Update(*kinematicOutput, inDeltaTime);
		}
	}
}
