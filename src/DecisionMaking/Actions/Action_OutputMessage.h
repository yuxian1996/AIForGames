#pragma once

#include "../Action.h"

#include <string>

class Action_OutputMessage : public Action
{
public:
	Action_OutputMessage(const std::string inMessage, uint8_t inPriority = 0) : Action(inPriority), mMessage(inMessage) {}
	Action_OutputMessage(const std::string inMessage, const float inExpireTime, const float inExecuteTime, const uint8_t inPriority = 0)
		: Action(inExpireTime, inExecuteTime, inPriority), mMessage(inMessage) {}

	virtual ~Action_OutputMessage() override = default;

	virtual void OnActionExecute(Context* ipContext) override
	{
		std::cout << mMessage << std::endl;
	}

private:
	std::string mMessage;
};