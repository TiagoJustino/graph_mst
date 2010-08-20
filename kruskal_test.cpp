#include <cppunit/extensions/HelperMacros.h>
#include <QtCore>
#include <gmpxx.h>
#include <vector>
#include "graph.h"
#include "kruskal.h"
#include "edge.h"
#include "vertex.h"

using std::vector;

class KruskalTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( KruskalTest );
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
        void internal_test(QString file, size_t s, mpf_class w) 
        {
            QFile *f = new QFile(file);
            Graph g = Graph(f);
            vector<Edge>v = kruskal(g);

            CPPUNIT_ASSERT_EQUAL( s,  v.size() );
            CPPUNIT_ASSERT_EQUAL( w, weight(v) );
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
            internal_test(QString("input/01_quadrado2009.txt"), (size_t)8,
                          (mpf_class)32);
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION( KruskalTest );
