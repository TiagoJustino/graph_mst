#include <QtCore>
#include <gmpxx.h>
#include "graph.h"

#include <iostream>

#define STR_NUM_LEN 64

Graph::Graph()
{
    /*
    this->vertices = new QSet<Vertex>();
    this->edges = new QSet<Edge>();
    */
}

Graph::Graph(FILE *f)
{
    char mp_str[STR_NUM_LEN];
    int n_vertices, n_edges, r;
    short int type;
    //TODO: Read graph name
    r = fscanf(f, " %*s ");
    r = fscanf(f, " %d %hd %d ", &n_vertices, &type, &n_edges);
    for (int i = 0; i < n_vertices; ++i) {
        r = fscanf(f, " %*s "); //TODO: Read node name
        r = fscanf(f, " %s ", mp_str);
        for(char *c = mp_str; *c; ++c) if(*c == ',') *c = '.';
        mpf_class x(mp_str);
        r = fscanf(f, " %s ", mp_str);
        mpf_class y(mp_str);
        for(char *c = mp_str; *c; ++c) if(*c == ',') *c = '.';
        this->vertices.push_back(Vertex(i, x, y));
    }
    if (type == 1) {
        for (mpz_class i(0); i < n_edges ; ++i) {
            int v1, v2;
            if(fscanf(f, " %d %d %s ", &v1, &v2, mp_str) != 3) break;
            for(char *c = mp_str; *c; ++c) if(*c == ',') *c = '.';
            mpf_class cost(mp_str);
            Edge edge(this->findVertexById(v1 - 1),
                      this->findVertexById(v2 - 1),
                      cost);
            this->edges.push_back(edge);
        }
    }
    fclose(f);
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

vector<Edge>& Graph::getEdges()
{
    return this->edges;
}

int Graph::order()
{
    return this->vertices.size();
}

void Graph::to_dot(vector<Edge>& edges, FILE *f)
{
    mp_exp_t exp;
    std::string s;
    for(vector<Edge>::iterator i = edges.begin(); i != edges.end(); ++i) {
        s = i->getCost().get_str(exp);
        if((int)exp < (int)s.size()) s.insert(exp, ".");
        else for(int n = s.size(); n < exp; n++) s += "0";
        fprintf(f, "\"%d\" -- \"%d\" [label=\"%s\"]\n", i->getV1().getId() + 1,
                i->getV2().getId() + 1, s.c_str());
    }
}

void Graph::to_dot(vector<Edge>& edges, const char *path)
{
    FILE *f = fopen(path, "w");
    fprintf(f, "graph {\nrankdir=LR\n");
    to_dot(edges, f);
    fprintf(f, "}");
    fclose(f);
}
