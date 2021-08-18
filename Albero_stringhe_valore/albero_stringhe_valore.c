#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// VA BENE
typedef struct _node
{
      char *str;    // chiave
      int value;
      struct _node *left;
      struct _node *right;
} node;

typedef node* bst;

void insert_in_bst(bst *tree, int value, char *str)
{
      if(*tree == NULL)
      {
            bst newnode = (bst) malloc(sizeof(node));
            newnode->value = value;
            newnode->str = str;
            newnode->left = NULL;
            newnode->right = NULL;

            *tree = newnode;
      } 
      else
            if(strcmp(str, (*tree)->str) <= 0)
                  insert_in_bst(&((*tree)->left), value, str);
            else
                  insert_in_bst(&((*tree)->right), value, str);
}

void max(bst tree, int *maxx)
{     // i valori, non essendo chiavi, non sono in ordine
      if(tree != NULL)
      {
            max(tree->left, maxx);
            max(tree->right, maxx);

            if(tree->value > *maxx)
                  *maxx = tree->value;
      }  
}

void find_string_max_value(bst tree, char *str)
{
      if(tree != NULL)
      {
            if(strcmp(str, tree->str) < 0)
                  find_string_max_value(tree->left, str);
            else if(strcmp(str, tree->str) > 0)
                  find_string_max_value(tree->right, str);
            else // strcmp(str, tree->str) == 0
            {
                  int maxx = tree->value;
                  max(tree, &maxx);
                  printf("%d\n", maxx);
            }
      }
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
      int n, value;
      bst tree = NULL;

      scanf("%d", &n);
      for(int i = 0; i < n; i++)
      {
            char *str = malloc(101 * sizeof(char));
            scanf("%s %d", str, &value);
            insert_in_bst(&tree, value, str);
      }

      char *str = malloc(101 * sizeof(char));
      scanf("%s", str); // stringa da cercare
      find_string_max_value(tree, str);

      free(str);
      clean_tree(&tree);
      return 0;
}