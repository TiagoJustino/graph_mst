#include <cppunit/extensions/HelperMacros.h>
#include <QtCore>
#include <gmpxx.h>
#include <ctime>
#include "graph.h"
#include "kruskal.h"
#include "prim.h"
#include "boruvka.h"
#include "edge.h"
#include "vertex.h"

#include <stdio.h>

#include <string>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

#define MAX(a, b) (b>a?b:a)

const struct {
    const char *path;
    double cost;
} inputs[] = {
    //{ "input/01_quadrado2009.txt", 32.0 },
    //{ "input/02_DONI22009.txt", 106.407933362449 },
    //{ "input/03_serrinha2009.txt", 15739.05 },
    //{ "input/04_palmeiras2008.txt", 555.15 },
    //{ "input/05_DONI12009.txt", 255.9 },
    //{ "input/06_DONI12009.txt", 345.3186 },
    { "5diamonds.grf", 0.0 },
    { "Euclid301.GRF", 0.0 },
    { "Euclid303.txt", 0.0 },
    { "Euclid306.txt", 0.0 },
    { "P20.GRF", 0.0 },
    { "P22.GRF", 0.0 },
    { "PEARN01.grf", 0.0 },
    { NULL, 0.0 }
};

string outputs[] = {
    //"01_quadrado2009_mst.dot",
    //"02_DONI22009_mst.dot",
    //"03_serrinha2009_mst.dot",
    //"04_palmeiras2008_mst.dot",
    //"05_DONI12009_mst.dot",
    //"06_DONI12009_mst.dot"
    "5diamonds.grf",
    "Euclid301.GRF",
    "Euclid303.txt",
    "Euclid306.txt",
    "P20.GRF",
    "P22.GRF",
    "PEARN01.grf"
};

vector<Edge> (*make_mst[])(Graph&) = {kruskal, prim, boruvka, NULL};
vector<Edge> (*make_dcmst[])(Graph&, int) = {kruskal, prim, NULL};
string algorithm[] = {"kruskal", "prim", "boruvka"};

class GraphMstTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( GraphMstTest );
    //CPPUNIT_TEST( testMst );
    CPPUNIT_TEST( testMstMaxDegree );
    CPPUNIT_TEST_SUITE_END();

private:
    mpf_class weight( vector<Edge>& v ) {
        mpf_class t = 0;
        for(vector<Edge>::iterator i = v.begin(); i != v.end(); ++i) {
            t += (*i).getCost();
        }
        return t;
    }
    Graph getGraph(string path) {
        return Graph(fopen(path.c_str(), "r"));
    }        
    void areSame(double a, double b) {
        CPPUNIT_ASSERT_EQUAL((long long)(10000 * a), (long long)(10000 * b));
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

public:
    void setUp() {}

    void tearDown() {}

    void testMst() {
        for (int i = 0; make_mst[i] != NULL; ++i) {
            printf("Algorithm = [%s]\n", algorithm[i].c_str());
            for (int j = 0; inputs[j].path != NULL; ++j) {
                clock_t start = clock();
                printf("Input [%s]:\n", inputs[j].path);
                Graph g = getGraph(inputs[j].path);
                if(!i) g.to_dot("ini");
                vector<Edge>v = make_mst[i](g);
                printf("    Time elapsed = [%lf], ", ((double)clock() - start) / CLOCKS_PER_SEC);
                printf("Weight = [%s]\n", Graph::mpfToString(weight(v)).c_str());
                Graph::to_dot(v, (algorithm[i] + "_" + outputs[j]).c_str());
                CPPUNIT_ASSERT_EQUAL_MESSAGE(inputs[j].path,
                                             g.order() - 1, (int)v.size());
                areSame(inputs[j].cost, weight(v).get_d());
            }
        }
    }
    void testMstMaxDegree() {
        int max_degree;
        for(int i = 0; make_dcmst[i]; ++i) {
            printf("%s (max degree: 2)\n", algorithm[i].c_str());
            for (int j = 0; inputs[j].path != NULL; ++j) {
                for(max_degree = 2; max_degree <= 2; ++max_degree) {
                    char degree_str[64];
                    clock_t start = clock();
                    printf("Input [%s]:\n", inputs[j].path);
                    Graph g = getGraph(inputs[j].path);
                    vector<Edge>v = make_dcmst[i](g, max_degree);
                    printf("    Time elapsed = [%lf], ", ((double)clock() - start) / CLOCKS_PER_SEC);
                    printf("Forest_size = [%d], ", (int)(g.order() - v.size()));
                    printf("Weight = [%s]\n", Graph::mpfToString(weight(v)).c_str());
                    sprintf(degree_str, "_%d", max_degree);
                    Graph::to_dot(v, (outputs[j] + "_dcmst_" + algorithm[i] + degree_str + ".dot").c_str());
                    CPPUNIT_ASSERT(getMaxDegree(v, g.order()) <= max_degree);
                }
            }
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( GraphMstTest );
