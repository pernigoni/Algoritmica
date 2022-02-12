#include <stdio.h>
#include <stdlib.h>

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

// STAMPA IN ORDINE CRESCENTE
void increasing_sort(bst tree)
{	
      if(tree != NULL)
      {
            increasing_sort(tree->left);
            printf("%d\n", tree->value);
            increasing_sort(tree->right);
      }
}

// STAMPA IN ORDINE DECRESCENTE
void decreasing_sort(bst tree)
{
      if(tree != NULL)
      {
            decreasing_sort(tree->right);
            printf("%d\n", tree->value);
            decreasing_sort(tree->left);
      }
}

// ALTEZZA DELL'ALBERO
int height(bst tree)
{
      if(tree == NULL) 
            return -1; // se il programma lo richiede, modificare con 0
      return max(height(tree->left), height(tree->right)) + 1;
}

// PROFONDITÀ
/*
      Ritorna la profondità del nodo con chiave "value",
      se non esiste ritorna -1.
*/
int depth(bst tree, int value, int dpt)
{
      if(tree == NULL) 
            return -1;
      if(tree->value == value) 
            return dpt;

      if(value <= tree->value)
            return depth(tree->left, value, dpt + 1);
      else
            return depth(tree->right, value, dpt + 1);
}

// RICERCA
/*
      Cerca un nodo con chiave "value", se esiste ritorna il puntatore a quel nodo,
      altrimenti NULL.
      Usata soprattutto come schema per altre funzioni.
*/
bst find(bst tree, int value)
{
      if(tree == NULL || tree->value == value) 
            return tree;

      if(value <= tree->value)
            return find(tree->left, value);
      else
            return find(tree->right, value);
}

/*
      Cerca un nodo con chiave "value", se esiste ritorna la sua profondità,
      altrimenti -1.
*/
int search(bst bt, int value, int dpt)
{
      if(bt == NULL)
            return -1;
      else if(value == bt->value)
            return dpt;
      else if(value < bt->value)
            return search(bt->left, value, ++dpt);
      else
            return search(bt->right, value, ++dpt);
}

// MINIMO
int bst_min(bst tree) // sse l'albero iniziale NON È VUOTO
{
      if(tree->left == NULL)
            return tree->value;
      return bst_min(tree->left);
}

// MASSIMO
int bst_max(bst tree) // sse l'albero iniziale NON È VUOTO
{
      if(tree->right == NULL)
            return tree->value;
      return bst_min(tree->right);
}

// STAMPA NODI A PROFONDITÀ k
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

void print_tree(bst tree, int dpt)
{
      if(tree != NULL)
      {
            printf("%d: %d\n", dpt, tree->value);
            print_tree(tree->left, dpt + 1);
            print_tree(tree->right, dpt + 1);
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
      int N, value;

      bst tree = NULL;

      scanf("%d", &N);
      for(int i = 0; i < N; i++)
      {
            scanf("%d", &value);
            insert_in_bst(&tree, value);
      }

      // DO SOMETHING
      // x = search(tree, value, 0);
      // print_tree(tree, 0);
      
      clean_tree(&tree);
      return 0;
}