#include <string>
#include "edge.h"
#include "vertex.h"

using namespace std;

Edge::Edge(Vertex& v1, Vertex& v2, mpf_class cost) :
      v1(v1), v2(v2), cost(cost)
{
    v1.add_neighbor(v2.getId(), cost);
    v2.add_neighbor(v1.getId(), cost);
}

Edge::Edge(Edge& e) :
      v1(e.v1), v2(e.v2), cost(e.cost)
{
}

Edge::Edge(const Edge& e) :
      v1(e.v1), v2(e.v2), cost(e.cost)
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

bool Edge::operator<(const Edge& other) const
{
    return this->cost < other.cost;
}
