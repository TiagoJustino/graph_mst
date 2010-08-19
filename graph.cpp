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
        mpz_class id, x, y;
        fin >> mpz_str; id = mpz_str.toStdString();
        fin >> mpz_str; x = mpz_str.toStdString();
        fin >> mpz_str; y = mpz_str.toStdString();
        this->vertices.append(Vertex(id, x, y));
    }
    if (type == 1) {
        for (mpz_class i(0); i < no_edges; ++i) {
            QString v1, v2;
            fin >> v1;
            fin >> v2;
            fin >> mpz_str;
            mpz_class cost(mpz_str.toStdString());
            Edge edge(this->findVertexById(mpz_class(v1.toStdString())),
                      this->findVertexById(mpz_class(v2.toStdString())),
                      cost);
            this->edges.append(edge);
        }
    }
    f->close();
}

Vertex Graph::findVertexById(mpz_class id)
{
    foreach(Vertex v, this->vertices) {
        if (v.getId() == id)
            return v;
    }
}
