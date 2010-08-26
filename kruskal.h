#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"
#include "edge.h"
#include <vector>

vector<Edge> kruskal(Graph& g);
vector<Edge> kruskal(Graph& g, int max_degree);

#endif // KRUSKAL_H
