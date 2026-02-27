#pragma once

class Edge
{
public:
	Edge(unsigned int id, unsigned int endVertexId, double length)
		: m_id{ id }, m_endVertexId{ endVertexId }, m_length{ length } {}

	~Edge() = default;

	inline unsigned int id() { return m_id; }
	
	inline unsigned int endVertexId() { return m_endVertexId; }

	inline double length() { return m_length; }

private:
	unsigned int m_id;
	unsigned int m_endVertexId;
	double m_length;
};