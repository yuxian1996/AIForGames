#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include <tuple>

class BTNode;
class BehaviorTree;

class Blackboard
{
public:
	Blackboard() = default;
	virtual ~Blackboard()
	{
		free(reinterpret_cast<void*>(mpGlobalMemory));
		free(reinterpret_cast<void*>(mpPerNodeMemory));
	}

	virtual void Init(std::vector<std::pair<std::string, uint16_t>> inGlobal, std::vector<std::tuple<std::string, uint8_t, uint16_t>> inPerNode)
	{
		for (auto pair : inGlobal)
		{
			mGlobalSize += pair.second;
		}
		mpGlobalMemory = reinterpret_cast<uintptr_t>(malloc(mGlobalSize));
		memset(reinterpret_cast<void*>(mpGlobalMemory), 0, mGlobalSize);

		uintptr_t globalPtr = mpGlobalMemory;
		for (auto pair : inGlobal)
		{
			mGlobals[pair.first] = globalPtr;
			globalPtr += pair.second;
		}

		for (auto tuple : inPerNode)
		{
			mPerNodeSize += std::get<2>(tuple);
		}
		mpPerNodeMemory = reinterpret_cast<uintptr_t>(malloc(mPerNodeSize));
		memset(reinterpret_cast<void*>(mpPerNodeMemory), 0, mPerNodeSize);

		uintptr_t perNodePtr = mpPerNodeMemory;
		for (auto tuple : inPerNode)
		{
			std::string key = std::get<0>(tuple) + "-" + std::to_string(std::get<1>(tuple));
			mPerNodes[key] = perNodePtr;
			perNodePtr += std::get<2>(tuple);
		}
	}

	static Blackboard* Copy(const Blackboard* ipBlackboard) 
	{ 
		Blackboard* copy = new Blackboard();

		copy->mGlobalSize = ipBlackboard->mGlobalSize;
		copy->mPerNodeSize = ipBlackboard->mPerNodeSize;

		copy->mpGlobalMemory = reinterpret_cast<uintptr_t>(malloc(copy->mGlobalSize));
		copy->mpPerNodeMemory = reinterpret_cast<uintptr_t>(malloc(copy->mPerNodeSize));
		memset(reinterpret_cast<void*>(copy->mpGlobalMemory), 0, copy->mGlobalSize);
		memset(reinterpret_cast<void*>(copy->mpPerNodeMemory), 0, copy->mPerNodeSize);

		uintptr_t globalPtr = copy->mpGlobalMemory;
		for (auto pair : ipBlackboard->mGlobals)
		{
			copy->mGlobals[pair.first] = globalPtr;
			globalPtr += pair.second;
		}

		uintptr_t perNodePtr = copy->mpPerNodeMemory;
		for (auto pair : ipBlackboard->mPerNodes)
		{
			copy->mPerNodes[pair.first] = perNodePtr;
			perNodePtr += pair.second;
		}

		return copy;
	}

	void* Get(std::string inKey) { return reinterpret_cast<void*>(mGlobals[inKey]); }
	template<class T>
	void Set(std::string inKey, const T& inValue)
	{
		*reinterpret_cast<T*>(mGlobals[inKey]) = inValue;
	}

	void* Get(std::string inKey, uint8_t inNodeID) 
	{ 
		std::string key = inKey + "-" + std::to_string(inNodeID);
		return reinterpret_cast<void*>(mPerNodes[key]);
	}
	template<class T>
	void Set(std::string inKey, const T& inValue, uint8_t inNodeID)
	{
		std::string key = inKey + "-" + std::to_string(inNodeID);
		*reinterpret_cast<T*>(mPerNodes[key])= inValue;
	}

private:
	std::unordered_map<std::string, uintptr_t> mGlobals;
	std::unordered_map<std::string, uintptr_t> mPerNodes;
	uintptr_t mpGlobalMemory;
	uintptr_t mpPerNodeMemory;
	uint16_t mGlobalSize = 0;
	uint16_t mPerNodeSize = 0;
};