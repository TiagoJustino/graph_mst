#include <vector>
#include <algorithm>
#include "kruskal.h"
#include "graph.h"
#include "edge.h"

using std::vector;
using std::greater;

vector<Edge> kruskal(Graph& g)
{
    vector<Edge> l;
    vector<Edge> heap;
    vector<Edge> tmp = g.getEdges();
    for(vector<Edge>::iterator i = tmp.begin(); i != tmp.end(); ++i) {
        Edge e(*i);
        heap.push_back(e);
    }
    printf("***************************\n");
    make_heap(heap.begin(), heap.end(), greater<Edge>()); 
    int n = g.order() - 1;

    while(n and !heap.empty()) {
        pop_heap(heap.begin(), heap.end(), greater<Edge>());
        Edge& e = heap.back();
        heap.pop_back();
        if(e.getV1().disjointSet() == e.getV2().disjointSet())
            continue;
        e.getV1().disjointSetJoin(e.getV2());
        l.push_back(e);
        n--;
    }

    return l;
}
