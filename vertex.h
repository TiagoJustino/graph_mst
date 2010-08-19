#ifndef VERTEX_H
#define VERTEX_H

#include <gmpxx.h>

class Vertex
{
private:
    int id;
    mpf_class x, y;
public:
    Vertex(int id, mpf_class x, mpf_class y);
    Vertex(const Vertex &vertex);
    int getId();
    mpf_class getX();
    mpf_class getY();
};

#endif // VERTEX_H
