#pragma once

#include "DTNode.h"
#include "../Action.h"
#include "../../Boid.h"

#include <memory>
#include <vector>

class DecisionTree
{
public:
	DecisionTree() = default;
	~DecisionTree() = default;

	virtual void Init() = 0;
	std::shared_ptr<Action> GetAction() { mpRoot->GetAction(); }

	const Boid* GetOwner() { return mpOwnerBoid; }

protected:
	DTNode* mpRoot;
	std::vector<DTNode*> mNodes;
	const Boid* mpOwnerBoid;	// cached owner for each GetAction, safe in single-thread
};