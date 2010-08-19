#include "vertex.h"

Vertex::Vertex(int id, mpf_class x, mpf_class y) :
        id(id), x(x), y(y), rank(0)
{
    this->parent = this;
}

Vertex::Vertex(const Vertex &vertex) :
        id(vertex.id), x(vertex.x), y(vertex.y)
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

Vertex* Vertex::disjointSet()
{
    Vertex *r;
    for(r = this; r != r->parent; r = r->parent);
    return r;
}

void Vertex::disjointSetJoin(Vertex &v)
{
    Vertex *a = this->disjointSet(), *b = v.disjointSet();
    if(a == b) return;
    if(a->rank > b->rank)
        b->parent = a;
    else {
        a->parent = b;
        if(a->rank == b->rank) b->rank++;
    }
}
