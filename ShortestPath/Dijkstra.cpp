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
	Vertex* currentVertex = vertices[from].get();
	currentVertex->mark() = 0;

	while (currentVertex->id() != to)
	{
		double totalLength{};
		
		if (currentVertex->previousVertexID() != -1)
		{
			Vertex* previousVertex = vertices[currentVertex->previousVertexID()].get();
			totalLength += previousVertex->mark();
		}

		for (auto& edge : currentVertex->edges())
		{
			Vertex* nextVertex = vertices[edge->endVertexId()].get();
			double currLength = totalLength + edge->length();

			if (currLength < nextVertex->mark())
			{
				nextVertex->mark() = currLength;
				nextVertex->previousVertexID() = currentVertex->id();
			}

			s_unexplored.push(nextVertex);
		}

		currentVertex = s_unexplored.top();
		s_unexplored.pop();
	}

	return PathResult{ currentVertex->mark(), "" };
}
