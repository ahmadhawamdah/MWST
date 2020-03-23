//-----------------------------------------------------------------------
// Ahmad Hawamdah
// ahawamda
// MWSP.c
// Reads from an input file
//------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include"Graph.h"


int main(int argc, char* argv[]){

    FILE *pIn, *pOut;
    int size, order;
    size = order = 0;

    int end1, end2, weight, label;
     end1 = end2 = weight = label = 1;

  

    // pIn = fopen(argv[1], "r");
    // pOut = fopen(argv[2], "w");

    // Please change the file input name if you're testing your own input file 

    pIn = fopen("in4", "r");
    pOut = fopen("out4", "w");


    
    if (pIn == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    if (pOut == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    
    fscanf(pIn, "%d", &size);
    fscanf(pIn, "%d", &order);

    Graph G = newGraph(order);
    Graph S = newGraph(order);

    for (int i = 1; i <= order ; i++)
    {
        fscanf(pIn, "%d", &end1);
        fscanf(pIn, "%d", &end2);
        fscanf(pIn, "%d", &weight);

        addEdge(G, end1, end2, weight, i);
        weight += weight;
    }
    

    S = Kruskal(G);

    printGraph(pOut, S);

    fclose(pIn);
    fclose(pOut);
    
    return(0);
}

