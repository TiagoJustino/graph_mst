######################################################################
# Automatically generated by qmake (2.01a) Fri Aug 20 11:39:24 2010
######################################################################

TEMPLATE = app
TARGET = graph_mst_test
DEPENDPATH += .
INCLUDEPATH += .
LIBS += -lgmpxx `cppunit-config --libs`
QMAKE_CFLAGS += -Werror
QMAKE_CXXFLAGS += -Werror
CONFIG -= release
CONFIG += debug
QMAKE_CFLAGS_DEBUG -= -g
QMAKE_CFLAGS_DEBUG += -g3 -O0 -Werror -DTRILIBRARY -DANSI_DECLARATORS
QMAKE_CXXFLAGS_DEBUG -= -g
QMAKE_CXXFLAGS_DEBUG += -g3 -O0 -Werror

# Input
HEADERS += edge.h graph.h kruskal.h vertex.h disjoint_sets.h prim.h \
           binary_heap.h triangle.h boruvka.h
SOURCES += edge.cpp graph.cpp kruskal.cpp vertex.cpp disjoint_sets.cpp \
           prim.cpp graph_mst_test.cpp main_test.cpp triangle.c boruvka.cpp
