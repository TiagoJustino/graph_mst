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

#define MAX(a, b) (b>a?b:a)

vector<Edge> (*make_mst[])(Graph&) = {kruskal, prim, boruvka, NULL};
vector<Edge> (*make_dcmst[])(Graph&, int) = {kruskal, prim, NULL};
string algorithm[] = {"kruskal", "prim", "boruvka"};

mpf_class weight( vector<Edge>& v ) {
    mpf_class t = 0;
    for(vector<Edge>::iterator i = v.begin(); i != v.end(); ++i) {
        t += i->getCost();
    }
    return t;
}

int getMaxDegree(vector<Edge>& v, int vertices) {
    vector<int> d(vertices, 0);
    int max=0;
    vector<Edge>::iterator i;
    for(i = v.begin(); i != v.end(); ++i) {
        ++d[i->getV1().getId()];
        ++d[i->getV2().getId()];
        max=MAX(max, MAX(d[i->getV1().getId()], d[i->getV2().getId()]));
    }
    return max;
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("Usage: %s file\n", argv[0]);
        return 0;
    }

    puts("{");
    puts("  \"mst\": [");
    for (int i = 0; make_mst[i] != NULL; ++i) {
        puts("    {");
        printf("      \"algorithm\": \"%s\",\n", algorithm[i].c_str());
        clock_t start = clock();
        Graph g = Graph(fopen(argv[1], "r"));
        g.to_dot("ini");
        vector<Edge>v = make_mst[i](g);
        printf("      \"time elapsed\": %lf,\n", ((double)clock() - start) / CLOCKS_PER_SEC);
        printf("      \"weight\": %s\n", Graph::mpfToString(weight(v)).c_str());
        //string str(argv[1]);
        Graph::to_dot(v, (string(argv[1]) + "_" + algorithm[i] + ".dot").c_str());
        printf("    }");
        if (make_mst[i+1] != NULL)
            puts(",");
        else
            puts("");
    }
    puts("  ],");

    puts("  \"dcmst\" : [");
    int max_degree, max_max_degree;
    for(int i = 0; make_dcmst[i]; ++i) {
        Graph g = Graph(fopen(argv[1], "r"));
        vector<Edge>v = make_mst[i](g);
        max_max_degree = getMaxDegree(v, g.order());
        for(max_degree = 2; max_degree <= max_max_degree; ++max_degree) {
            puts("    {");
            printf("      \"algorithm\": \"%s\",\n", algorithm[i].c_str());
            printf("      \"max degree\": %d,\n", max_degree);
            clock_t start = clock();
            Graph g = Graph(fopen(argv[1], "r"));
            vector<Edge>v = make_dcmst[i](g, max_degree);
            printf("      \"time elapsed\": %lf,\n", ((double)clock() - start) / CLOCKS_PER_SEC);
            printf("      \"forest size\": %d,\n", (int)(g.order() - v.size()));
            printf("      \"weight\": %s\n", Graph::mpfToString(weight(v)).c_str());
            Graph::to_dot(v, (algorithm[i] + "dcmst.dot").c_str());
            printf("    }");
            if (make_dcmst[i+1] != NULL or max_degree != max_max_degree)
                puts(",");
            else
                puts("");
        }
    }
    puts("  ]");
    puts("}");

    return 0;
}
