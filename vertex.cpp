#include "vertex.h"

Vertex::Vertex(int id, mpf_class x, mpf_class y) :
        id(id), x(x), y(y), parent(NULL), rank(0)
{
}

Vertex::Vertex(const Vertex &vertex) :
        id(vertex.id), x(vertex.x), y(vertex.y), parent(vertex.parent),
        rank(vertex.rank)
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
    for(r = this; r->parent; r = r->parent) printf("[%p]\n", r);
    printf("Returning [%p]\n", r);
    return r;
}

void Vertex::disjointSetJoin(Vertex &v)
{
    Vertex *a = this->disjointSet(), *b = v.disjointSet();
    printf("Joining [%p] to [%p]\n", a, b);
    if(a == b) return;
    if(a->rank > b->rank)
        b->parent = a;
    else {
        a->parent = b;
        if(a->rank == b->rank)
            b->rank++;
    }
}
