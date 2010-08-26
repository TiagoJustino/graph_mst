#ifndef PRIM_H
#define PRIM_H

#include "graph.h"
#include "edge.h"
#include <vector>

vector<Edge> prim(Graph& g);
vector<Edge> prim(Graph& g, int max_degree);

#endif // PRIM_H
