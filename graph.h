#ifndef GRAPH_H
#define GRAPH_H

#include <QtCore>
#include <gmpxx.h>
#include "vertex.h"
#include "edge.h"

class Graph
{
private:
    QString name;
    QList<Vertex> vertices;
    QList<Edge> edges;

public:
    Graph();
    Graph(QFile *f);
    void addVertex(Vertex v);
    void addEdge(Edge e);
    Vertex findVertexById(mpz_class id);
};

#endif // GRAPH_H
