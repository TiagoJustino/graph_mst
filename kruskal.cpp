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
        heap.pop_back();
        int setA = dsets.FindSet(e.getV1().getId()),
            setB = dsets.FindSet(e.getV2().getId());
        if(setA == setB) {
            //mp_exp_t exp;
            //std::string s;
            //s = e.getCost().get_str(exp);
            //if((int)exp < (int)s.size()) s.insert(exp, ".");
            //else for(int n = s.size(); n < exp; n++) s += "0";
            //printf("%d %d (cost=[%s]) are in same set\n", e.getV1().getId(),
                   //e.getV2().getId(), s.c_str());
            continue;
        }
        //printf("joining %d %d\n", e.getV1().getId(), e.getV2().getId());
        dsets.Union(setA, setB);
        l.push_back(e);
        n--;
    }

    return l;
}
