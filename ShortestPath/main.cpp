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

		/*for (auto& [id, vertex] : vertices)
		{
			std::cout << "ID: " << id << " Name: " << vertex->name() << " Edges: \n";
			
			for (auto& edge : vertex->edges())
			{
				std::cout << "ID: " << edge->id() << " Length: " << edge->length() << " End vertex: " << edge->endVertexId() << "\n";
			}

			std::cout << "\n\n";
		}*/


		auto shortestPath = Dijkstra::findShortestPath(288, 289, vertices);

		std::cout << shortestPath.first << "\n";
	}

	return 0;
}