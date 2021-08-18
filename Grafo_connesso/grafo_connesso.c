#include <stdio.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2
// VA BENE

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

void dfs_visit_cormen(graph G, int src, int *colours, int *pi)
{
      colours[src] = GRAY;

      int dest;
      for(int i = 0; i < G[src].degree; i++)
      {
            dest = G[src].adj[i];

            if(colours[dest] == WHITE)
            {
                  pi[dest] = src;
                  dfs_visit_cormen(G, dest, colours, pi);
            }
      }
      colours[src] = BLACK;
}

int* dfs_cormen(graph G, int N, int src)
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
                  dfs_visit_cormen(G, src, colours, pi);
      
      free(pi);
      return colours;
}

int is_connected(graph G, int N, int src)
{
      int *colours = dfs_cormen(G, N, src);
      for(int i = 0; i < N; i++)
            if(colours[i] == WHITE)
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

      if(is_connected(G, N, 0) == 0)
            printf("0\n");
      else
            printf("1\n");

      delete_graph(G, N);
      return 0;
}