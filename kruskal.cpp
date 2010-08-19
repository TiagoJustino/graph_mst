#include "kruskal.h"
#include "graph.h"
#include "edge.h"
#include <vector>
#include <algorithm>

using std::vector;

Graph kruskal(Graph& g)
{
    vector<Edge> e = g.getEdges();
    make_heap(e.begin(), e.end()); 

    return g;
}
