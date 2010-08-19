#include <QtCore>
#include <gmpxx.h>
#include "graph.h"

#include <iostream>

Graph::Graph()
{
    /*
    this->vertices = new QSet<Vertex>();
    this->edges = new QSet<Edge>();
    */
}

Graph::Graph(QFile *f)
{
    QString mpz_str;
    mpz_class no_vertices, no_edges;
    short int type;
    f->open(QIODevice::ReadOnly);
    QTextStream fin(f);
    fin >> this->name;
    fin >> mpz_str; no_vertices = mpz_str.toStdString();
    fin >> type;
    fin >> mpz_str; no_edges = mpz_str.toStdString();
    for (mpz_class i(0); i < no_vertices; ++i) {
        int id;
        mpz_class x, y;
        fin >> id;
        fin >> mpz_str; x = mpz_str.toStdString();
        fin >> mpz_str; y = mpz_str.toStdString();
        this->vertices.push_back(Vertex(id, x, y));
    }
    if (type == 1) {
        for (mpz_class i(0); i < no_edges; ++i) {
            int v1, v2;
            fin >> v1;
            fin >> v2;
            fin >> mpz_str;
            mpz_class cost(mpz_str.toStdString());
            Edge edge(this->findVertexById(v1),
                      this->findVertexById(v2),
                      cost);
            this->edges.push_back(edge);
        }
    }
    f->close();
}

Vertex Graph::findVertexById(int id)
{
    Vertex not_found(-1, 0, 0);
    foreach(Vertex v, this->vertices) {
        if (v.getId() == id)
            return v;
    }
    return not_found; 
}

vector<Edge> Graph::getEdges()
{
    return this->edges;
}

int Graph::order()
{
    return this->vertices.size();
}
