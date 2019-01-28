#include "SeperationSteering.h"

#include "../Boid.h"
#include <glm/glm.hpp>
#include <algorithm>
#include "../Group.h"

DynamicSteeringOutput * DynamicSeperationSteering::GetSteeringOutput() const
{
	float k = mpBoid->K;
	float maxAcc = mpBoid->mMaxAcceleration;
	Kinematic* pKinematic = mpBoid->GetKinematic();
	
	mpOutput->mAngular = 0;
	mpOutput->mLinear = glm::vec2(0, 0);
	for (auto pBoid : mpBoid->mpGroup->mpBoids)
	{
		if(pBoid->mKinematic.position == pKinematic->position)
			continue;

		glm::vec2 vector = pKinematic->position - pBoid->mKinematic.position;
		float distance = glm::length(vector);
		float strength = std::min(k / (distance * distance), maxAcc);

		mpOutput->mLinear += strength * glm::normalize(vector);
	}

	if (glm::length(mpOutput->mLinear) > maxAcc)
	{
		mpOutput->mLinear = glm::normalize(mpOutput->mLinear) * maxAcc;
	}

	return mpOutput;

}
