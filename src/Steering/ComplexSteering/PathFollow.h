#pragma once

#include "../Steering.h"
#include "SeekArrive.h"
#include "../../Boid.h"
#include "glm/glm.hpp"

#include <vector>

class PathFollow : public DynamicSteering
{
public:
	PathFollow(Boid* ipBoid, const std::vector<Kinematic>& inPath) : DynamicSteering(ipBoid), mSeekArrive(ipBoid), mSeek(ipBoid), mCorners(inPath)
	{
		mpBoid->mpTarget = GetNearestCorner();
	}
	virtual ~PathFollow() = default;

	virtual DynamicSteeringOutput* GetSteeringOutput() const override
	{
		if (mpBoid->mpTarget != nullptr)
		{
			// turn to next corner
			if (glm::length(mpBoid->GetKinematic()->position - mpBoid->mpTarget->position) < mpBoid->mTargetRadius && 
				mCurrentIndex < mCorners.size() - 1)
			{
				mpBoid->mpTarget = &mCorners[++mCurrentIndex];
			}
			if (mCurrentIndex == mCorners.size() - 1)
				return mSeekArrive.GetSteeringOutput();

			return mSeek.GetSteeringOutput();
		}
		mpBoid->mKinematic.velocity = glm::vec2(0, 0);
		mpBoid->mKinematic.rotation = 0;
		return mpOutput;
	}

	void SetPath(const std::vector<Kinematic>& inPath)
	{
		mCorners = inPath;
		mpBoid->mpTarget = GetNearestCorner();
	}

private:
	SeekDynamicArrive mSeekArrive;
	DynamicSeekSteering mSeek;
	std::vector<Kinematic> mCorners;
	mutable int mCurrentIndex = 0;

	Kinematic* GetNearestCorner()
	{
		if (mCorners.size() > 0)
		{
			mCurrentIndex = 0;
			return &mCorners[0];
		}
		else return nullptr;
	}

};