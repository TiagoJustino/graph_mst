#include <cppunit/extensions/HelperMacros.h>
#include <QtCore>
#include <gmpxx.h>
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

const struct {
    const char *path;
    double cost;
} inputs[] = {
    { "input/01_quadrado2009.txt", 32.0 },
    { "input/02_DONI22009.txt", 106.407933362449 },
    { "input/03_serrinha2009.txt", 15739.05 },
    { "input/04_palmeiras2008.txt", 555.15 },
    { "input/05_DONI12009.txt", 255.9 },
    { NULL, 0.0 }
};

vector<Edge> (*make_mst[])(Graph&) = {kruskal, prim, boruvka, NULL};
const char* algorithm[] = {"kruskal", "prim", "boruvka"};

class GraphMstTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( GraphMstTest );
    CPPUNIT_TEST( testMst );
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

public:
    void setUp() {}

    void tearDown() {}

    void testMst() {
        for (int i = 0; make_mst[i] != NULL; ++i) {
            printf("Algorithm = [%s]\n", algorithm[i]);
            for (int j = 0; inputs[j].path != NULL; ++j) {
                printf("Input = [%s]\n", inputs[j].path);
                Graph g = getGraph(inputs[j].path);
                vector<Edge>v = make_mst[i](g);
                Graph::to_dot(v, "graph.dot");
                CPPUNIT_ASSERT_EQUAL_MESSAGE(inputs[j].path,
                                             g.order() - 1, (int)v.size());
                areSame(inputs[j].cost, weight(v).get_d());
                // For some reason i got the following error when comparing double:
                // equality assertion failed
                // - Expected: 106.407933362449
                // - Actual  : 106.407933362449
                // And with cast fo float i get:
                // - Expected: 255.9
                // - Actual  : 255.9
                // - input/05_DONI12009.txt
                // WTF !!!!!!!!
            }
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( GraphMstTest );
