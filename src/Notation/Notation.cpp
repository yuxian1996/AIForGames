#include "Notation.h"

void Notation::AddPoints(const glm::vec2 & inPoints)
{
	mPoints.push_back(inPoints);
	mTimes.push_back(mDelayTime);
}

void Notation::RemoveLastPoints()
{
	mPoints.pop_front();
	mTimes.pop_front();
}

void Notation::Draw() const
{
	switch (mType)
	{
	case NotationType::Dot:
		ofSetColor(mColor);
		for (const auto& point : mPoints)
		{
			ofDrawCircle(point, mWidth);
		}
		break;
	case NotationType::Line:
		ofSetLineWidth(mWidth);
		ofSetColor(mColor);
		if (mPoints.size() <= 1)
			return;
		for(int i = 0; i < mPoints.size() - 1; i++)
		{
			ofDrawLine(mPoints[i], mPoints[i + 1]);
		}
		break;
	default:
		break;
	}
}

void Notation::Update(const float inDeltaTime)
{
	for (int i = 0; i < mTimes.size(); i++)
	{
		mTimes[i] -= inDeltaTime;
	}

	if (mTimes.size() >= 1 && mTimes[0] <= 0)
	{
		RemoveLastPoints();
	}
}
