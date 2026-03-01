#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include "Loader.hpp"
#include "Dijkstra.hpp"

namespace
{
	static constexpr const char* verticesPath = "../data/TestMatica/SR_uzly.ATR";
	static constexpr const char* edgesPath = "../data/TestMatica/SR_cesty.ATR";
	static constexpr const char* incidentalVerticesPath = "../data/TestMatica/SR_incid.txt";
}

int main()
{
	_CrtDumpMemoryLeaks();

	{
		auto vertices = Loader::loadVertices(verticesPath);
		Loader::loadEdges(vertices, incidentalVerticesPath, edgesPath);

		auto shortestPath = Dijkstra::findShortestPath(320, 1178, vertices);

		std::cout << "Route length: " << shortestPath.first << "\n";
		std::cout << "Route:\n" << shortestPath.second << "\n";
	}

	return 0;
}