#pragma once
#include <utility>
#include <string>
#include "Vertex.hpp"

/// <summary>
/// @brief		-	Found shortest path
/// double      -	Path length
/// std::string -	Vertices in the path
/// </summary>
using PathResult = std::pair<double, std::string>;

class AStar
{
public:
	AStar() = delete;

	~AStar() = delete;

	PathResult findShortestPath(unsigned int from, unsigned int to, ForwardStar& vertices);


};