#include <cppunit/extensions/HelperMacros.h>
#include "binary_heap.h"

class BinaryHeapTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( BinaryHeapTest );
    CPPUNIT_TEST( preliminaryTest );
    CPPUNIT_TEST( test );
    CPPUNIT_TEST_SUITE_END();
    private:
    public:
        class Element {
            int v;
            public:
                Element(int _v): v(_v) {};
                bool operator<(const Element& e) const { return this->v < e.v; };
                int getValue() { return this->v; };
        };

        void setUp()
        {
        }

        void tearDown() 
        {
        }

        void preliminaryTest()
        {
            Element a(4), b(9), c(15);
            CPPUNIT_ASSERT( a < b );
            CPPUNIT_ASSERT( a < c );
            CPPUNIT_ASSERT( b < c );
            CPPUNIT_ASSERT_ASSERTION_FAIL( CPPUNIT_ASSERT( a < a ) );
            CPPUNIT_ASSERT_ASSERTION_FAIL( CPPUNIT_ASSERT( b < b ) );
            CPPUNIT_ASSERT_ASSERTION_FAIL( CPPUNIT_ASSERT( c < c ) );
            CPPUNIT_ASSERT_ASSERTION_FAIL( CPPUNIT_ASSERT( b < a ) );
            CPPUNIT_ASSERT_ASSERTION_FAIL( CPPUNIT_ASSERT( c < a ) );
            CPPUNIT_ASSERT_ASSERTION_FAIL( CPPUNIT_ASSERT( c < b ) );
        }

        void test()
        {
            Element a(4), b(9), c(15);
            BinaryHeap<Element> heap;
            /* push_back empty pop update insert */
            CPPUNIT_ASSERT_EQUAL( 0, heap.size() );
            CPPUNIT_ASSERT_EQUAL( true, heap.empty() );
            heap.insert(b);
            CPPUNIT_ASSERT_EQUAL( 1, heap.size() );
            CPPUNIT_ASSERT_EQUAL( false, heap.empty() );
            CPPUNIT_ASSERT_EQUAL( 9, heap.getMin().getValue() );
            CPPUNIT_ASSERT_EQUAL( 1, heap.size() );
            CPPUNIT_ASSERT_EQUAL( false, heap.empty() );
            CPPUNIT_ASSERT_EQUAL( 9, heap.pop().getValue() );
            CPPUNIT_ASSERT_EQUAL( 0, heap.size() );
            CPPUNIT_ASSERT_EQUAL( true, heap.empty() );
        }
};

CPPUNIT_TEST_SUITE_REGISTRATION( BinaryHeapTest );
