#pragma once
#include <string>
#include <numeric>
#include <vector>
#include <memory>
#include "Edge.hpp"

class Vertex;

using ForwardStar = std::map<unsigned int, std::unique_ptr<Vertex>>;

class Vertex
{
public:
	Vertex(unsigned int id, std::string name)
		: m_id{ id }, m_name{ name }, m_previousVertexID {-1},
		  m_mark { std::numeric_limits<double>::max() } {};

	~Vertex() = default;

	inline unsigned int id() const { return m_id; }

	inline double& mark() { return m_mark; }

	inline int& previousVertexID() { return m_previousVertexID; }

	inline std::string& name() { return m_name; }

	inline std::vector<std::unique_ptr<Edge>>& edges() { return m_edges; }

private:
	unsigned int m_id;
	int m_previousVertexID;
	double m_mark;
	std::string m_name;
	std::vector<std::unique_ptr<Edge>> m_edges;
};