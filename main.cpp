#include <QtCore>
#include "graph.h"
#include "kruskal.h"

int main()
{
  QFile *f = new QFile("input/01_quadrado2009.txt");
  Graph g = Graph(f);
  kruskal(g);
  return 0;
}
