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

int lca(bst tree, int x, int y)
{
      if(tree != NULL)
      {
            if(x <= tree->value && y >= tree->value)
                  return tree->value;
            if(x >= tree->value && y <= tree->value)
                  return tree->value;
            
            if(x <= tree->value && y <= tree->value)
                  return lca(tree->left, x, y);
            if(x >= tree->value && y >= tree->value)
                  return lca(tree->right, x, y);
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
{     // n >= 2
      int n, value, x, y; 
      bst tree = NULL;

      scanf("%d", &n);
      for(int i = 0; i < n; i++)
      {
            scanf("%d", &value);
            insert_in_bst(&tree, value);
      }

      scanf("%d %d", &x, &y);

      printf("%d\n", lca(tree, x, y));

      clean_tree(&tree);
      return 0;
}