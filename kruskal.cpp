#include "kruskal.h"
#include "graph.h"
#include "edge.h"
#include <vector>
#include <algorithm>
#include <functional>

using std::vector;
using std::greater;

vector<Edge> kruskal(Graph& g)
{
    vector<Edge> l;
    vector<Edge> heap = g.getEdges();
    make_heap(heap.begin(), heap.end(), greater<Edge>()); 
    int n = g.order() - 1;

    while(n and !heap.empty()) {
        pop_heap(heap.begin(), heap.end(), greater<Edge>());
        Edge e(heap.back());
        heap.pop_back();
        if(e.getV1().disjointSet() == e.getV2().disjointSet())
            continue;
        l.push_back(e);
        n--;
    }

    return l;
}
