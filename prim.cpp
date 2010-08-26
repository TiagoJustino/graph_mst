#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <list>
#include "prim.h"
#include "graph.h"
#include "edge.h"
#include "binary_heap.h"

using std::vector;
using std::list;
using std::pair;

class Weight {
    public:
        int vertex, parent;
        mpf_class weight;

        Weight(int _v, int _p, mpf_class _w):
            vertex(_v), parent(_p), weight(_w) {};

        bool operator<(const Weight& other) const {
            if(this->weight == -1) return false;
            if(other.weight == -1) return true;
            return this->weight < other.weight;
        };
};

vector<Edge> prim(Graph& g)
{
    vector<Edge> l;
    BinaryHeap<Weight> heap;
    vector<bool> marked(g.order(), false);
    vector<BinaryHeapNode<Weight>*> nodes(g.order());
    Weight initial(0, -1, 0.0); // parent -1 means no parent

    nodes[0] = heap.push_back(initial);
    marked[0] = true;
    for(int i = g.order() - 1; i; --i) {
        Weight w(i, -1, -1);// weight -1 means infinite
        nodes[i] = heap.push_back(w);
    }
    int n = g.order() - 1;

    while(n and !heap.empty()) {
        Weight w = heap.pop();
        if(w.parent != -1) { // Parent not null
            Vertex v1(g.findVertexById(w.parent));
            Vertex v2(g.findVertexById(w.vertex));

            Edge e(v1, v2, w.weight);
            marked[w.vertex] = true;
            l.push_back(e);
            --n;
        }

        list<pair<int, mpf_class> > neighbors = g.findVertexById(w.vertex).get_neighbors();
        list<pair<int, mpf_class> >::iterator i = neighbors.begin();
        for(; i != neighbors.end(); ++i) {
            if(marked[i->first]) continue;
            // the distance from graph to that vertice was still infinte;
            if(nodes[i->first]->el.weight == -1) {
                nodes[i->first]->el.weight = i->second;
                nodes[i->first]->el.parent = w.vertex;
                heap.update(nodes[i->first]);
            }
            else if(nodes[i->first]->el.weight > i->second) {
                nodes[i->first]->el.weight = i->second;
                nodes[i->first]->el.parent = w.vertex;
                heap.update(nodes[i->first]);
            }
        }
    }

    return l;
}

vector<Edge> prim(Graph& g, int max_degree)
{
    vector<Edge> l;
    BinaryHeap<Weight> heap;
    vector<bool> marked(g.order(), false);
    vector<int> degree(g.order(), 0);
    int n = g.order() - 1;
    list<pair<int, mpf_class> > _neighbors;
    list<pair<int, mpf_class> >::iterator _it;

    while(n) {
        int i;
        for(i = 0; i < g.order(); i++)
            if(marked[i] == false)
                break;
        if(i == g.order())
            break;
        marked[i] = true;
        _neighbors = g.findVertexById(i).get_neighbors();
        for(_it = _neighbors.begin(); _it != _neighbors.end(); ++_it) {
            if(marked[_it->first])
                continue;
            Weight w(_it->first, i, _it->second);
            heap.insert(w);
        }

        while(!heap.empty()) {
            Weight w = heap.pop();
            if(marked[w.vertex])
                continue;
            if(max_degree >= 0 and (degree[w.vertex] == max_degree or
                                    degree[w.parent] == max_degree))
                continue;
            Vertex v1(g.findVertexById(w.parent));
            Vertex v2(g.findVertexById(w.vertex));
            Edge e(v1, v2, w.weight);

            ++degree[w.vertex];
            ++degree[w.parent];
            marked[w.vertex] = true;
            l.push_back(e);
            --n;

            list<pair<int, mpf_class> > neighbors = g.findVertexById(w.vertex).get_neighbors();
            list<pair<int, mpf_class> >::iterator it = neighbors.begin();
            for(; it != neighbors.end(); ++it) {
                if(marked[it->first]) continue;
                Weight neww(it->first, w.vertex, it->second);
                heap.insert(neww);
            }
        }
    }

    return l;
}
