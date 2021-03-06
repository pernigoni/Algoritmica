#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
      int data;
      struct _node *prec;
      struct _node *next;
} node;

node* create_list(node *list, int elem)
{     // la lista e' VUOTA
      list = malloc(sizeof(node));
      list->data = elem;
      list->next = NULL;
      list->prec = NULL;
      return list;
}

node* append(node *last_elem, int elem)
{     // last_elem e' l'ultimo elemento inserito in lista
      // la lista deve essere NON-VUOTA
      last_elem->next = malloc(sizeof(node));
      last_elem->next->data = elem;
      last_elem->next->next = NULL;
      last_elem->next->prec = last_elem;
      return last_elem->next;
}

void push_front(node **list, int elem)
{     // *list e' il primo elemento della lista
      node *new_elem = malloc(sizeof(node));
      new_elem->data = elem;
      new_elem->prec = NULL;
      new_elem->next = *list;
      (*list)->prec = new_elem;
      *list = new_elem;
}

void print_list(node *list)
{
      while(list != NULL)
      {
            printf("%d ", list->data);
            list = list->next;
      }
}

void reverse_print_list(node *rev_list)
{     // rev_list e' puntatore all'ultimo elemento della lista
      while(rev_list != NULL)
      {
            printf("%d ", rev_list->data);
            rev_list = rev_list->prec;
      }
}

void free_list(node **list)
{
      node *aux;
      while(*list != NULL)
      {
            aux = *list;
            *list = (*list)->next;
            free(aux);
      }
}

int main()
{
      int N, elem;
      node *list = NULL;
      
      // node *last_elem = NULL; // solo per inserimento in coda
      
      scanf("%d", &N);

      for(int i = 0; i < N; i++)
      {
            scanf("%d", &elem);
            if(list == NULL)
            {
                  list = create_list(list, elem);
                  // last_elem = list;
            } 
            else 
            {
                  // IN TESTA
                  push_front(&list, elem);
                  // IN CODA
                  // last_elem = append(last_elem, elem);
            }
      }

      // DO THINGS

      free_list(&list);
      return 0;
}