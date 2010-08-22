#include "vertex.h"
#include "edge.h"

Vertex::Vertex(int id, mpf_class x, mpf_class y) :
        id(id), x(x), y(y)
{
}

int Vertex::getId()
{
    return this->id;
}

mpf_class Vertex::getX()
{
    return this->x;
}

mpf_class Vertex::getY()
{
    return this->y;
}

void Vertex::add_neighbor(Edge& edge)
{
    this->edges.push_back(edge);
}

vector<Edge>& Vertex::get_neighbors()
{
    return this->edges;
}
