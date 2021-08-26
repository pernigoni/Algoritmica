#include <stdio.h>
#include <stdlib.h>
/*
      Lezione 9 - Esercizio 5 - PIATTAFORMA
*/
// VA BENE
typedef struct _node // ALBERO TERNARIO (lascio bst per comodità)
{
      int value;
      struct _node *left;
      struct _node *center;
      struct _node *right;
} node;

typedef node* bst;

void insert_in_bst__(bst *tree, int value)
{
      if(*tree == NULL)
      {
            bst newnode = malloc(sizeof(node));
            newnode->value = value;
            newnode->left = NULL;
            newnode->center = NULL;
            newnode->right = NULL;

            *tree = newnode;
      } 
      else
      {
            if(value < (*tree)->value)
                  insert_in_bst__(&((*tree)->left), value);
            else if(value % (*tree)->value == 0)
                  insert_in_bst__(&((*tree)->center), value);
            else
                  insert_in_bst__(&((*tree)->right), value);
      }
}

int three_sons(bst tree)
{
      if(tree == NULL)
            return 0;
      
      if(tree->left != NULL && tree->center != NULL && tree->right != NULL)
            return 1 + three_sons(tree->left) + three_sons(tree->center) + three_sons(tree->right);
      else 
            return three_sons(tree->left) + three_sons(tree->center) + three_sons(tree->right);
}

void clean_tree(bst *tree)
{
      if(*tree != NULL)
      {
            clean_tree(&((*tree)->left));
            clean_tree(&((*tree)->center));
            clean_tree(&((*tree)->right));
            free(*tree);
      }
}

int main()
{
      int N, value;

      bst tree = NULL;

      scanf("%d", &N);
      for(int i = 0; i < N; i++)
      {
            scanf("%d", &value);
            insert_in_bst__(&tree, value);
      }

      printf("%d\n", three_sons(tree));
      
      clean_tree(&tree);
      return 0;
}