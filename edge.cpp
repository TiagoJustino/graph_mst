#include "edge.h"

Edge::Edge(Vertex v1, Vertex v2, mpf_class cost) :
      v1(v1), v2(v2), cost(cost)
{
}

Edge::Edge(const Edge& e) :
      v1(Vertex(e.v1)), v2(Vertex(e.v2)), cost(e.cost)
{
}

Vertex& Edge::getV1()
{
    return this->v1;
}

Vertex& Edge::getV2()
{
    return this->v2;
}

mpf_class Edge::getCost()
{
    return this->cost;
}

bool Edge::operator>(const Edge& other) const
{
    return this->cost > other.cost;
}
