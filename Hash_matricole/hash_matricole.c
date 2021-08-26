#include <stdio.h>
#include <stdlib.h>
#define HASH_CONST 941
/*
      APPELLO 10/09/2019

      Inserire N matricole in una tabella hash di dimensione 2N usando la funzione 
      hash h = (matricola * 941) % 2N.
      Successivamente si acquisiscono due sequenze di matricole rispettivamente di 
      lunghezza M1 e M2 che corrispondono ai bocciati di prima e seconda prova.
      Eliminare dalla tabella le matricole che hanno bocciato sia la prima che la 
      seconda prova.
      Stampare il numero di studenti che possono sostenere la prova finale (che sono
      stati boccciati al massimo una volta).

      INPUT:      5 123 333 666 111 400 2 123 666 3 400 123 666
      OUTPUT:     3
*/

// NON HO I TEST MA DOVREBBE ANDARE BENE

typedef struct _item 
{
      int data; // matricola
      int count_fails;
      struct _item *next;
} item;

int h(int x, int n)
{
      return (x * HASH_CONST) % (2 * n);
}

void insert_in_list(item **list, int elem)
{
      item *new_elem = malloc(sizeof(item));
      new_elem->data = elem;
      new_elem->count_fails = 0;
      new_elem->next = *list;
      *list = new_elem;
}

void update_fails(item **list, int elem)
{
      item *curr = *list;
      while(curr != NULL)
      {
            if(curr->data == elem)
            {
                  curr->count_fails += 1;
                  return ;
            }
            curr = curr->next;
      }
}

item* delete_two_fails(item *list, int *count)
{     
      item *curr = list, *prec = NULL, *tmp;      			
      while(curr != NULL)
            if(curr->count_fails == 2)
            {
                  *count += 1;

                  if(prec == NULL)
                  {
                        tmp = list;
                        list = curr->next;
                        free(tmp);
                        curr = list;
                  }
                  else
                  {
                        prec->next = curr->next;
                        free(curr);
                        curr = prec->next;
                  }
            }
            else
            {
                  prec = curr;
                  curr = curr->next;
            }
      return list;
}

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
            hash = h(x, n);
            insert_in_list(&T[hash], x);
      }

      int m;

      printf("Numero di bocciati della PRIMA prova.. ");
      scanf("%d", &m);
      for(int i = 0; i < m; i++)
      {
            scanf("%d", &x);
            hash = h(x, n);
            update_fails(&T[hash], x);
      }

      printf("Numero di bocciati della SECONDA prova.. ");
      scanf("%d", &m);
      for(int i = 0; i < m; i++)
      {
            scanf("%d", &x);
            hash = h(x, n);
            update_fails(&T[hash], x);
      }

      // ELIMINARE DALLA TABELLA CHI HA FALLITO ENTRAMBE LE PROVE
      int count = 0; // mi serve contarli perché lo chiede l'esercizio
      for(int i = 0; i < 2 * n; i++)
            T[i] = delete_two_fails(T[i], &count);

      print_hashtable(T, n);

      printf("%d\n", n - count); // studenti che possono sostenere la prova finale

      for(int i = 0; i < 2 * n; i++)
            clear_list(&T[i]);
      free(T);

      return 0;
}