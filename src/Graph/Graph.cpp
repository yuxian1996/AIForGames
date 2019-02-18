#include "Graph.h"

#include <fstream>

Graph::Graph(const std::vector<Node>& inNodes, const std::vector<Edge>& inEdges) : mNodes(inNodes)
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

Graph* Graph::Load(const char * const inPath)
{
	int numNode, numEdge;

	std::ifstream stream(std::string(inPath), std::ifstream::in);

	stream >> numNode;
	std::vector<Node> nodes;
	for (int i = 0; i < numNode; i++)
	{
		float x, y;
		stream >> x >> y;
		nodes.push_back(Node(x, y));
	}
	
	stream >> numEdge;
	std::vector<Edge> edges;
	for (int i = 0; i < numEdge; i++)
	{
		int source, dest;
		float cost;
		stream >> source >> dest >> cost;
		edges.push_back(Edge(source - 1, dest - 1, cost));
		edges.push_back(Edge(dest - 1, source - 1, cost));
	}

	auto graph = new Graph(nodes, edges);
	return graph;
}
