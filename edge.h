#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"
#include <gmpxx.h>

class Edge
{
private:
    Vertex v1, v2;
    mpf_class cost;
public:
    Edge(Vertex v1, Vertex v2, mpz_class cost);
    Vertex getV1();
    Vertex getV2();
    mpz_class getCost();
    bool operator>(const Edge& other) const;
};

#endif // EDGE_H
