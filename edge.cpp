#include "edge.h"

Edge::Edge(Vertex v1, Vertex v2, mpz_class cost) :
        v1(v1), v2(v2), cost(cost)
{
}

Vertex Edge::getV1()
{
    return this->v1;
}

Vertex Edge::getV2()
{
    return this->v2;
}

mpz_class Edge::getCost()
{
    return this->cost;
}

bool Edge::operator>(const Edge& other) const
{
    return this->cost > other.cost;
}
