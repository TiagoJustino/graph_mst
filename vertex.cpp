#include "vertex.h"

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
