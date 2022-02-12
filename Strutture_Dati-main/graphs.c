#include <stdio.h>
#include <stdlib.h>
// !!! IN FONDO C'È LA DFS IN STILE CORMEN

typedef struct _edges
{
      int degree;
      int *adj;
} edges;

typedef edges* graph;

typedef struct _queue
{
      int *values;
      int capacity;
      int head;
      int tail;
      int size;	
} queue;
 
int main()
{
      int N;
      graph G;

      scanf("%d", &N);
      G = read_graph(N);

      delete_graph(G, N);
      return 0;
}

// GRAFO INDIRETTO
graph read_graph(int N)
{
      graph G = malloc(sizeof(edges) * N);

      for(int i = 0; i < N; i++)
      {
            scanf("%d", &G[i].degree);
            G[i].adj = malloc(sizeof(int) * G[i].degree);
            for(int j = 0; j < G[i].degree; j++)
                  scanf("%d", &G[i].adj[j]);        
      }
      return G;
}

void delete_graph(graph G, int N)
{
      for(int i = 0; i < N; i++)
            free(G[i].adj);
      free(G);
}

void print_graph(graph G, int N)
{
      for(int i = 0; i < N; i++)
      {
            printf("%d: ", i);
            for(int j = 0; j < G[i].degree; j++)
                  printf("%d ", G[i].adj[j]);
            printf("\n");
      } 
      printf("\n");
}
		
// DFS
int* dfs(graph G, int N, int src)
{
      int *colours = malloc(N * sizeof(int)); // la colorazione è solo bianco e nero
      for(int i = 0; i < N; i++) 
            colours[i] = 0;

      colours[src] = 1;

      recursive_dfs(G, src, colours);
      // iterative_dfs(G, N, src, colours);

      return colours;
}

void recursive_dfs(graph G, int src, int *colours)
{
      int dest;

      for(int i = 0; i < G[src].degree; i++)
      {
            dest = G[src].adj[i];
            if(colours[dest] == 0)
            {
                  colours[dest] = 1;
                  recursive_dfs(G, dest, colours);
            }
      }
}

void iterative_dfs(graph G, int N, int src, int *colours)
{     // più efficiente
      int *stack = malloc(N * sizeof(int));
      int stack_size, current, dest;

      stack[0] = src;
      stack_size = 1;

      while(stack_size > 0)
      {
            current = stack[--stack_size];
            for(int i = 0; i < G[current].degree; i++)
            {
                  dest = G[current].adj[i];
                  if(colours[dest] == 0)
                  {
                        colours[dest] = 1;
                        stack[stack_size++] = dest;
                  }
            }
      }

      free(stack);
}

// IMPLEMENTAZIONE OPERAZIONI CODA

void queue_init(queue *Q, int capacity)
{
      Q->capacity = capacity;
      Q->values = malloc(capacity * sizeof(int));
      Q->head = 0;
      Q->tail = -1;
      Q->size = 0;
}

void queue_delete(queue *Q)
{
      free(Q->values);
}

void queue_pushBack(queue *Q, int value)
{     // funziona sse la coda non è piena
      if(Q->size < Q->capacity)
      {
            Q->tail = (Q->tail + 1) % Q->capacity;
            Q->values[Q->tail] = value;
            Q->size++;
      }
}

int queue_popFront(queue *Q)
{     // funziona assumendo che la coda non sia vuota
      int front = Q->values[Q->head];
      Q->head = (Q->head + 1) % Q->capacity;
      Q->size--;
      return front;
}

int queue_isEmpty(queue *Q)
{
      return Q->size == 0;
}

// BFS			
//     importante per calcolare la distanza tra i vertici
int* bfs(graph G, int N, int src)
{
      int *colours = malloc(sizeof(int) * N);
      queue Q;
      int current, dest;

      for(int i = 0; i < N; i++) 
            colours[i] = 0;
      colours[src] = 1;

      queue_init(&Q, N);
      queue_pushBack(&Q, src);

      while(!queue_isEmpty(&Q))
      {
            current = queue_popFront(&Q);
            for(int i = 0; i < G[current].degree; i++)
            {
                  dest = G[current].adj[i];
                  if(colours[dest] == 0)
                  {
                  	colours[dest] = 1;
                        queue_pushBack(&Q, dest);
                  }
            }
      }
      queue_delete(&Q);
      return colours;
}

// DISTANCE BFS
int* distance_bfs(graph G, int N, int src)
{
      int *distance = malloc(sizeof(int) * N);
      queue Q;
      int current, dest;

      for(int i = 0; i < N; i++) distance[i] = -1;
      distance[src] = 0;

      queue_init(&Q, N);
      queue_pushBack(&Q, src);

      while(!queue_isEmpty(&Q))
      {
            current = queue_popFront(&Q);
            for(int i = 0; i < G[current].degree; i++)
            {
                  dest = G[current].adj[i];
                  if(distance[dest] == -1)
                  {
                  	distance[dest] = 1 + distance[current];
                  	queue_pushBack(&Q, dest);
                  }
            }
      }
      queue_delete(&Q);
      return distance; // array che contiene le distanze minime tra src e i
}

// DFS FATTA DA ME PSEUDO-COPIANDO QUELLA DEL CORMEN
#define WHITE 0
#define GRAY 1
#define BLACK 2

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
