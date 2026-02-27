#include "Dijkstra.hpp"

void Dijkstra::reinitVerticesMarks(ForwardStar& vertices)
{
	for (auto& [id, vertex] : vertices)
	{
		vertex->mark() = std::numeric_limits<unsigned int>::max();
	}
}

PathResult Dijkstra::findShortestPath(unsigned int from, unsigned int to, ForwardStar& vertices)
{
	{
		auto itFrom = vertices.find(from);
		auto itTo = vertices.find(to);
		
		if (itFrom == vertices.end() || itTo == vertices.end())
		{
			throw std::runtime_error("Wrong input");
		}
	}

	int exploredVertices{};

	Vertex* currentVertex = vertices[from].get();
	currentVertex->mark() = 0;

	while (currentVertex->id() != to && exploredVertices < vertices.size())
	{
		double totalLength{};

		currentVertex->explored() = true; //questionable

		//if (currentVertex->previousVertexID() != -1)
		//{
		//	Vertex* previousVertex = vertices[currentVertex->previousVertexID()].get();
		//	totalLength += previousVertex->mark();
		//}

		for (auto& edge : currentVertex->edges())
		{
			Vertex* nextVertex = vertices[edge->endVertexId()].get();
			double currLength = currentVertex->mark() + edge->length();

			if (currLength < nextVertex->mark())
			{
				nextVertex->mark() = currLength;
				nextVertex->previousVertexID() = currentVertex->id();
			}

			if (!nextVertex->explored())
			{
				s_unexplored.push(nextVertex);
			}
		}

		++exploredVertices;
		currentVertex = s_unexplored.top();
		s_unexplored.pop();
	}

	return PathResult{ currentVertex->mark(), "" };
}
