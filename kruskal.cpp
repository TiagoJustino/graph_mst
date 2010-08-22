#include <vector>
#include <algorithm>
#include "kruskal.h"
#include "graph.h"
#include "edge.h"
#include "disjoint_sets.h"

using std::vector;
using std::greater;

vector<Edge> kruskal(Graph& g)
{
    vector<Edge> l;
    vector<Edge> heap;
    vector<Edge> tmp = g.getEdges();
    DisjointSets dsets(tmp.size());

    for(vector<Edge>::iterator i = tmp.begin(); i != tmp.end(); ++i) {
        Edge e(*i);
        heap.push_back(e);
    }
    make_heap(heap.begin(), heap.end(), greater<Edge>()); 
    int n = g.order() - 1;

    while(n and !heap.empty()) {
        pop_heap(heap.begin(), heap.end(), greater<Edge>());
        Edge& e = heap.back();
        int setA = dsets.FindSet(e.getV1().getId()),
            setB = dsets.FindSet(e.getV2().getId());
        if(setA == setB) {
            heap.pop_back();
            continue;
        }
        dsets.Union(setA, setB);
        l.push_back(e);
        //For some reason must be called l.push_back(e) before heap.pop_back()
        heap.pop_back();
        n--;
    }

    return l;
}
