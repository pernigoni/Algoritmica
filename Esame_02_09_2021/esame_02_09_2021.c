#include <stdio.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1

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

// cerca gli archi all'indietro
int dfs_cycle(graph G, int src, int *colours, int *pi, int k)
{
      colours[src] = GRAY;

      int dest;

      /*
            Il numero di adiacenti è al massimo k + 1.
                  k figli più il padre. 
      */
      if(G[src].degree > k + 1)
            return 0;

      for(int i = 0; i < G[src].degree; i++)
      {
            dest = G[src].adj[i];

            if(colours[dest] == WHITE)
            {
                  pi[dest] = src;
                  if(dfs_cycle(G, dest, colours, pi, k) == 1)
                        return 1;
            }
            /*
                  dest già incontrato ma non è il padre.
                  Grafo aciclico <=> non esistono archi all'indietro.
            */
            else if(pi[src] != dest)
                  return 1;
      }
      return 0;
}

int is_k_tree(graph G, int N, int src, int k)
{     
      int   *colours = malloc(N * sizeof(int)), 
            *pi = malloc(N * sizeof(int));

      for(int i = 0; i < N; i++) 
      {
            colours[i] = WHITE;
            pi[i] = -1;
      }

      int ret = 1; 
      if(dfs_cycle(G, src, colours, pi, k) == 1) // se c'è un ciclo
            ret = 0;

      for(int i = 0; i < N; i++)
            if(colours[i] == WHITE) // se il grafo non è connesso
                  ret = 0;

      free(colours);
      free(pi);
      return ret;
}

void delete_graph(graph G, int N)
{
      for(int i = 0; i < N; i++)
            free(G[i].adj);
      free(G);
}

int main()
{
      int N, k;
      graph G;

      scanf("%d %d", &k, &N);

      G = read_graph(N);

      printf("%d\n", is_k_tree(G, N, 0, k));

      delete_graph(G, N);
      return 0;
}