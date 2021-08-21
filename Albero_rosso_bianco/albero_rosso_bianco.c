#include <stdio.h>
#include <stdlib.h>
// VA BENE
typedef struct _node
{
      int value;
      int color; // 0 = rosso, 1 = bianco
      struct _node *left;
      struct _node *right;
} node;

typedef node* bst;

int max(int a, int b)
{
      return a > b ? a : b;
}

void insert_in_bst(bst *tree, int value, int color)
{
      if(*tree == NULL)
      {
            bst newnode = malloc(sizeof(node));
            newnode->value = value;
            newnode->color = color;
            newnode->left = NULL;
            newnode->right = NULL;
            *tree = newnode;
      } 
      else
            if(value <= (*tree)->value)
                  insert_in_bst(&((*tree)->left), value, color);
            else
                  insert_in_bst(&((*tree)->right), value, color);
}

int red_height(bst tree, int *ok)
{
      if(tree == NULL)
            return 0;
      
      int hsx, hdx;
      if(tree->color == 0)
      {
            hsx = 1 + red_height(tree->left, ok);
            hdx = 1 + red_height(tree->right, ok);
      }  
      else
      {
            hsx = red_height(tree->left, ok);
            hdx = red_height(tree->right, ok);
      } 
      if(abs(hsx - hdx) > 1)
            *ok = 0;

      return max(hsx, hdx);
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
      int n, value, color, ok = 1;
      bst tree = NULL;

      scanf("%d", &n);
      for(int i = 0; i < n; i++)
      {
            scanf("%d %d", &value, &color);
            insert_in_bst(&tree, value, color);
      }

      red_height(tree, &ok);

      if(ok)
            printf("TRUE\n");
      else
            printf("FALSE\n");

      clean_tree(&tree);
      return 0;
}
