//-----------------------------------------------------------------------
// Ahmad Hawamdah
// ahawamda
// Graph.c
// Implementation file for the Graph
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


typedef struct GraphObj {
    List *adjL; 
    int size;
    int order;


} GraphObj;


typedef struct EntryObj{
    int end1;
    int end2;
    double weight;
    int label;
} EntryObj;

typedef struct EntryObj* Entry;

struct minGraph {
    int p; // parent
    int rank; 
};

Entry newEntry(int e1, int e2, double w, int label) {
    Entry E;
    E = malloc(sizeof(EntryObj));
    E->end1 = e2;
    E->end2 = e1;
    E->weight = w;
    E->label = label;
    return(E);
}



Graph newGraph (int n) {
    
      
    Graph G = malloc(sizeof(GraphObj));
    G->adjL = malloc((n+1) * sizeof(List));
    G->order = n;
    G->size = 0;

    
    for (int ind = 0; ind <= getOrder(G); ind++) {
           G->adjL[ind] = newList();

       }
    
    return(G);
}


void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
    for (int ind = 0; ind < getOrder(*pG); ind++) {
        freeList(&((*pG))->adjL[ind]); // free List
    }
        
        free((*pG)->adjL);
        free(*pG); // free matrix
        *pG = NULL;
    }
}



int getOrder(Graph G) { 
    return (G->order);
}

int getSize(Graph G) {
    return (G->size);
}

void addEdge(Graph G, int u, int v, double w, int entry) {

    addArc(G, u, v, w, entry);
    addArc(G, v, u, w, entry);
    G->size--;
      
}
        

void addArc(Graph G, int u, int v, double w, int entry) {
    
    if (u < 1 || u > G->order) {
    printf("Graph Error: calling addArc() on vertices u exceeded boundris\n");
    exit(1);
    }
    
    if (v < 1 || v > G->order) {
      printf("Graph Error: calling addArc() on vertices v exceeded boundris\n");
      exit(1);
    }
    
    

    List adjL1 = G->adjL[u];
    Entry E = newEntry(u, v, w, entry);
    Entry E1 = NULL;

    if(length(adjL1) == 0){
        E->end1 = u;
        E->end2 = v;
        E->weight = w;
        append(adjL1, E);
        G->size++;
        
    } else { 
        moveFront(adjL1);
        E1 = (Entry)get(adjL1);
        while(E1->end1 < v) {
            moveNext(adjL1);
            if(index(adjL1) == -1)
                break;
         }

         if (index(adjL1) == -1) { // check NULL status
            E->end1 = u;
            E->end2 = v;
            E->weight = w;
            append(adjL1, E);
            G->size++;
         } else {
            E->end1 = u;
            E->end2 = v;
            E->weight = w;
            insertBefore(adjL1, E);
            G->size++;
        }
    }
}




void printGraph(FILE* out, Graph G) {
    if( G==NULL ) {
       printf("Graph Error: calling printGraph() on NULL Graph reference\n");
       exit(1);
    }
    double sum = 0.0;
    List listOfWeights = newList();
    for (int n = 1; n < G->order; n++){
        List adjList = G->adjL[n];
        moveFront(adjList);
        while(index(adjList) != -1){
            Entry e = get(adjList);
            if(e->end1 > e->end2) {
                sum = sum + e->weight;
                fprintf(out, "% 4i: (%d, %d) %.1lf\n",e->label, e->end1, e->end2, e->weight);
                append(listOfWeights, e);
            }
            moveNext(adjList);
        }
    }
    fprintf(out, "Total Weight = %.02lf\n", sum);
}

Graph Kruskal (Graph G){

    // Taking the nodes from and adjaceny list of lists and putting them in one list
    Graph N = newGraph(getOrder(G));
    List listOfWeights = newList();
    for (int n = 1; n < G->order; n++){
        List adjList = G->adjL[n];
        moveFront(adjList);
        while(index(adjList) != -1){
            Entry e = get(adjList);
            if(e->end1 > e->end2){
                append(listOfWeights, e);
            }
            moveNext(adjList);
        }
    }


    // Sorting the adjacency list by weight in an increasing order
    Entry e;
    List copyL = copyList(listOfWeights);
    List returnL = newList();
    while(length(copyL) != 0){
        moveFront(copyL);
        int pos = 0;
        e = get(copyL);
        while(index(copyL) != -1){
            if(e->weight > ((Entry) get(copyL))->weight){
                e = get(copyL);
                pos = index(copyL);
            }
            moveNext(copyL);
        }
        append(returnL, e);
        moveFront(copyL);
        for(int i = 0; i < pos; i++){
            moveNext(copyL);
        }
        delete(copyL);
    }

    // Detecting Cycles and adding Edges accordingly 
    moveFront(returnL);
    while(index(returnL) != -1){
        moveNext(returnL);
    }
    int arr[100000];
    for(int i = 0; i < 100000; i++){
        arr[i] = 0;
    }
    moveFront(returnL);
    int start = 1;
    while(index(returnL)!= -1){
        e = get(returnL);
        int v1 = e->end1;
        int v2 = e->end2;
        if(start == 1){
            addEdge(N, v1, v2, e->weight, e->label);
            // fprintf(stdout, "%d: (%d, %d) %d\n",e->label, v1, v2, e->weight);
            arr[v2] = 1;
            arr[v1] = 1;
            delete(returnL);
            moveFront(returnL);
            start = 0;
        }
        else if(arr[v1] == 1 && arr[v2] == 0){
            addEdge(N, v1, v2, e->weight, e->label);
            // fprintf(stdout, "%d: (%d, %d) %d\n",e->label, v1, v2, e->weight);
            arr[v2] = 1;
            delete(returnL);
            moveFront(returnL);
        } else if(arr[v1] == 0 && arr[v2] == 1){
            addEdge(N, v1, v2, e->weight, e->label);
            // fprintf(stdout,"%d: (%d, %d) %d\n",e->label, v1, v2, e->weight);
            arr[v1] = 1;
            delete(returnL);
            moveFront(returnL);
        } else{
            moveNext(returnL);
        }
    }
    return N;
}

