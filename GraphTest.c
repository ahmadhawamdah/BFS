

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
//#include "List.h"


int main() {
    
    Graph A = newGraph(70);
    
   int i, s, max, min, d;

    int n = 35;
    


   List  C = newList(); // central vertices
   List  P = newList(); // peripheral vertices
   List  E = newList(); // eccentricities
   Graph G = NULL;

    //printf("yo am here! \n");

   // Build graph G
   G = newGraph(n);


   addEdge(G, 1, 2);
   addEdge(G, 1, 3);
   addEdge(G, 2, 4);
   addEdge(G, 2, 5);
   addEdge(G, 3, 8);
   addEdge(G, 3, 7);
   addEdge(G, 5, 6);
   addEdge(G, 5, 9);

   // Print adjacency list representation of G
   printGraph(stdout, G);
//printf("yo am here! \n");
   // Calculate the eccentricity of each vertex
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

//    Determine the Radius and Diameter of G, as well as the Central and
//    Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      } else if (d < min){
         min = d;
         clear(C);
         append(C, i);
      }
       
      if( d==max ) {
         append(P, i);
      } else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects

   freeList(&C);
   freeList(&P);

   freeList(&E);

   freeGraph(&G);

   return(0);
}
