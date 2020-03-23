#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include"Graph.h"


int main(int argc, char* argv[]){

    FILE *pIn, *pOut;
    int size = 0;
    
    //Graph source and distance
    int gSrc, gDist;
    gSrc = gDist = 1;
    
    //BFS source and distance
    int BFSsrc, BFSdist;
    BFSsrc = BFSdist = 1;

    pIn = fopen(argv[1], "r");
    pOut = fopen(argv[2], "w");

    
    if (pIn == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    if (pOut == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    
    fscanf(pIn, "%d", &size);
    int n = size + 1;
    Graph G = newGraph(n);
      
    
    while(gSrc != 0) {
        
        
        fscanf(pIn, "%d", &gSrc);
        fscanf(pIn, "%d", &gDist);
        
        if(gDist == 0 && gSrc == 0)
            break;
        
        addEdge(G, gSrc, gDist);
    }
    
    printGraph(pOut, G);
    fprintf(pOut, "\n\n");
    
   while (BFSsrc != 0) {
    
           fscanf(pIn, "%d", &BFSsrc);
           fscanf(pIn, "%d", &BFSdist);
    
    
           if (BFSdist == 0 && BFSsrc == 0) {
               break;
           }
    
           List path = newList();
           BFS(G, BFSsrc);
           getPath(path, G, BFSdist);
    
    
         if (getDist(G, BFSdist) != INF) {
             fprintf(pOut, "The distance from %d to %d is %d\n", BFSsrc,
             BFSdist, length(path) - 1);
             fprintf(pOut, "A shortest %d-%d path is: ", BFSsrc, BFSdist);
             printList(pOut, path);
             fprintf(pOut, "\n\n");
    
    
         } else {
             fprintf(pOut, "The distance from %d to %d is infinity\n", BFSsrc, BFSdist);
             fprintf(pOut, "No %d-%d path exists\n\n", BFSsrc, BFSdist);
         }
           freeList(&path);
       }

    
    //freeGraph(&G);
    fclose(pIn);
    fclose(pOut);
    
    return(0);
}

