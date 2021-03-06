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
      int count; // conta quanti elementi sono presenti dopo curr
      struct _item *next;
} item;

int h(int x, int n, int a, int b)
{
      return ((a * x + b) % HASH_CONST) % (2 * n);
}

void insert_in_list__(item **list, int elem, int *conflicts, int *max_len)
{
      if(*list != NULL) // se la lista non è vuota c'è conflitto
            *conflicts += 1;

      item *new_elem = malloc(sizeof(item));
      new_elem->data = elem;
      new_elem->next = *list;

      if(*list == NULL)
            new_elem->count = 0;
      else
            new_elem->count = new_elem->next->count + 1;

      if(new_elem->count > *max_len)
            *max_len = new_elem->count;

      *list = new_elem;
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
      
      int conflicts = 0, max_len = 0;
      for(int i = 0; i < n; i++)
      {
            scanf("%d", &x);
            hash = h(x, n, a, b);
            insert_in_list__(&T[hash], x, &conflicts, &max_len);
      }

      printf("%d\n%d\n", max_len + 1, conflicts);

      for(int i = 0; i < 2 * n; i++)
            clear_list(&T[i]);
      free(T);

      return 0;
}
