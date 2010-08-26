#include "graph.h"
#include <gmpxx.h>
#include <ctime>
#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include "kruskal.h"
#include "prim.h"
#include "boruvka.h"
#include "edge.h"
#include "vertex.h"

using std::string;

vector<Edge> (*make_mst[])(Graph&) = {kruskal, prim, boruvka, NULL};
string algorithm[] = {"kruskal", "prim", "boruvka"};

mpf_class weight( vector<Edge>& v ) {
    mpf_class t = 0;
    for(vector<Edge>::iterator i = v.begin(); i != v.end(); ++i) {
        t += i->getCost();
    }
    return t;
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("Usage: %s file\n", argv[0]);
        return 0;
    }

    printf("File: %s\n", argv[1]);
    for (int i = 0; make_mst[i] != NULL; ++i) {
        printf("Algorithm = [%s]\n", algorithm[i].c_str());
        clock_t start = clock();
        Graph g = Graph(fopen(argv[1], "r"));
        g.to_dot("ini");
        vector<Edge>v = make_mst[i](g);
        printf("    Time elapsed = [%lf], ", ((double)clock() - start) / CLOCKS_PER_SEC);
        printf("Weight = [%s]\n", Graph::mpfToString(weight(v)).c_str());
        //string str(argv[1]);
        Graph::to_dot(v, (string(argv[1]) + "_" + algorithm[i] + ".dot").c_str());
    }        

    return 0;
}
