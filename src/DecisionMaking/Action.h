#pragma once

#include "Context.h"

#include <cstdint>

class Action
{
public:
	//Action() = default;
	Action(const uint8_t inPriority = 0) : mPriority(inPriority) {}
	Action(const float inExpireTime, const float inExecuteTime, const uint8_t inPriority = 0)
		: mExpireTime(inExpireTime), mExecuteTime(inExecuteTime), mPriority(inPriority) {}
	virtual ~Action() = default;

	void Execute(float inDeltaTime, Context* ipContext) { mRunningTime += inDeltaTime; OnActionExecute(ipContext); };
	void Wait(float inDeltaTime) { mWaitingTime += inDeltaTime; }
	bool ShouldExpire() { return mWaitingTime >= mExpireTime; }
	bool IsFinished() { return mRunningTime >= mExecuteTime; }

	uint8_t GetPriority() const { return mPriority; }
	float GetExpireTime() const { return mExpireTime; }
	float GetWaitingTime() const { return mWaitingTime; }
	float GetExecuteTime() const { return mExecuteTime; }
	float GetRunningTime() const { return mRunningTime; }

	void Reset() { mWaitingTime = 0; mRunningTime = 0; }

protected:
	virtual void OnActionExecute(Context* ipContext) = 0;

private:
	float mExpireTime = 10.0f;
	float mWaitingTime = 0;
	float mExecuteTime = 3.0f;
	float mRunningTime = 0;
	uint8_t mPriority = 0;
};