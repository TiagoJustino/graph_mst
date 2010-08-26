#include <gmpxx.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "graph.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "triangle.h"
#ifdef __cplusplus
}
#endif

#define STR_NUM_LEN 64
#define MAX_GRAPH_NAME 512

mpf_class Graph::calculateDistance(Vertex a, Vertex b) {
    mpf_class x = b.getX() - a.getX();
    mpf_class y = b.getY() - a.getY();
    mpf_class d2 = x*x + y*y;
    mpf_class r;
    //printf("[%s][%s]-[%s][%s]\n", mpfToString(a.getX()).c_str(),
           //mpfToString(a.getY()).c_str(), mpfToString(b.getX()).c_str(),
           //mpfToString(b.getY()).c_str());
    //printf("before sqrt=[%s]\n", mpfToString(d2).c_str());
    mpf_sqrt(r.get_mpf_t(), d2.get_mpf_t());
    //printf("after sqrt=[%s]\n", mpfToString(r).c_str());
    return r;
}

void Graph::setGraphFromDelaunay(FILE *f, int n_vertices) {
    //c creates segments on the convex hull of the triangulation
    //D ensure that all the triangles in the mesh are Delaunay
    //j prevents duplicated input vertices
    //e outputs a list of edges of the triangulation
    //z numbers all items starting from zero*
    //S specifies the maximum number of Steiner points to 0
    //C check the consistency of the final mesh
    //Q quiet
    /** Steiner points (vertices that are not in the input, but are added to
     *  meet the constraints on minimum angle and maximum area).
     */
    char *str = (char*)"cDjezSCQ";
    struct triangulateio in, out;
    int i;

    /* triangle will initialize NULL pointers */
    memset(&in, 0, sizeof(struct triangulateio));
    memset(&out, 0, sizeof(struct triangulateio));

    in.numberofpoints = n_vertices;
    in.pointlist  = (REAL*)malloc(2*in.numberofpoints*sizeof(REAL));
    for(i = 0; i < in.numberofpoints; ++i) {
        fscanf(f, "%lf %lf", &in.pointlist[2*i], &in.pointlist[2*i+1]);
    }

    triangulate(str, &in, &out, NULL);

    for(i = 0; i < out.numberofpoints; ++i)
        this->vertices.push_back(Vertex( i, out.pointlist[2*i], out.pointlist[2*i+1]));
    for(i = 0; i < out.numberofedges; ++i) {
        Vertex& a = this->findVertexById(out.edgelist[2*i]);
        Vertex& b = this->findVertexById(out.edgelist[2*i+1]);
        this->edges.push_back(Edge(a, b, calculateDistance(a, b)));
    }
    //TODO: Free input and output structs.
}

Graph::Graph()
{
}

Graph::Graph(FILE *f)
{
    char mp_str[STR_NUM_LEN], _name[MAX_GRAPH_NAME];
    int n_vertices, n_edges, r;
    short int type;
    //TODO: Read graph name
    r = fscanf(f, " %[^\n]s ", _name);
    name = _name;
    r = fscanf(f, " %d %hd %d ", &n_vertices, &type, &n_edges);
    if(type == 1) {
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
    else
        this->setGraphFromDelaunay(f, n_vertices);
    fclose(f);
}

Vertex& Graph::findVertexById(unsigned int id)
{
    return vertices[id];
}

vector<Edge>& Graph::getEdges()
{
    return this->edges;
}

vector<Vertex>& Graph::getVertices()
{
    return this->vertices;
}

int Graph::order()
{
    return this->vertices.size();
}

std::string Graph::mpfToString(mpf_class n)
{
    mp_exp_t exp;
    std::string s = n.get_str(exp);
    if(exp < 0) {
        for(; exp; ++exp) s.insert(0, "0");
        s.insert(0, ".");
    }
    else if((int)exp < (int)s.size()) s.insert(exp, ".");
    else for(int n = s.size(); n < exp; n++) s += "0";
    return s;
}

void Graph::to_dot(vector<Edge> edges, FILE *f)
{
    for(vector<Edge>::iterator i = edges.begin(); i < edges.end(); ++i) 
        fprintf(f, "\"%d\" -- \"%d\" [label=\"%s\"]\n", i->getV1().getId() + 1,
                i->getV2().getId() + 1, mpfToString(i->getCost()).c_str());
}

void Graph::to_dot(vector<Edge> edges, const char *path)
{
    FILE *f = fopen(path, "w");
    fprintf(f, "graph {\n");
    to_dot(edges, f);
    fprintf(f, "}");
    fclose(f);
}

void Graph::to_dot(const std::string sufix)
{
    to_dot(this->edges, (this->name + "_" + sufix + ".dot").c_str());
}
