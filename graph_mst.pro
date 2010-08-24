######################################################################
# Automatically generated by qmake (2.01a) Fri Aug 20 11:39:24 2010
######################################################################

TEMPLATE = app
TARGET = graph_mst_test
DEPENDPATH += .
INCLUDEPATH += .
LIBS += -lgmpxx `cppunit-config --libs`
QMAKE_CXXFLAGS += -Werror
CONFIG -= release
CONFIG += debug

# Input
HEADERS += edge.h graph.h kruskal.h vertex.h disjoint_sets.h prim.h \
           binary_heap.h
SOURCES += edge.cpp graph.cpp kruskal.cpp vertex.cpp disjoint_sets.cpp \
           prim.cpp binary_heap_test.cpp
SOURCES += kruskal_test.cpp
SOURCES += main_test.cpp
