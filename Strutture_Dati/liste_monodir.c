#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
      int data;
      struct _node *next;
} node;

node* create_list(node *list, int elem)
{     // la lista DEVE ESSERE VUOTA
      list = malloc(sizeof(node));
      list->data = elem;
      list->next = NULL;
      return list;
}

node* append(node *last_elem, int elem)
{     // last_elem è l'ultimo elemento inserito in lista
      // la lista NON DEVE ESSERE VUOTA
      last_elem->next = malloc(sizeof(node));
      last_elem->next->data = elem;
      last_elem->next->next = NULL;
      return last_elem->next;
}

void push_front(node **list, int elem)
{     // *list e' il primo elemento della lista
      node *new_elem = malloc(sizeof(node));
      new_elem->data = elem;
      new_elem->next = *list;
      *list = new_elem;
}

void insert_ordered(node **list, int data)
{
      node *curr = *list, *prec = NULL, *new_elem = malloc(sizeof(node)); 
      new_elem->data = data;

      while(curr != NULL && data > curr->data)
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

void delete_duplicates(node *list)
{
      if(list == NULL || list->next == NULL)
            return ;

      if(list->data == (list->next)->data)
      {
            node *tmp = list->next;
            list->next = tmp->next;
            free(tmp);
            delete_duplicates(list);
      }
      else
            delete_duplicates(list->next);
}

node* delete_elem(node *list, int elem)
{     /*
            Elimina il primo elemento uguale a elem,
            per eliminarli tutti basta non usare found.
      */
      node *curr = list, *prec = NULL, *tmp;      
      int found = 0;				
      while(curr != NULL && !found)
            if(curr->data == elem)
                  if(prec == NULL)
                  {
                        tmp = list;
                        list = curr->next;
                        free(tmp);
                        curr = list;
                        found = 1; 
                  }
                  else
                  {
                        prec->next = curr->next;
                        free(curr);
                        curr = prec->next;
                        found = 1;
                  }
            else
            {
                  prec = curr;
                  curr = curr->next;
            }
      return list;
}

node* delete_last(node *list)
{
      if(list == NULL)
            return NULL;
      
      if(list->next == NULL)
      {
            free(list);
            return NULL;
      }
      
      // Cerco il penultimo nodo.
      node *second_last = list;
      while(second_last->next->next != NULL)
            second_last = second_last->next;
      
      free(second_last->next);
      second_last->next = NULL;

      return list;
}

void print_list(node *list)
{
      while(list != NULL)
      {
            printf("%d ", list->data);
            list = list->next;
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

void reverse_print_list(node *list)
{
      if(list == NULL)
            return ;
      reverse_print_list(list->next);
      printf("%d\n", list->data);
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
