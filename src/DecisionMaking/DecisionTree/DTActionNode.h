#pragma once

#include "DTNode.h"

#include <vector>
#include <memory>

class Context;

class DTActionNode : public DTNode
{
public:
	DTActionNode(std::shared_ptr<Action> ipAction) { mpAction = ipAction; }
	virtual ~DTActionNode() = default;

	virtual std::shared_ptr<Action> GetAction(const Context* const ipContext) override { return mpAction; }

protected:
	std::shared_ptr<Action> mpAction;
};