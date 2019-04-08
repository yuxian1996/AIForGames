#pragma once

#include "../BTNode.h"

#include <vector>

class BTNode_Composite : public BTNode
{
public:
	BTNode_Composite() = default;
	virtual ~BTNode_Composite() override = default;

	void SetChildren(const std::vector<BTNode*>& inChildren) { mChildren = inChildren; }
	std::vector<BTNode*>& GetChildren() { return mChildren; }
	BTNode* GetChild(uint8_t index) 
	{ 
		if (index < 0 || index >= mChildren.size())
			return nullptr;
		return mChildren[index];
	}

};