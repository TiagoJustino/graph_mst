#include <vector>
#include <algorithm>
#include "kruskal.h"
#include "graph.h"
#include "edge.h"
#include "disjoint_sets.h"

using std::vector;
using std::greater;

vector<Edge> kruskal(Graph& g, int max_degree)
{
    vector<Edge> l;
    vector<Edge> heap;
    vector<Edge> tmp = g.getEdges();
    vector<int> degree(g.order(), 0);
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
        if(setA == setB or
            (max_degree >= 0 and (degree[e.getV1().getId()] == max_degree or
                                  degree[e.getV2().getId()] == max_degree))) {
            heap.pop_back();
            continue;
        }
        ++degree[e.getV1().getId()];
        ++degree[e.getV2().getId()];
        dsets.Union(setA, setB);
        l.push_back(e);
        //For some reason must be called l.push_back(e) before heap.pop_back()
        heap.pop_back();
        n--;
    }

    return l;
}

vector<Edge> kruskal(Graph& g)
{
    return kruskal(g, -1);
}
