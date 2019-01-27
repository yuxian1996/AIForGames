#pragma once

#include "graphics/ofGraphics.h"
#include <deque>

enum class NotationType
{
	Dot,
	Line,
};

class Notation
{
public:
	Notation() : mType(NotationType::Dot), mColor(100, 100, 100), mWidth(3.0f), mDelayTime(1.5f) {}
	Notation(NotationType inType, const ofColor& inColor, const float inWidth, const float inDelayTime)
		: mType(inType), mColor(inColor), mWidth(inWidth), mDelayTime(inDelayTime) {}

	// Points
	void SetPoints(std::deque<glm::vec2> inPoints) { mPoints = inPoints; }
	void AddPoints(const glm::vec2& inPoints);

	// Draw
	void Draw() const;

	// Update
	void Update(const float inDeltaTime);

private:
	std::deque<glm::vec2> mPoints;
	std::deque<float> mTimes;
	NotationType mType;
	ofColor mColor;
	float mWidth;
	float mDelayTime;

	void RemoveLastPoints();

};