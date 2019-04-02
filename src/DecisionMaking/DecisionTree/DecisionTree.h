#pragma once

#include "DTNode.h"
#include "../Action.h"
#include "../../Boid.h"
#include "../Context.h"

#include <memory>
#include <vector>

class DecisionTree
{
public:
	DecisionTree() = default;
	virtual ~DecisionTree() = default;

	virtual void Init() = 0;
	std::shared_ptr<Action> GetAction(const Context* const ipContext) { return mpRoot->GetAction(ipContext); }

protected:
	DTNode* mpRoot;
	std::vector<DTNode*> mNodes;
};