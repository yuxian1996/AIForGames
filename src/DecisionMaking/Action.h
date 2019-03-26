#pragma once

#include <cstdint>

class Action
{
public:
	Action() = default;
	Action(const uint8_t inPriority) : mPriority(inPriority) {}
	virtual ~Action() = default;

	void Execute(float inDeltaTime) { mRunningTime += inDeltaTime; OnActionExecute(); };
	void Wait(float inDeltaTime) { mWaitingTime += inDeltaTime; }
	bool ShouldExpire() { return mWaitingTime >= mExpireTime; }
	bool IsFinished() { return mRunningTime >= mExpireTime; }

	uint8_t GetPriority() const { return mPriority; }
	float GetExpireTime() const { return mExpireTime; }
	float GetWaitingTime() const { return mWaitingTime; }
	float GetExecuteTime() const { return mExecuteTime; }
	float GetRunningTime() const { return mRunningTime; }

protected:
	virtual void OnActionExecute() = 0;

private:
	float mExpireTime = 10.0f;
	float mWaitingTime = 0;
	float mExecuteTime = 3.0f;
	float mRunningTime = 0;
	uint8_t mPriority = 0;
	
};