#ifndef GRAPH_H
#define GRAPH_H

#include <QtCore>
#include <gmpxx.h>
#include <vector>
#include "vertex.h"
#include "edge.h"

using std::vector;

class Graph
{
private:
    static Vertex not_found;

    QString name;
    vector<Vertex> vertices;
    vector<Edge> edges;
    static void to_dot(vector<Edge>& edges, FILE *f);

public:
    Graph();
    Graph(FILE *f);
    void addVertex(Vertex v);
    void addEdge(Edge e);
    Vertex& findVertexById(unsigned int id);
    vector<Edge>& getEdges();
    int order();

    static void to_dot(vector<Edge>& edges, const char *path);
};

#endif // GRAPH_H
