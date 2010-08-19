#include "vertex.h"

Vertex::Vertex(mpf_class id, mpf_class x, mpf_class y) :
        id(id), x(x), y(y)
{
}

Vertex::Vertex(const Vertex &vertex) :
        id(vertex.id), x(vertex.x), y(vertex.y)
{
}

mpf_class Vertex::getId()
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
