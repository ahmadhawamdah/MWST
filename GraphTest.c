
//-----------------------------------------------------------------------
// Ahmad Hawamdah
// ahawamda
// GraphTest.c
// Graph client file for testing purposes
//------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
//#include "List.h"

int main()
{

    Graph G = newGraph(50);


    // addEdge parameters represent
    // Source, Desttnation, Weight, and Label

    addEdge(G, 1, 2, 6, 1);
    addEdge(G, 1, 4, 3, 2);
    addEdge(G, 2, 3, 5, 3);
    addEdge(G, 2, 5, 8, 4);
    addEdge(G, 3, 5, 1, 5);
    addEdge(G, 3, 7, 4, 6);
    addEdge(G, 4, 5, 7, 7);
    addEdge(G, 4, 6, 9, 8);
    addEdge(G, 5, 6, 6, 9);
    addEdge(G, 5, 7, 5, 10);
    addEdge(G, 6, 7, 2, 11);

    Kruskal(G);

    printGraph(stdout, G);
    // Free objects
    freeGraph(&G);

    return (0);
}

