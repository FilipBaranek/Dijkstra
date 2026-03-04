#include "Vertex.hpp"

double Vertex::heuristic(Vertex* vertexTo) const
{
    double x = std::pow(m_xPos - vertexTo->xPos(), 2);
    double y = std::pow(m_yPos - vertexTo->yPos(), 2);

    return std::sqrt(x + y);
}