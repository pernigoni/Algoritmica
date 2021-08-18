#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
      Esame del 06/11/2014 - PIATTAFORMA
*/
// VA BENE
typedef struct _item 
{
      char *key;  // nome oggetto
      int value;  // valore affettivo
      struct _item *next;
} item;

typedef struct _pair
{
      char *array_key;
      int array_value;
} pair;

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

int count = 0; // conta il numero di elementi inseriti nella tabella hash

void insert_in_list__(item **list, char *key, int value)
{
      item *curr = *list;
      while(curr != NULL)
      {
            if(strcmp(curr->key, key) == 0)
                  if(value > curr->value)
                  {
                        curr->value = value;
                        free(key); // !!!!!
                        return ;
                  }
                  else
                  {
                        free(key); // !!!!!
                        return ;
                  }
            curr = curr->next;
      }

      count++;

      item *new_elem = malloc(sizeof(item));
      new_elem->key = key;
      new_elem->value = value;
      new_elem->next = *list;
      *list = new_elem;
}

void clear_list(item **list)
{
      item *aux;
      while(*list != NULL)
      {
            // free((*list)->key);  NON VA FATTO PERCHÈ L'HO LIBERATO "SFRUTTANDO L'ARRAY DI COPIA"

            aux = *list;
            (*list) = (*list)->next;
            free(aux);
      }
}

int struct_int_cmp_decreasing(const void *a, const void *b)
{
      pair *n = (pair *) a;
      pair *m = (pair *) b;
      return m->array_value - n->array_value;
}

int struct_str_cmp_increasing_ifValueIsTheSame(const void *a, const void *b)
{     
      /*
            A parità di value ordina in modo alfabetico crescente su key.
      */
      pair *n = (pair *) a;
      pair *m = (pair *) b;

      if(n->array_value == m->array_value)
            return strcmp(n->array_key, m->array_key);
      else
            return 0;
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
            char *key = malloc(101 * sizeof(char));
            /*
                  In alcuni casi la insert prevede che key non venga
                  inserito quindi libero key nella insert (altrimenti
                  è memoria irraggiungibile persa per sempre).

                  Mentre alla fine, nella clear_list, libero le key
                  inserite nella tabella.
            */
            int value;
            scanf("%s %d", key, &value);

            hash = h(key, n);
            insert_in_list__(&T[hash], key, value);
      }

      /*
            Copio gli elementi della tabella hash in un array di pair.
            Poi ordino in modo decrescente su array_value e a parità
            di array_value in modo alfabetico crescente su array_key.
      */
      pair *a = malloc(count * sizeof(pair));
      int j = 0;

      for(int i = 0; i < 2 * n; i++)
      {
            item *curr = T[i];
            while(curr != NULL)
            {
                  a[j].array_key = curr->key;
                  a[j].array_value = curr->value;
                  j++;
                  curr = curr->next;
            }
      }

      qsort(a, count, sizeof(pair), struct_int_cmp_decreasing);
      qsort(a, count, sizeof(pair), struct_str_cmp_increasing_ifValueIsTheSame);

      for(int i = 0; i < 15; i++)   // il problema dice di stampare i primi 15
            printf("%s\n", a[i].array_key);
      
      for(int i = 0; i < count; i++) // libero l'array di pair
            free(a[i].array_key);
      free(a);


      for(int i = 0; i < 2 * n; i++)
            clear_list(&T[i]);
      free(T);

      return 0;
}
