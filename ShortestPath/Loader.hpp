#pragma once
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <exception>
#include "Vertex.hpp"

class Loader
{
public:
	Loader() = delete;

	~Loader() = delete;

	static ForwardStar loadVertices(std::string filePath);

	static void loadEdges(ForwardStar& vertices, std::string incidentalVerticesFilePath, std::string edgesFilePath);
};