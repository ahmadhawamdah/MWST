
#ifndef GRAPH_H
#define GRAPH_H
#include "List.h"

#define NIL 0
#define UNDEF -1


typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);

/*** Manipulation procedures ***/

Graph SortWeights(Graph G);
void addEdge(Graph G, int u, int v, double w, int label);
void addArc(Graph G, int u, int v, double w, int label);
Graph Kruskal (Graph G);

/*** Other operations ***/
void printGraph(FILE* out, Graph S);

#endif
