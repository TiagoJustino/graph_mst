#ifndef VERTEX_H
#define VERTEX_H

#include <gmpxx.h>

class Vertex
{
private:
    int id;
    mpf_class x, y;
    //Disjoint Set attributes
    Vertex* parent;
    int rank;

public:
    Vertex(int id, mpf_class x, mpf_class y);
    Vertex(const Vertex &vertex);
    int getId();
    mpf_class getX();
    mpf_class getY();
    Vertex* disjointSet();
    void disjointSetJoin(Vertex &v);
};

#endif // VERTEX_H
