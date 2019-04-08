#pragma once

#include <unordered_set>

class Blackboard;
class BehaviorTree;
class BTNode;

class BTTick
{
public:
	//BTTick() = default;
	BTTick(Blackboard* ipBlackboard, BehaviorTree* ipTree) : mpBlackboard(ipBlackboard), mpTree(ipTree) {}
	~BTTick() = default;

	void OpenNode(BTNode* ipNode) { mOpenNodes.insert(ipNode); }
	void CloseNode(BTNode* ipNode) { mOpenNodes.erase(ipNode); }

	void SetEnterNode(BTNode* ipNode) { mpEnterNode = ipNode; }
	void SetExecuteNode(BTNode* ipNode) { mpExecuteNode = ipNode; }
	void SetExitNode(BTNode* ipNode) { mpExitNode = ipNode; }

	Blackboard* GetBlackboard() { return mpBlackboard; }
	BehaviorTree* GetBehaviorTree() { return mpTree; }

private:
	BehaviorTree* mpTree;
	Blackboard* mpBlackboard;
	std::unordered_set<BTNode*> mOpenNodes;

	BTNode* mpEnterNode = nullptr;
	BTNode* mpExecuteNode = nullptr;
	BTNode* mpExitNode = nullptr;
};