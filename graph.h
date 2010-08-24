#ifndef GRAPH_H
#define GRAPH_H

#include <QtCore>
#include <gmpxx.h>
#include <vector>
#include <string>
#include "vertex.h"
#include "edge.h"

using std::vector;

class Graph
{
private:
    //Attributes:
    QString name;
    vector<Vertex> vertices;
    vector<Edge> edges;

    //Methods:
    void setGraphFromDelaunay(FILE *f, int n_vertices);
    static void to_dot(vector<Edge> edges, FILE *f);
    static mpf_class calculateDistance(Vertex a, Vertex b);

public:
    Graph();
    Graph(FILE *f);
    void addVertex(Vertex v);
    void addEdge(Edge e);
    Vertex& findVertexById(unsigned int id);
    vector<Edge>& getEdges();
    int order();

    static void to_dot(vector<Edge> edges, const char *path);
    static std::string mpfToString(mpf_class n);
};

#endif // GRAPH_H
