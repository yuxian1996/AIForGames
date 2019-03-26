#pragma once

#include "../Action.h"

class DTNode
{
public: 
	DTNode() = default;
	virtual ~DTNode() = default;

	virtual std::shared_ptr<Action> GetAction() = 0;

};