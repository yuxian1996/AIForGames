#include "Graph.h"

#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <algorithm>

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

Graph* Graph::GenerateRandomGraph(int numNode)
{
	std::vector<Node> nodes;
	for (int i = 0; i < numNode; i++)
	{
		nodes.push_back(Node((float)rand() / RAND_MAX * width, (float)rand() / RAND_MAX * height));
	}

	int numEdge = numNode * (float)rand() / RAND_MAX * 5;
	std::vector<Edge> edges;
	std::unordered_set<std::string> records;
	for (int i = 0; i < numEdge; i++)
	{
		int a = (numNode - 1) * (float)rand() / RAND_MAX;
		int b = (numNode - 1) * (float)rand() / RAND_MAX;
		std::string key = std::to_string(a) + "_" + std::to_string(b);
		if (a == b || records.find(key) != records.end())
			continue;

		// cost = [ distance, 3 * distance]
		float cost = Node::Distance(nodes[a], nodes[b]) * (1 + 2 * (float)rand() / RAND_MAX);
		edges.push_back(Edge(a, b, cost));
		edges.push_back(Edge(b, a, cost));
		records.insert(key);
		records.insert(std::to_string(b) + "_" + std::to_string(a));
	}

	return new Graph(nodes, edges);

}

bool Graph::FindPath(int inSource, int inDest, std::function<float(int, int)> inFunction)
{
	mRecords.clear();

	if (inSource == inDest)
	{	
#ifdef _DEBUG
		std::cout << inSource << std::endl;
#endif // DEBUG
		return true;
	}
	std::unordered_set<int> closeList;
	std::vector<int> openList;
	openList.push_back(inSource);

	int currentNode = -1;

	while (openList.size() != 0)
	{
		currentNode = openList.front();
		openList.erase(openList.begin());

		if (currentNode == inDest)
			break;

		// get all children
		auto outEdges = mEdges[currentNode];
		for (auto edge : outEdges)
		{
			int next = edge.GetDest();
			if (closeList.find(next) != closeList.end())
				continue;

			float h = inFunction(next, inDest);
			float g = mRecords[currentNode].GetCostSoFar() + edge.GetCost();
			float f = h + g;

			if (mRecords.find(next) == mRecords.end())
			{
				// add new record
				mRecords[next] = NodeRecord(next, edge, g, f);
				openList.push_back(next);
			}
			else if (mRecords[next].GetEstimatedTotal() > f)
			{
				// replace old record
				mRecords[next].SetCostSoFar(g);
				mRecords[next].SetEstimatedTotal(f);
				mRecords[next].SetIncomingEdge(edge);
			}
		}

		// resort
		auto& records = mRecords;
		std::sort(openList.begin(), openList.end(), [&records](int a, int b)
		{
			return records[a].GetEstimatedTotal() < records[b].GetEstimatedTotal();
		});
		closeList.insert(currentNode);
	}

	if (currentNode != inDest)
	{
		std::cout << "Can't find a valid path!" << std::endl;
		return false;
	}
	else
	{
		// output path
		std::vector<int> path;
		int last = mRecords[currentNode].GetInComingEdge().GetSource();
		while (last != inSource)
		{
			last = mRecords[currentNode].GetInComingEdge().GetSource();
			path.push_back(currentNode);
			currentNode = last;
		}
		std::reverse(path.begin(), path.end());

#ifdef _DEBUG
		std::cout << last + 1;
		for (auto i : path)
		{
			std::cout << "->" << i + 1;
		}
		std::cout << std::endl;

#endif // DEBUG

		return true;
	}
}
