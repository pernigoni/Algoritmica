#include <stdio.h>
#include <stdlib.h>
// VA BENE
typedef struct _node
{
      int value;
      struct _node *left;
      struct _node *right;
} node;

typedef node* bst;

void insert_in_bst(bst *tree, int value)
{
      if(*tree == NULL)
      {
            bst newnode = (bst) malloc(sizeof(node));
            newnode->value = value;
            newnode->left = NULL;
            newnode->right = NULL;

            *tree = newnode;
      } 
      else
            if(value <= (*tree)->value)
                  insert_in_bst(&((*tree)->left), value);
            else
                  insert_in_bst(&((*tree)->right), value);
}

void second_max(bst tree, int *count)
{     /*
            Il secondo massimo è il penultimo elemento della visita in ordine
                  => è il secondo elemento della visita in ordine inverso.
      */
      if(tree != NULL && *count < 2)
      {
            second_max(tree->right, count);

            (*count)++;
            if(*count == 2)
                  printf("%d\n", tree->value);

            second_max(tree->left, count);
      }
}

void clean_tree(bst *tree)
{
      if(*tree != NULL)
      {
            clean_tree(&((*tree)->left));
            clean_tree(&((*tree)->right));
            free(*tree);
      }
}

int main()
{
      int n, value, k;
      bst tree = NULL;

      scanf("%d", &n);
      for(int i = 0; i < n; i++)
      {
            scanf("%d", &value);
            insert_in_bst(&tree, value);
      }

      int count = 0;
      second_max(tree, &count);

      clean_tree(&tree);
      return 0;
}