#include <stdio.h>
#include <stdlib.h>
// VA BENE
typedef struct _node
{
      int value;
      int L;
      int R;
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

            newnode->L = 0;
            newnode->R = 0;

            *tree = newnode;
      } 
      else
            if(value <= (*tree)->value)
                  insert_in_bst(&((*tree)->left), value);
            else
                  insert_in_bst(&((*tree)->right), value);
}

void post_visit(bst tree)
{
      if(tree != NULL)
      {
            post_visit(tree->left);
            post_visit(tree->right);
            if(tree->left != NULL)
                  tree->L = tree->left->L + 1;
            if(tree->right != NULL)
                  tree->R = tree->right->R + 1;
      }
}

void increasing_sort(bst tree)
{
      if(tree != NULL)
      {
            increasing_sort(tree->left);
            if(tree->L > tree->R)
                  printf("%d\n", tree->value);
            increasing_sort(tree->right);
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
      int n, value;
      bst tree = NULL;

      scanf("%d", &n);
      for(int i = 0; i < n; i++)
      {
            scanf("%d", &value);
            insert_in_bst(&tree, value);
      }

      post_visit(tree);
      increasing_sort(tree);
      
      clean_tree(&tree);
      return 0;
}













