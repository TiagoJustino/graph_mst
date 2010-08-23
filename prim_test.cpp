#include <cppunit/extensions/HelperMacros.h>
#include <QtCore>
#include <gmpxx.h>
#include <vector>
#include "graph.h"
#include "prim.h"
#include "edge.h"
#include "vertex.h"

using std::vector;

class PrimTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( PrimTest );
    CPPUNIT_TEST( test );
    CPPUNIT_TEST_SUITE_END();
    private:
        mpf_class weight( vector<Edge>& v )
        {
            mpf_class t = 0;
            for(vector<Edge>::iterator i = v.begin(); i != v.end(); ++i) {
                t += (*i).getCost();
            }
            return t;
        }
        void internal_test(FILE* f, size_t s, double w)
        {
            Graph g = Graph(f);
            vector<Edge>v = prim(g);
            Graph::to_dot(v, "graph.dot");

            CPPUNIT_ASSERT_EQUAL( s,  v.size() );
            CPPUNIT_ASSERT_EQUAL( w, weight(v).get_d() );
        }
    public:
        void setUp()
        {
        }

        void tearDown() 
        {
        }

        void test()
        {
            internal_test(fopen("input/01_quadrado2009.txt", "r"), (size_t)8, 32);
            internal_test(fopen("input/03_serrinha2009.txt", "r"), (size_t)219, 15739.05);
            internal_test(fopen("input/04_palmeiras2008.txt", "r"), (size_t)271, 555.15);
        }
};

CPPUNIT_TEST_SUITE_REGISTRATION( PrimTest );
