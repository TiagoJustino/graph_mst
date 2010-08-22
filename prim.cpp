#include <vector>
#include <algorithm>
#include "prim.h"
#include "graph.h"
#include "edge.h"
#include "binary_heap.h"

using std::vector;
using std::greater;

class Weight {
    public:
        int v, p;
        mpf_class w;

        Weight(int _v, int _p, mpf_class _w): v(_v), p(_p), w(_w) {};
        bool operator<(const Weight& other) const { return this->w < other.w; };
};

vector<Edge> prim(Graph& g)
{
    vector<Edge> l;
    BinaryHeap<Weight> heap;
    BinaryHeapNode<Weight> **nodes;
    nodes = (BinaryHeapNode<Weight> **)malloc(g.order() * sizeof(BinaryHeapNode<Weight> *));
    Weight initial(0, -1, 0.0);

    //TODO: verify the value of INFINITE
    nodes[0] = heap.push_back(initial);
    for(int i = g.order() - 1; i; --i) {
        Weight w(i, -1, -1);// weight -1 means infinite
        nodes[i] = heap.push_back(w);
    }
    int n = g.order() - 1;

    while(n and !heap.empty()) {
        Weight& w = heap.pop();
        if(w.p != -1) { // Parent not null
            Vertex _v1 = g.findVertexById(w.p);
            Vertex _v2 = g.findVertexById(w.v);
            Vertex v1(_v1.getId(), _v1.getX(), _v1.getY());
            Vertex v2(_v2.getId(), _v2.getX(), _v2.getY());

            Edge e(v1, v2, w.w);
            l.push_back(e);
        }
        vector<Edge>& neighbors = g.findVertexById(w.v).get_neighbors();
        vector<Edge>::iterator i = neighbors.begin();

        for(; i != neighbors.end(); ++i) {
            //TODO: see how to do this in c++
            if(w.v == i->getV1().getId() and w.v != i->getV2().getId() and
               nodes[i->getV2().getId()]->el.w > w.w) {
                nodes[i->getV2().getId()]->el.p = w.v;
                nodes[i->getV2().getId()]->el.w = w.w;
                heap.update(nodes[i->getV2().getId()]);
            }
            else if(w.v == i->getV2().getId() and w.v != i->getV1().getId() and
                    nodes[i->getV2().getId()]->el.w > w.w) {
                nodes[i->getV2().getId()]->el.p = w.v;
                nodes[i->getV2().getId()]->el.w = w.w;
                heap.update(nodes[i->getV1().getId()]);
            }
        }
        --n;
    }
    free(nodes);

    return l;
}
