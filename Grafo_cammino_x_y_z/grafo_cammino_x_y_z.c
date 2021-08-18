#include <stdio.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1
// SEMBRA CHE VADA BENE (ho fatto i test in modo autonomo)
/*
      Stabilire se il nodo y si trova su un cammino che va da x a z.
*/
typedef struct _edges
{
      int degree;
      int *adj;
} edges;

typedef edges* graph;

graph read_graph(int N)
{
      graph G = (graph) malloc(sizeof(edges) * N);

      for(int i = 0; i < N; i++)
      {
            scanf("%d", &G[i].degree);
            G[i].adj = (int*) malloc(sizeof(int) * G[i].degree);
            for(int j = 0; j < G[i].degree; j++)
                  scanf("%d", &G[i].adj[j]);        
      }
      return G;
}

void dfs_path(graph G, int src, int b, int *colours)
{
      colours[src] = GRAY;

      int dest;
      for(int i = 0; i < G[src].degree; i++) // for all v ∈ Adj[u]
      {
            dest = G[src].adj[i];

            if(colours[dest] == WHITE)
                  if(dest == b) // trovato b
                  {
                        colours[dest] = GRAY;
                        return ; 
                  }
                  else
                        dfs_path(G, dest, b, colours);
      }
}

int path_x_y_z(graph G, int N, int src, int x, int y, int z)
{     
      int *colours = malloc(N * sizeof(int));

      for(int i = 0; i < N; i++) 
            colours[i] = WHITE;
      
      dfs_path(G, x, y, colours);

      if(colours[y] == WHITE)
      {
            free(colours);
            return 0;
      }

      for(int i = 0; i < N; i++)
            colours[i] = WHITE;
      
      dfs_path(G, y, z, colours);

      if(colours[z] == WHITE)
      {
            free(colours);
            return 0;
      }
      
      free(colours);
      return 1;
}

void delete_graph(graph G, int N)
{
      for(int i = 0; i < N; i++)
            free(G[i].adj);
      free(G);
}

int main()
{
      int N;
      graph G;

      scanf("%d", &N);

      G = read_graph(N);

      int x, y, z;
      printf("x: ");
      scanf("%d", &x);
      printf("y: ");
      scanf("%d", &y);
      printf("z: ");
      scanf("%d", &z);

      if(path_x_y_z(G, N, 0, x, y, z) == 1)
            printf("Esiste un cammino da [%d] a [%d] passante per [%d]\n", x, z, y);
      else
            printf("NON Esiste un cammino da [%d] a [%d] passante per [%d]\n", x, z, y);

      delete_graph(G, N);
      return 0;
}

/*
INPUT
      6
      1 1
      1 2
      1 3
      2 2 5
      1 3
      0
      x: ..
      y: ..
      z: ..
*/