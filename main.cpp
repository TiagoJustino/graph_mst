#include <QtCore>
#include "graph.h"

int main(int argc, char *argv[])
{
  QFile *f = new QFile("input/01_quadrado2009.txt");
  Graph *g = new Graph(f);
  return 0;
}
