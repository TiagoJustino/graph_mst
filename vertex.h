#ifndef VERTEX_H
#define VERTEX_H

#include <gmpxx.h>
#include <vector>

using std::vector;

class Edge;

class Vertex
{
private:
    int id;
    mpf_class x, y;
    // neighbors
    vector<Edge> edges;

public:
    Vertex(int id, mpf_class x, mpf_class y);
    int getId();
    mpf_class getX();
    mpf_class getY();
    void add_neighbor(Edge& edge);
    vector<Edge>& get_neighbors();
};

#endif // VERTEX_H
