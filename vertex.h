#ifndef VERTEX_H
#define VERTEX_H

#include <gmpxx.h>

class Vertex
{
private:
    mpf_class id, x, y;
public:
    Vertex(mpf_class id, mpf_class x, mpf_class y);
    Vertex(const Vertex &vertex);
    mpf_class getId();
    mpf_class getX();
    mpf_class getY();
};

#endif // VERTEX_H
