#pragma once

#include "Edge.h"
#include "Node.h"

#include <vector>
#include <unordered_map>

/* Directional Weighted Graph*/
class Graph
{
public:
	Graph(const std::vector<Node>& inNodes, const std::vector<Edge>& inEdges)
		: mNodes(inNodes)
	{
		for (auto edge : inEdges)
		{
			int node = edge.GetSource();
			if (mEdges.find(node) == mEdges.end())
			{
				mEdges[node] = std::vector<Edge>({ edge });
			}
			else
			{
				mEdges[node].push_back(edge);
			}
		}
	}

	std::vector<Edge> GetEdge(int inNode) { return mEdges[inNode]; }
	Node GetNode(int inNode) const { return mNodes[inNode]; }

private:
	std::unordered_map<int, std::vector<Edge>> mEdges;
	std::vector<Node> mNodes;
};