#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
      Esame del 27/06/2014 - PIATTAFORMA
*/
// VA BENE
typedef struct _item 
{
      char *key;  // nome 
      char *phone;  // numero di telefono
      struct _item *next;
} item;

int h(char *key, int N)
{
      int i = 0, pos = 0;
      while(key[i] != '\0')
      {
            pos += key[i];
            i++;
      }
      return pos % (2 * N);
}

void insert_ordered(item **list, char *key, char *phone)
{
      item *curr = *list, *prec = NULL, *new_elem = malloc(sizeof(item)); 
      new_elem->key = key;
      new_elem->phone = phone;

      while(curr != NULL && strcmp(key, curr->key) > 0)
      {
            prec = curr;
            curr = curr->next;         
      }
      if(prec == NULL)
      {
            new_elem->next = *list;
            *list = new_elem;
      }
      else
      {
            prec->next = new_elem;
            new_elem->next = curr;
      }
}

void print_list(item *list)
{
      while(list != NULL)
      {
            printf("%s %s\n", list->key, list->phone);
            list = list->next;
      }
}

void clear_list(item **list)
{
      item *aux;
      while(*list != NULL)
      {
            free((*list)->key);     // !!!!!
            free((*list)->phone);   // !!!!!

            aux = *list;
            (*list) = (*list)->next;
            free(aux);
      }
}

int main()
{
      item **T;
      int n, hash;

      scanf("%d", &n);

      if(n == 0)
            return 0;

      T = malloc(2 * n * sizeof(item*));
      for(int i = 0; i < 2 * n; i++)
            T[i] = NULL;

      for(int i = 0; i < n; i++)
      {
            char  *key = malloc(101 * sizeof(char)), 
                  *phone = malloc(21 * sizeof(char));
            scanf("%s %s", key, phone);

            hash = h(key, n);
            insert_ordered(&T[hash], key, phone);
      }

      int k;
      scanf("%d", &k);
      if(k >= 0 && k < 2 * n)
            print_list(T[k]);
      
      for(int i = 0; i < 2 * n; i++)
            clear_list(&T[i]);
      free(T);

      return 0;
}





















