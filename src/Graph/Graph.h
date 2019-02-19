#pragma once

#include "Edge.h"
#include "Node.h"
#include "NodeRecord.h"

#include <vector>
#include <unordered_map>
#include <functional>

/* Directional Weighted Graph*/
class Graph
{
public:
	Graph(const std::vector<Node>& inNodes, const std::vector<Edge>& inEdges);

	// Static ===============
	static Graph* GenerateRandomGraph(int numNode);
	static Graph* Load(const char* const inPath);

	// Getter ===============
	std::vector<Edge> GetEdge(int inNode) { return mEdges[inNode]; }
	Node GetNode(int inNode) const { return mNodes[inNode]; }
	std::unordered_map<int, NodeRecord>& GetRecord() { return mRecords; }
	
	void ClearRecord() { mRecords.clear(); }
	bool FindPath(int inSource, int inDest, std::function<float(int, int)> inFunction);

	static const int width = 1000;
	static const int height = 1000;

private:	
	std::unordered_map<int, std::vector<Edge>> mEdges;
	std::unordered_map<int, NodeRecord> mRecords;
	std::vector<Node> mNodes;

};