#pragma once

#include "../Action.h"

class DecisionTree;

class DTNode
{
public: 
	DTNode() = default;
	virtual ~DTNode() = default;

	virtual std::shared_ptr<Action> GetAction() = 0;

	void SetTree(const DecisionTree* ipTree) { mpDecisioniTree = ipTree; }
	const DecisionTree* GetDecisionTree() { return mpDecisioniTree; }

protected:
	const DecisionTree* mpDecisioniTree;

};