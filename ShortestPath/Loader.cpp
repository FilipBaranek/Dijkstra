#include "Loader.hpp"

ForwardStar Loader::loadVertices(std::string filePath)
{
	ForwardStar vertices;
	std::ifstream file(filePath);

	if (!file)
	{
		throw std::runtime_error("Vertex file not found");
	}

	std::string line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string name;
		unsigned int id;

		if (ss >> id)
		{
			std::getline(ss >> std::ws, name);
		}

		vertices[id] = std::make_unique<Vertex>(id, name);
	}

	return vertices;
}

void Loader::loadEdges(
	ForwardStar& vertices,
	std::string incidentalVerticesFilePath,
	std::string edgesFilePath
)
{
	std::ifstream edgesFile(edgesFilePath);
	std::ifstream incidentalVerticesFile(incidentalVerticesFilePath);

	if (!edgesFile)
	{
		throw std::runtime_error("Edges file not found");
	}
	else if (!incidentalVerticesFile)
	{
		throw std::runtime_error("Incidental vertices file not found");
	}

	unsigned int edgeFileID, incidentalFileEdgeID, startVertexId, endVertexId;
	double length;

	while (edgesFile >> edgeFileID)
	{
		incidentalVerticesFile >> incidentalFileEdgeID;

		if (edgeFileID != incidentalFileEdgeID)
		{
			throw std::runtime_error("Edge index missmatch");
		}

		incidentalVerticesFile >> startVertexId;
		incidentalVerticesFile >> endVertexId;
		edgesFile >> length;

		vertices[startVertexId]->edges().emplace_back(std::make_unique<Edge>(edgeFileID, endVertexId, length));
		vertices[endVertexId]->edges().emplace_back(std::make_unique<Edge>(edgeFileID, startVertexId, length));
	}
}
