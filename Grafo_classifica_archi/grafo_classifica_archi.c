#include <stdio.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1
// PENSO VADA BENE (non ho fatto abbastanza test ma sono confident)
/*
      Classificare gli archi di un grafo indiretto.
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

void dfs_visit_classification(graph G, int src, int *colours, int *pi)
{
      colours[src] = GRAY;

      int dest; // dest = v, src = u
      for(int i = 0; i < G[src].degree; i++) // for all v ∈ Adj[u]
      {
            dest = G[src].adj[i];

            if(colours[dest] == WHITE)
            {
                  pi[dest] = src;
                  printf("(%d,%d) arco d'albero\n", src, dest);
                  dfs_visit_classification(G, dest, colours, pi);
            }
            else if(colours[dest] == GRAY)
                  if(pi[src] != dest)
                        printf("(%d,%d) arco all'indietro\n", src, dest);
                  else
                        printf("(%d,%d) arco d'albero\n", src, dest);
      }
}

void dfs_cormen(graph G, int N, int src)
{     
      int   *colours = malloc(N * sizeof(int)), 
            *pi = malloc(N * sizeof(int));

      for(int i = 0; i < N; i++)
      {
            colours[i] = WHITE;
            pi[i] = -1;
      }

      for(int i = 0; i < N; i++)
            if(colours[i] == WHITE)
                  dfs_visit_classification(G, src, colours, pi);
      
      free(pi);
      free(colours);
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

      dfs_cormen(G, N, 0);

      delete_graph(G, N);
      return 0;
}