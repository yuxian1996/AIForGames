#pragma once

#include "DTNode.h"
#include "../Action.h"

#include <memory>

class DecisionTree
{
public:
	DecisionTree() = default;
	~DecisionTree() = default;

	void Init();
	std::shared_ptr<Action> GetAction() { mpRoot->GetAction(); }

protected:
	DTNode* mpRoot;
};