#include <stdio.h>
#include <stdlib.h>
/*
      Lezione 9 - Esercizio 4 - PIATTAFORMA
*/
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
            bst newnode = malloc(sizeof(node));
            newnode->value = value;
            newnode->left = NULL;
            newnode->right = NULL;

            *tree = newnode;
      } 
      else
      {
            if(value <= (*tree)->value)
                  insert_in_bst(&((*tree)->left), value);
            else 
                  insert_in_bst(&((*tree)->right), value);
      }
}

int same_path_from_src_to_k(bst tree_1, bst tree_2, int k)
{     
      if(tree_1 == NULL || tree_2 == NULL)
            return 0;

      if(tree_1->value == tree_2->value)
      {
            if(k < tree_1->value)
                  return same_path_from_src_to_k(tree_1->left, tree_2->left, k);
            else if(k > tree_1->value)
                  return same_path_from_src_to_k(tree_1->right, tree_2->right, k);
            else
                  return 1;
      }

      return 0;
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
      int N, value, k;

      bst tree_1 = NULL, tree_2 = NULL;

      scanf("%d %d", &N, &k);

      for(int i = 0; i < N; i++)
      {
            scanf("%d", &value);
            insert_in_bst(&tree_1, value);
      }
      for(int i = 0; i < N; i++)
      {
            scanf("%d", &value);
            insert_in_bst(&tree_2, value);
      }

      printf("%d\n", same_path_from_src_to_k(tree_1, tree_2, k));
      
      clean_tree(&tree_1);
      clean_tree(&tree_2);
      return 0;
}