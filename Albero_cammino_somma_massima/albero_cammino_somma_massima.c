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

void min_maxPath(bst tree, int *max_sum, int *min)
{
      if(tree == NULL)
      {
            *max_sum = 0;
            *min = 0;
            return ;
      }
      
      int max_sum_L, max_sum_R, min_L, min_R;
      min_maxPath(tree->left, &max_sum_L, &min_L);
      min_maxPath(tree->right, &max_sum_R, &min_R);

      if(max_sum_L >= max_sum_R)
      {
            *max_sum = max_sum_L + tree->value;
            /*
                  Nel caso in cui non c'è alcun nodo sinistro, questo if
                  è scelto sse non c'è nemmeno alcun nodo destro.
                  (max_sum_L == max_sum_R) == 0
                  In questo caso il minimo è il valore del nodo corrente.
            */
            if(max_sum_L == 0)
                  *min = tree->value;
            else
                  *min = min_L;
      }
      else if(max_sum_L < max_sum_R)
      {
            *max_sum = max_sum_R + tree->value;
            /*
                  Il figlio destro di un nodo è maggiore del nodo, quindi
                  il minimo è sempre il valore del nodo corrente.
            */
            *min = tree->value;
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

      int max_sum, min;
      min_maxPath(tree, &max_sum, &min);
      printf("%d\n", min);

      clean_tree(&tree);
      return 0;
}
