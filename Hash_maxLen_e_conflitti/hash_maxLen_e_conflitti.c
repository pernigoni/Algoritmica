#include <stdio.h>
#include <stdlib.h>
#define HASH_CONST 999149
/*
      Lezione 10 - Esercizio 1 - PIATTAFORMA
*/
// VA BENE
typedef struct _item 
{
      int data;
      struct _item *next;
} item;

int h(int x, int n, int a, int b)
{
      return ((a * x + b) % HASH_CONST) % (2 * n);
}

void insert_in_list__(item **list, int elem, int *conflicts)
{
      if(*list != NULL) // se la lista non è vuota c'è conflitto
            *conflicts += 1;
      
      item *new_elem = malloc(sizeof(item));
      new_elem->data = elem;
      new_elem->next = *list;
      *list = new_elem;
}

int length(item *list)
{
      int len = 0;
      while(list != NULL)
      {
            len++;
            list = list->next;
      }
      return len;
}

void clear_list(item **list)
{
      item *aux;
      while(*list != NULL)
      {
            aux = *list;
            (*list) = (*list)->next;
            free(aux);
      }
}

int main()
{
      item **T;
      int n, x, hash;

      scanf("%d", &n);
      
      int a, b;
      scanf("%d %d", &a, &b);

      T = malloc(2 * n * sizeof(item *));
      for(int i = 0; i < 2 * n; i++)
            T[i] = NULL;
      
      int conflicts = 0;
      for(int i = 0; i < n; i++)
      {
            scanf("%d", &x);
            hash = h(x, n, a, b);
            insert_in_list__(&T[hash], x, &conflicts);
      }

      int max_len = length(T[0]);
      for(int i = 1; i < 2 * n; i++)
            if(length(T[i]) > max_len)
                  max_len = length(T[i]);

      printf("%d\n%d\n", max_len, conflicts);

      for(int i = 0; i < 2 * n; i++)
            clear_list(&T[i]);
      free(T);

      return 0;
}