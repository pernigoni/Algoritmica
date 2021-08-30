#include <stdio.h>
#include <stdlib.h>
#define HASH_CONST 999149
// VA BENE
typedef struct _item 
{
      int data;
      int count;  // numero occorrenze di data
      struct _item *next;
} item;

int h(int x, int n)
{
      return (x % 999149) % (2 * n);
}

void insert_in_list(item **list, int elem)
{
      item *new_elem = malloc(sizeof(item));
      new_elem->data = elem;
      new_elem->next = *list;
      *list = new_elem;
}

void insert_in_list__(item **list, int data)
{     /*
            Se trovo data nella tabella aggiorno il campo count,
            altrimenti inserimento in testa.
      */
      item *curr = *list;
      while(curr != NULL)
      {
            if(curr->data == data)
            {
                  curr->count += 1;
                  return ;
            }
            curr = curr->next;
      }

      item *new_elem = malloc(sizeof(item));
      new_elem->data = data;
      new_elem->count = 1;
      new_elem->next = *list;
      *list = new_elem;
}

int is_count_greater_than_k(item *list, int elem, int k)
{
      while(list != NULL)
      {
            if(list->data == elem && list->count >= k)
                  return 1;
            list = list->next;
      }
      return 0;
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
      int n, k, x, hash;

      scanf("%d %d", &n, &k);

      T = (item **) malloc(2 * n * sizeof(item *));
      for(int i = 0; i < 2 * n; i++)
            T[i] = NULL;
      
      int *a = malloc(n * sizeof(int));
      for(int i = 0; i < n; i++)
      {
            scanf("%d", &x);
            a[i] = x;
            hash = h(x, n);
            insert_in_list__(&T[hash], x);
      }

      for(int i = 0; i < n; i++)
      {
            hash = h(a[i], n);
            if(is_count_greater_than_k(T[hash], a[i], k) == 1)
                  printf("%d ", a[i]);
      }
      printf("\n");
      free(a);

      for(int i = 0; i < 2 * n; i++)
            clear_list(&T[i]);
      free(T);

      return 0;
}
