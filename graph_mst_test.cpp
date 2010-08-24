#include <cppunit/extensions/HelperMacros.h>
#include <QtCore>
#include <gmpxx.h>
#include "graph.h"
#include "kruskal.h"
#include "prim.h"
#include "edge.h"
#include "vertex.h"

#include <stdio.h>

#include <string>
#include <vector>
using namespace std;

const struct {
    const char *path;
    double cost;
} inputs[] = {
    { "input/01_quadrado2009.txt", 32.0 },
//  {"input/02_DONI22009.txt", COST },
    { "input/03_serrinha2009.txt", 15739.05 },
    { "input/04_palmeiras2008.txt", 555.15 },
//  { "input/05_DONI12009.txt", COST },
    { NULL, 0.0 }
};

vector<Edge> (*make_mst[])(Graph&) = {kruskal, prim, NULL};

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

public:
    void setUp() {}

    void tearDown() {}

    void testMst() {
        for (int i = 0; make_mst[i] != NULL; ++i) {
            for (int j = 0; inputs[j].path != NULL; ++j) {
                Graph g = getGraph(inputs[j].path);
                vector<Edge>v = make_mst[i](g);
                //Graph::to_dot(v, "graph.dot");
                CPPUNIT_ASSERT_EQUAL( g.order() - 1, (int)v.size() );
                CPPUNIT_ASSERT_EQUAL( inputs[j].cost, weight(v).get_d() );
            }
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( GraphMstTest );
