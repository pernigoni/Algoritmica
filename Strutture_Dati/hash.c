#include <stdio.h>
#include <stdlib.h>

#define HASH_CONST 999149

typedef struct _item 
{
      int data;
      // struct _item *prec;
      struct _item *next;
} item;

int h(int x, int n)
{
      return (x % HASH_CONST) % (2 * n);
}

/* // LISTE BIDIREZIONALI
void insert_in_list(item **list, int elem)
{
      item *new_elem = malloc(sizeof(item));
      new_elem->data = elem;
      new_elem->prec = NULL;
      new_elem->next = *list;
      if(*list != NULL)
            (*list)->prec = new_elem;
      *list = new_elem;
}*/

// LISTE MONODIREZIONALI (uguale all'inserimento in testa delle liste)
void insert_in_list(item **list, int elem)
{
      item *new_elem = malloc(sizeof(item));
      new_elem->data = elem;
      new_elem->next = *list;
      *list = new_elem;
}

// LUNGHEZZA DELLA LISTA
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

// CERCA NELLA LISTA
int find(item *list, int elem) // 1 se trova elem, 0 altrimenti
{
      while(list != NULL)
      {
            if(list->data == elem)
                  return 1;
            list = list->next;
      }
      return 0;
}

// STAMPA TABELLA HASH
void print_hashtable(item **T, int n)
{
      for(int i = 0; i < 2 * n; i++)
      {   
            if(i != 0)
                  printf("\n");
            printf("======================================================\n");
            printf("i = %d | ", i);
            item *curr = T[i];
            while(curr != NULL)
            {
                  printf("(%d) ", curr->data);
                  curr = curr->next;
            }
      }
      printf("\n======================================================\n");
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

      T = malloc(2 * n * sizeof(item *));
      for(int i = 0; i < 2 * n; i++)
            T[i] = NULL;
      
      for(int i = 0; i < n; i++)
      {
            scanf("%d", &x);
            hash = h(x, n); 	// OPPURE h(x);
            insert_in_list(&T[hash], x);
      }

      // DO THINGS

      print_hashtable(T, n);

      for(int i = 0; i < 2 * n; i++)
            clear_list(&T[i]);
      free(T);

      return 0;
}
