

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj {
    List *adjL;
    int *p; // parent
    int *col; // color
    int *dist; // distance
    int size;
    int order;
    int s; // source
    
} GraphObj;

Graph newGraph (int n) {
    
      
    Graph G = malloc(sizeof(GraphObj));
    G->adjL = malloc((n+1) * sizeof(List));
    G->p = malloc((n+1) * sizeof(int));
    G->col = malloc((n+1) * sizeof(int));
    G->dist = malloc((n+1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->s = NIL;
    
    for (int ind = 1; ind <= n; ind++) {
        G->adjL[ind] = newList();
        G->col[ind] = WHITE;
        G->dist[ind] = INF;
        G->p[ind] = NIL;
    }
    return(G);
}


void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
    for (int ind = 0; ind < getOrder(*pG); ind++) {
        freeList(&((*pG))->adjL[ind]); // free List
    }
        
        free((*pG)->adjL);
        free((*pG)->col);
        free((*pG)->dist);
        free((*pG)->p);
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


int getSource(Graph G) {
    return (G->s);
}

int getParent(Graph G, int u) {
    if (G==NULL) {
        exit(1);
    }
    
    if (u < 1 || u > G->order) {
      printf("Graph Error: calling addEdge() on vertices u exceeded boundris\n");
      exit(1);
      }
    
    return (G->p[u]);
}


int getDist(Graph G, int u) {
    return (G->dist[u]);
}



void addEdge(Graph G, int u, int v) {

    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
      
}
        

void addArc(Graph G, int u, int v) {
    
    if (u < 1 || u > G->order) {
    printf("Graph Error: calling addArc() on vertices u exceeded boundris\n");
    exit(1);
    }
    
    if (v < 1 || v > G->order) {
      printf("Graph Error: calling addArc() on vertices v exceeded boundris\n");
      exit(1);
    }
    
     List adjL1 = G->adjL[u];

    if(length(adjL1) == 0){
        append(adjL1, v);
        G->size++;
    } else {
        moveFront(adjL1);
        while(get(adjL1) < v) {
             moveNext(adjL1);
             if(index(adjL1) == -1)
                 break;
         }

         if (index(adjL1) == -1) { // check NULL status
             append(adjL1, v);
             G->size++;
         } else {
             insertBefore(adjL1, v);
             G->size++;
        }
    }
}
    
void printGraph(FILE* out, Graph G) {
    if( G==NULL ) {
       printf("Graph Error: calling printGraph() on NULL Graph reference\n");
       exit(1);
    }
    
     for (int ind = 1; ind <= getOrder(G); ind++) {
         List L = G->adjL[ind];
         if (length(L) != 0) {
             moveFront(L);
             int v = get(L);
             fprintf(out, "\n%d: ", ind);
             while (index(L) > -1){
                 v = get(L);
                 fprintf(out, "%d ", v);
                 moveNext(L);
             }
         }else{
             fprintf(out,"\n%d: ", ind);
         }
    }
}


void getPath(List L, Graph G, int u) {
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getParent() with a invalid vertex\n");
        exit(1);
    }
    
    if (getSource(G) == u) {
        append(L, u); // prepend?
    } else if (getParent(G,u) == NIL) {
        append(L , NIL);
    } else {
        
        getPath(L,G, getParent(G,u));
        append(L,u);
    }
}


void BFS(Graph G, int s) {
    
    for (int ind = 1; ind <= getOrder(G); ind++) {
        G->col[ind] = WHITE;
        G->dist[ind] = INF;
        G->p[ind] = NIL;
    }
    
    int x, y;
    x = y = 0;
    
    G->s = s;
    G->col[s] = GRAY;
    G->dist[s] = 0;
    G->p[s] = NIL;
    
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        int x = front(Q);
        deleteFront(Q);
        
        List L = G->adjL[x];
        moveFront(L);
        while(index(L) > -1) {
            int y = get(L);
            if(G->col[y] == WHITE) {
                G->col[y] = GRAY;
                G->dist[y] = G->dist[x] + 1;
                G->p[y] = x;
                append(Q, y);
            }
            moveNext(L);
        }
        G->col[x] = BLACK;
    }
    freeList(&Q);
}

