#pragma once
#include <queue>
#include <map>
#include <utility>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Vertex.hpp"

/// <summary>
/// @brief		-	Found shortest path
/// double      -	Path length
/// std::string -	Vertices in the path
/// </summary>
using PathResult = std::pair<double, std::string>;

struct DijkstraComparator
{
	bool operator()(Vertex* a, Vertex* b) const
	{
		return a->mark() > b->mark();
	}
};

struct AStarComparator
{
public:
	AStarComparator(Vertex*& destination)
		: m_destination{ destination } {}

	bool operator()(Vertex* a, Vertex* b) const
	{
		double fA = a->mark() + a->heuristic(m_destination);
		double fB = b->mark() + b->heuristic(m_destination);

		return fA > fB;
	}

private:
	Vertex*& m_destination;
};

class ShortestPath
{
public:
	ShortestPath() = delete;

	~ShortestPath() = delete;

	static void reinitVerticesMarks(ForwardStar& vertices);

	static PathResult dijkstraShortestPath(unsigned int from, unsigned int to, ForwardStar& vertices);

	static PathResult aStarShortestPath(unsigned int from, unsigned int to, ForwardStar& vertices);

private:
	inline static Vertex* s_destination = nullptr;
	inline static std::priority_queue<Vertex*, std::vector<Vertex*>, DijkstraComparator> s_unexploredDijkstra{};
	inline static std::priority_queue<Vertex*, std::vector<Vertex*>, AStarComparator> s_unexploredAStar{ AStarComparator(s_destination) };
};