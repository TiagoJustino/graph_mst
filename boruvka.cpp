#include <vector>
#include <list>
#include <set>
#include "disjoint_sets.h"
#include "boruvka.h"

using namespace std;

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
        if (ds.FindSet(i) == set)
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
        set<Edge> e;
//  4   For each component:
        for (component = components.begin(); component != components.end(); ++component) {
            list<int> vertices(listElements(cc, *component));
            list<int>::iterator vertex;
//  5     Begin with an empty set of edges S
            set<Edge> s;
//  6     For each vertex in the component:
            for (vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
//  7       Add the cheapest edge from the vertex in the component to another vertex in a disjoint component to S
                list< pair< int, mpf_class > > neighbour(g.findVertexById(*vertex).get_neighbors());

                for (list< pair< int, mpf_class > >::iterator i = neighbour.begin(); i != neighbour.end(); ++i)
                    if (cc.FindSet(*vertex) == cc.FindSet((*i).first))
                        neighbour.erase(i);

                pair< int, mpf_class > min = *(neighbour.begin());

                for (list< pair< int, mpf_class > >::iterator i = (++neighbour.begin()); i != neighbour.end(); ++i)
                    if ((*i).second < min.second)
                        min = *i;

                Vertex v1 = g.findVertexById(*vertex);
                Vertex v2 = g.findVertexById(min.first);
                s.insert(Edge(v1, v2, min.second));
            }
//  8     Add the cheapest edge in S to E
            Edge min_edge(*(s.begin()));
            set<Edge>::iterator edge;
            for (edge = (++s.begin()); edge != s.end(); ++edge) {
                if (min_edge > (*edge))
                    min_edge = Edge(*edge);
            }
            cc.Union(cc.FindSet((min_edge).getV1().getId()), cc.FindSet((min_edge).getV2().getId()));
            e.insert(min_edge);
        }
//  9   Add the resulting set of edges E to T.
        for (set<Edge>::iterator edge = e.begin(); edge != e.end(); ++edge) {
            t.push_back(*edge);
        }
    }
// 10 The resulting set of edges T is the minimum spanning tree of G.

    return t;
}
