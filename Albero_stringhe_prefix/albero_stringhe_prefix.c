#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// VA BENE
typedef struct _node
{
      char *str;
      struct _node *left;
      struct _node *right;
} node;

typedef node* bst;

void insert_in_bst(bst *tree, char *str)
{
      if(*tree == NULL)
      {
            bst newnode = (bst) malloc(sizeof(node));
            newnode->str = str;
            newnode->left = NULL;
            newnode->right = NULL;
            *tree = newnode;
      } 
      else
            if(strcmp(str, (*tree)->str) <= 0)
                  insert_in_bst(&((*tree)->left), str);
            else
                  insert_in_bst(&((*tree)->right), str);
}

int contains(char *a, char *b)  // ritorna 1 se a contiene b, 0 altrimenti
{
      if(strlen(a) < strlen(b))
            return 0;
      for(int i = 0; i < strlen(b); i++)
            if(a[i] != b[i])
                  return 0;
      return 1;
}

char* print_prefix(bst tree)
{
      if(tree != NULL)
      {     /*
                  Se tree->left == NULL allora il minimo è nel nodo corrente,
                  altrimenti lo cerco a sinistra.
            */
            char *min = tree->str;
            if(tree->left != NULL)
                  min = print_prefix(tree->left);
            /*
                  Se min è prefisso di tree->str, stampo tree->str.
                  (in altre parole se tree->str contiene min...)
            */
            if(contains(tree->str, min) == 1)
                  printf("%s\n", tree->str);
            /*
                  I nodi a destra non sono influenzati da quello che c'è a
                  sinistra.
                  Ogni volta che si va a destra si "ricomincia".
            */
            print_prefix(tree->right);
            /*
                  Finita la visita di un sottoalbero il padre potrebbe aver bisogno
                  del min. In particolare se il sottoalbero era radicato a sinistra,
                  altrimenti lo ignora. 
            */
            return min;
      }
      else
            return "";
}

void clean_tree(bst *tree)
{
      if(*tree != NULL)
      {
            clean_tree(&((*tree)->left));

            free((*tree)->str); // !!!!!

            clean_tree(&((*tree)->right));
            free(*tree);
      }
}

int main()
{
      int n;
      bst tree = NULL;

      scanf("%d", &n);
      for(int i = 0; i < n; i++)
      {
            char *str = malloc(101 * sizeof(char));
            scanf("%s", str);
            insert_in_bst(&tree, str);
      }

      print_prefix(tree);
      
      clean_tree(&tree);
      return 0;
}