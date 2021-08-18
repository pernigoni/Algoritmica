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

void print_level(bst tree, int k, int dpt) 
{
      if(tree != NULL)
      {
            print_level(tree->left, k, dpt + 1);
            
            if(k == dpt)
                  printf("%d\n", tree->value);
                  
            print_level(tree->right, k, dpt + 1);
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

      scanf("%d", &k);
      print_level(tree, k, 0);

      clean_tree(&tree);
      return 0;
}