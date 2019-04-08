#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <cassert>

class BTNode;
class BehaviorTree;

class Blackboard
{
public:
	Blackboard() = default;
	virtual ~Blackboard() = default;

	virtual void Init() = 0;

	void* Get(std::string inKey) { return mGlobals[inKey]; }
	template<class T>
	void Set(std::string inKey, const T& inValue)
	{
		memcpy(mGlobals[inKey], &inValue, sizeof(T));
	}

	void* Get(std::string inKey, uint8_t inNodeID) { return mPerNodes[inNodeID][inKey]; }
	template<class T>
	void Set(std::string inKey, const T& inValue, uint8_t inNodeID)
	{
		*reinterpret_cast<T*>(mPerNodes[inNodeID][inKey])= inValue;
	}

private:
	std::unordered_map<std::string, void*> mGlobals;
	std::vector<std::unordered_map<std::string, void*>> mPerNodes;
	void* mpGlobalMemory;
	void* mpPerNodeMemory;
};