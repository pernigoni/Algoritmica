#include <stdio.h>
#include <stdlib.h>
// VA BENE
/*
      Cammino minimo da src a v.
*/
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
{     // it works iff the queue is not full
      if(Q->size < Q->capacity)
      {
            Q->tail = (Q->tail + 1) % Q->capacity;
            Q->values[Q->tail] = value;
            Q->size++;
      }
}

int queue_popFront(queue *Q)
{     // it works under the assumption that the queue is not empty
      int front = Q->values[Q->head];
      Q->head = (Q->head + 1) % Q->capacity;
      Q->size--;
      return front;
}

int queue_isEmpty(queue *Q)
{
      return Q->size == 0;
}

// DISTANCE BFS
int* distance_bfs(graph G, int N, int src)
{
      int *distance = malloc(sizeof(int) * N);
      queue Q;
      int current, dest;

      for(int i = 0; i < N; i++) 
            distance[i] = -1;
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

      int k, src, dest;
      scanf("%d", &k);
      for(int i = 0; i < k; i++)
      {
            scanf("%d %d", &src, &dest);
            int *distance = distance_bfs(G, N, src);
            printf("%d\n", distance[dest]);
            free(distance);
      }

      delete_graph(G, N);
      return 0;
}





