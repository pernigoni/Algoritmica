#include <stdio.h>
#include <stdlib.h>
// due colori a caso
#define RED 0     
#define BLUE 1
// VA BENE
/*
      Un grafo è bipartito sse è possibile colorarlo usando 2 colori.
      Colorare il grafo vuol dire assegnare ad ogni nodo un colore diverso
      da quello dei suoi vertici adiacenti.
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

/*
      Colorazione ricorsiva di tipo DFS, src è il nodo che abbiamo appena raggiunto,
      col è il colore con cui stiamo cercando di colorarlo.
*/
int dfs_visit_two_colours(graph G, int N, int *colours, int src, int col)
{
      if(colours[src] != -1 && colours[src] != col)
            return 0; // il nodo è già stato colorato con un colore diverso
      
      colours[src] = col;

      int dest;
      for(int i = 0; i < G[src].degree; i++)
      {
            dest = G[src].adj[i];
            
            if(colours[dest] == -1)
            {     // nodo non colorato, provo a colorarlo con il colore opposto
                  if(dfs_visit_two_colours(G, N, colours, dest, !col) == 0)
                        return 0;
            }
            else
                  // nodo colorato, controllo che il colore sia giusto
                  if(colours[dest] == col)
                        return 0; // dest ha lo stesso colore di src
      }
      return 1;
}

int is_bipartite(graph G, int N)
{     
      int colours[N];

      for(int i = 0; i < N; i++)
            colours[i] = -1;  // -1 vuol dire che il nodo non è ancora stato visitato

      for(int i = 0; i < N; i++)
            /*
                  Se il nodo è già stato colorato si va avanti,
                  altrimenti si controlla che la colorazione ricorsiva
                  abbia avuto successo.
            */
            if(colours[i] == -1 && 0 == dfs_visit_two_colours(G, N, colours, i, RED))
                  return 0;
      
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

      printf("%d\n", is_bipartite(G, N));

      delete_graph(G, N);
      return 0;
}