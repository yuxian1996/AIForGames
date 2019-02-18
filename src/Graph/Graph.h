#pragma once

#include "Edge.h"
#include "Node.h"
#include "NodeRecord.h"

#include <vector>
#include <unordered_map>

/* Directional Weighted Graph*/
class Graph
{
public:
	Graph(const std::vector<Node>& inNodes, const std::vector<Edge>& inEdges);

	static Graph* Load(const char* const inPath);

	std::vector<Edge> GetEdge(int inNode) { return mEdges[inNode]; }
	Node GetNode(int inNode) const { return mNodes[inNode]; }
	std::unordered_map<int, NodeRecord>& GetRecord() { return mRecords; }

private:
	std::unordered_map<int, std::vector<Edge>> mEdges;
	std::unordered_map<int, NodeRecord> mRecords;
	std::vector<Node> mNodes;
};