#include <stdio.h>
#include <stdlib.h>
// VA BENE

int count = 0;

typedef struct _node
{
      int data;
      struct _node *next;
} node;

void push_front(node **list, int elem)
{
      node *new_elem = malloc(sizeof(node));
      new_elem->data = elem;
      new_elem->next = *list;
      *list = new_elem;
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
            {
                  count--;

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
            }
            else
            {
                  prec = curr;
                  curr = curr->next;
            }

      count++;

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
      printf("$\n");
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
      int N, elem, op;
      node *Q = NULL;
      
      scanf("%d", &N);

      do
      {
            scanf("%d", &op);

            if(op == 1)
            {
                  scanf("%d", &elem);
                  Q = delete_elem(Q, elem);
                  push_front(&Q, elem);

                  if(count > N)
                  {     // La lunghezza di Q eccede N quindi elimino l'ultimo.
                        Q = delete_last(Q);
                        count--; 
                  }
            }
            else if(op == 2)
                  print_list(Q);

      } while(op != 0) ;

      free_list(&Q);
      return 0;
}