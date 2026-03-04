#include "ShortestPath.hpp"

void ShortestPath::reinitVerticesMarks(ForwardStar& vertices)
{
    for (auto& [id, vertex] : vertices)
    {
        vertex->mark() = std::numeric_limits<double>::max();
    }

    while (!s_unexploredAStar.empty())
    {
        s_unexploredAStar.pop();
    }

    while (!s_unexploredDijkstra.empty())
    {
        s_unexploredDijkstra.pop();
    }
}

PathResult ShortestPath::dijkstraShortestPath(unsigned int from, unsigned int to, ForwardStar& vertices)
{
	auto itFrom = vertices.find(from);
	auto itTo = vertices.find(to);

	if (itFrom == vertices.end() || itTo == vertices.end())
	{
		throw std::runtime_error("Wrong input");
	}

	int exploredVertices{};

	Vertex* currentVertex = vertices[from].get();
	currentVertex->mark() = 0;

	while (currentVertex->id() != to && exploredVertices < vertices.size())
	{
		double totalLength{};

		currentVertex->explored() = true;

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
				s_unexploredDijkstra.push(nextVertex);
			}
		}

		++exploredVertices;
		currentVertex = s_unexploredDijkstra.top();
		s_unexploredDijkstra.pop();
	}

    if (!currentVertex || currentVertex->id() != to)
    {
        return { -1.0, "No path found" };
    }

	std::vector<Vertex*> verticesInFoundPath;
	while (true)
	{
		verticesInFoundPath.push_back(currentVertex);

		if (currentVertex->previousVertexID() == -1)
		{
			break;
		}

		currentVertex = vertices[currentVertex->previousVertexID()].get();
	}

	std::ostringstream oss;
	for (int i = verticesInFoundPath.size() - 1; i >= 0; --i)
	{
		oss << verticesInFoundPath.at(i)->id();

		if (verticesInFoundPath.at(i) != verticesInFoundPath.front())
		{
			oss << "->";
		}
	}

	return { verticesInFoundPath.front()->mark(), oss.str() };
}

PathResult ShortestPath::aStarShortestPath(unsigned int from, unsigned int to, ForwardStar& vertices)
{
    auto itFrom = vertices.find(from);
    auto itTo = vertices.find(to);

    if (itFrom == vertices.end() || itTo == vertices.end())
    {
        throw std::runtime_error("Wrong input");
    }

    s_destination = vertices[to].get();

    Vertex* startVertex = vertices[from].get();
    startVertex->mark() = 0;
    startVertex->previousVertexID() = -1;

    s_unexploredAStar.push(startVertex);

    Vertex* currentVertex = nullptr;

    while (!s_unexploredAStar.empty())
    {
        currentVertex = s_unexploredAStar.top();
        s_unexploredAStar.pop();

        if (currentVertex->explored())
        {
            continue;
        }
        currentVertex->explored() = true;

        if (currentVertex->id() == to)
        {
            break;
        }

        for (auto& edge : currentVertex->edges())
        {
            Vertex* nextVertex = vertices[edge->endVertexId()].get();
            double currLength = currentVertex->mark() + edge->length();;

            if (currLength < nextVertex->mark())
            {
                nextVertex->mark() = currLength;
                nextVertex->previousVertexID() = currentVertex->id();

                s_unexploredAStar.push(nextVertex);
            }
        }
    }

    if (!currentVertex || currentVertex->id() != to)
    {
        return { -1.0, "No path found" };
    }
    
    std::vector<Vertex*> path;
    while (currentVertex)
    {
        path.push_back(currentVertex);

        if (currentVertex->previousVertexID() == -1)
        {
            break;
        }

        currentVertex = vertices[currentVertex->previousVertexID()].get();
    }

    std::ostringstream oss;

    for (int i = static_cast<int>(path.size()) - 1; i >= 0; --i)
    {
        oss << path[i]->id();

        if (i != 0)
        {
            oss << "->";
        }
    }

    return { path.front()->mark(), oss.str() };
}