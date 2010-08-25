#include <iostream>
#include <vector>
#include <list>
#include <set>
#include "disjoint_sets.h"
#include "boruvka.h"

using namespace std;

class edge_t {
public:
    int v1, v2;
    mpf_class w;
    bool operator<(edge_t o) { return this->w < o.w; }
    bool operator==(edge_t o) { return ((this->v1 == o.v1 and this->v2 == o.v2) or (this->v1 == o.v2 and this->v2 == o.v1)) and this->w == o.w; }
};

static list<int> listSets(const DisjointSets &ds)
{
    list<int> sets;
    for (int i = 0; i < ds.NumElements(); ++i)
    {
        if (ds.FindSet(i) == i)
            sets.push_front(i);
    }
    return sets;
}

static list<int> listElements(const DisjointSets &ds, int set)
{
    list<int> elements;
    for (int i = 0; i < ds.NumElements(); ++i)
    {
        if (ds.FindSet(i) == ds.FindSet(set))
            elements.push_front(i);
    }
    return elements;
}

vector<Edge> boruvka(Graph &g)
{
    DisjointSets cc(g.getVertices().size());
//  1 Begin with a connected graph G containing edges of distinct weights, and an empty set of edges T
    vector<Edge> t;

//  2 While the vertices of G connected by T are disjoint:
    while (cc.NumSets() != 1) {
        list<int> components(listSets(cc));
        list<int>::iterator component;
//  3   Begin with an empty set of edges E
        list<edge_t> e;
//  4   For each component:
        for (component = components.begin(); component != components.end(); ++component) {
            list<int> vertices(listElements(cc, *component));
            list<int>::iterator vertex;
//  5     Begin with an empty set of edges S
            list<edge_t> s;
//  6     For each vertex in the component:
            for (vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
//  7       Add the cheapest edge from the vertex in the component to another vertex in a disjoint component to S
                list< pair< int, mpf_class > > neighbour(g.findVertexById(*vertex).get_neighbors());

                pair< int, mpf_class > min;
                min.first = -1;

                for (list< pair< int, mpf_class > >::iterator i = neighbour.begin(); i != neighbour.end(); ++i) {
                    if (cc.FindSet(*vertex) == cc.FindSet((*i).first))
                        continue;
                    if (min.first == -1 or (*i).second < min.second)
                        min = *i;
                }

                if (min.first == -1) {
                    continue;
                }

                edge_t te;
                te.v1 = *vertex;
                te.v2 = min.first;
                te.w = min.second;
                s.push_front(te);
            }
//  8     Add the cheapest edge in S to E
            edge_t min_edge = *(s.begin());
            list<edge_t>::iterator edge;
            for (edge = (++s.begin()); edge != s.end(); ++edge) {
                if (min_edge.w > (*edge).w)
                    min_edge = (*edge);
            }
            bool pepe_jah_tirei_a_vela = false;
            for (list<edge_t>::iterator i = e.begin(); i != e.end(); ++i) {
                if (*i == min_edge)
                    pepe_jah_tirei_a_vela = true;
            }
            if (!pepe_jah_tirei_a_vela)
                e.push_front(min_edge);
        }
//  9   Add the resulting set of edges E to T.
        for (list<edge_t>::iterator edge = e.begin(); edge != e.end(); ++edge) {
            if(cc.FindSet(edge->v1) == cc.FindSet(edge->v2)) continue;
            cc.Union(cc.FindSet(edge->v1), cc.FindSet(edge->v2));
            Edge te(g.findVertexById(edge->v1), g.findVertexById(edge->v2), edge->w);
            t.push_back(te);
        }
    }
// 10 The resulting set of edges T is the minimum spanning tree of G.

    return t;
}
