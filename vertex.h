#ifndef VERTEX_H
#define VERTEX_H

#include <gmpxx.h>
#include <utility>
#include <list>

using std::list;
using std::pair;

class Vertex
{
private:
    int id;
    mpf_class x, y;
    // neighbors
    list<pair<int, mpf_class> > neighbors;

public:
    Vertex(int id, mpf_class x, mpf_class y);
    int getId();
    mpf_class getX();
    mpf_class getY();
    void add_neighbor(int id, mpf_class cost);
    list<pair<int, mpf_class> > get_neighbors();
};

#endif // VERTEX_H
