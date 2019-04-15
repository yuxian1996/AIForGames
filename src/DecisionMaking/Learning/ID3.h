#pragma once

#include "../Context.h"
#include "../../Steering/ComplexSteering/PathFollow.h"
#include "../Actions/Action_ChangeTarget.h"
#include "../Actions/Action_MoveToPlayer.h"
#include "../Actions/Action_StartMoving.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <cmath>

enum class DistanceToPlayer : uint8_t
{
	CLOSE,
	MEDIUM,
	DFAR
};

struct ID3_Node
{
	uint8_t attribute;
	std::vector<ID3_Node*> children;
};

struct ID3_Set
{
	uint8_t distanceToPlayer;
	uint8_t isReach;
	uint8_t Action;

	uint8_t operator[](uint8_t index) const
	{
		switch (index)
		{
		case 0:
			return distanceToPlayer;
		case 1:
			return isReach;
		case 2:
			return Action;
		default:
			break;
		}
	}
};

class ID3
{
public:
	void Init()
	{
		out.open(trainingFilePath, std::ofstream::app);
	}

	void Finish()
	{
		out.close();
	}

	void SaveAttribute(const Context* ipContext )
	{
		out << static_cast<int>(GetDistanceToPlayer(ipContext)) << static_cast<int>(ReachTarget(ipContext));
	}
	void SaveAction(const std::shared_ptr<Action> inAction)
	{
		Action* action = inAction.get();
		int output = 0;
		if (auto derivedAction = dynamic_cast<Action_StartMoving*>(action))
		{
			output = 0;
		}
		else if (auto derivedAction = dynamic_cast<Action_MoveToPlayer*>(action))
		{
			output = 1;
		}
		else if (auto derivedAction = dynamic_cast<Action_ChangeTarget*>(action))
		{
			output = 2;
		}
		out << output << std::endl;
	}

	void Train()
	{
		std::cout << "Start Training..." << std::endl;
		std::ifstream in;
		in.open(trainingFilePath);
		std::vector<ID3_Set> sets;
		while(!in.eof())
		{
			ID3_Set set;
			in >> set.distanceToPlayer >> set.isReach >> set.Action;
			set.distanceToPlayer -= '0';
			set.isReach -= '0';
			set.Action -= '0';
			sets.push_back(set);
		}


		auto root = GetRoot({ 0, 1 }, {3, 2}, sets);
		resultOut.open("data/result.txt", std::ofstream::trunc);

		OutputNode(root);

		resultOut.close();
	}

private:
	std::ofstream out;
	const std::string trainingFilePath = "data/Traning.txt";
	std::ofstream resultOut;

	void OutputNode(ID3_Node* node)
	{
		if (node == nullptr)
			return;

		resultOut << (int)node->attribute << std::endl;
		for (int i = 0; i < node->children.size(); i++)
		{
			OutputNode(node->children[i]);
		}
	}

	ID3_Node* GetRoot(std::vector<uint8_t> attributes, std::vector<uint8_t> attributesMax, std::vector<ID3_Set>& data)
	{
		if (data.size() == 0)
		{
			return nullptr;
		}

		if (attributes.size() == 0)
		{
			return nullptr;
		}

		if (attributes.size() == 1)
		{
			ID3_Node* newNode = new ID3_Node;
			
			std::vector<int> label(attributesMax[0], 0);
			for (int i = 0; i < data.size(); i++)
			{
				for (int j = 0; j < attributesMax[0]; j++)
				{
					if (data[i][attributesMax[0]] == j)
					{
						label[j] = (data[i][2]);
					}
				}
			}

			newNode->attribute = attributes[0];
			for (int i = 0; i < attributesMax[0]; i++)
			{
				auto node = new ID3_Node;
				node->attribute = label[i];
				newNode->children.push_back(node);
			}

			return newNode;
		}


		int maxAttri = 0;
		float maxG = 0;
		for (int i = 0; i < attributes.size(); i++)
		{
			int max = attributesMax[i];

			float g = GetGain(i, max, data);
			if (g > maxG)
			{
				maxG = g;
				maxAttri = i;
			}
		}

		ID3_Node* newNode = new ID3_Node;
		newNode->attribute = maxAttri;
		int count = attributesMax[maxAttri];
		attributes.erase(attributes.begin() + maxAttri);
		attributesMax.erase(attributesMax.begin() + maxAttri);

		for (int i = 0; i < count; i++)
		{
			// remove 
			for (int j = 0; j < data.size(); j++)
			{
				if (data[j][maxAttri] == i)
				{
					data.erase(data.begin() + j);
					j--;
				}
			}

			auto node = GetRoot(attributes, attributesMax, data);
			newNode->children.push_back(node);
		}

		return newNode;
	}

	float GetGain( uint8_t attriIndex, uint8_t count, const std::vector<ID3_Set>& data)
	{
		std::vector<uint8_t> labels(data.size(), 0);
		for (int i = 0; i < data.size(); i++)
		{
			labels[i] = data[i].Action;
		}

		float sum = 0;
		for (int i = 0; i < count; i++)
		{
			std::vector<ID3_Set> subSet;
			for(int j = 0; j < data.size(); j++)
			{
				if(data[i][attriIndex] == j)
				{
					subSet.push_back(data[i]);
				}
			}

			sum += (float)subSet.size() / data.size() * GetEntropy(subSet);
		}
		
		return GetEntropy(data) - sum;

	}

	float GetEntropy(const std::vector<ID3_Set>& data)
	{
		std::unordered_map <uint8_t, float> posibilities;

		float step = 1.0f / data.size();
		for (int i = 0; i < data.size(); i++)
		{
			if (posibilities.find(data[i].Action) == posibilities.end())
				posibilities[data[i].Action] = step;
			else
				posibilities[data[i].Action] += step;
		}

		float entropy = 0;
		for (auto p : posibilities)
		{
			entropy -= p.second * std::log2f(p.second);
		}

		return entropy;
	}

	bool ReachTarget(const Context* ipContext)
	{
		auto owner = ipContext->GetOwner();
		PathFollow* steering = dynamic_cast<PathFollow*>(owner->mpDynamicSteering);

		if (owner->mpTarget == nullptr || steering == nullptr)
			return false;
		auto corners = steering->GetCorners();
		if (
			glm::distance(owner->GetKinematic()->position, corners[corners.size() - 1].position) <= 10.0f)
			return true;
		return false;
	}

	DistanceToPlayer GetDistanceToPlayer(const Context* ipContext)
	{
		auto owner = ipContext->GetOwner();
		auto player = owner->mpPlayer;

		float distance = glm::distance(owner->GetKinematic()->position, player->GetKinematic()->position);
		if (distance <= 200.0f)
			return DistanceToPlayer::CLOSE;
		else if (distance <= 400.0f)
			return DistanceToPlayer::MEDIUM;
		else
			return DistanceToPlayer::DFAR;
	}
};