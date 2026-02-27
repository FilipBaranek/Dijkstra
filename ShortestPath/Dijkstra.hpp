#pragma once
#include <queue>
#include <map>
#include <utility>
#include <string>
#include "Vertex.hpp"

using PathResult = std::pair<double, std::string>;

struct PriorityComparator
{
	bool operator()(Vertex* a, Vertex* b)
	{
		return a->mark() > b->mark();
	}
};

class Dijkstra
{
public:
	Dijkstra() = delete;

	~Dijkstra() = delete;

	static void reinitVerticesMarks(ForwardStar& vertices);

	static PathResult findShortestPath(unsigned int from, unsigned int to, ForwardStar& vertices);

private:
	inline static std::priority_queue<Vertex*, std::vector<Vertex*>, PriorityComparator> s_unexplored{};
};