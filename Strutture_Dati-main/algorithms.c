#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b)
{
      int tmp = *a;
      *a = *b;
      *b = tmp;
}

void cyclic_swap(int *a, int *b, int *c)
{
      int tmp = *b;
      *b = *a;
      *a = *c;
      *c = tmp;
}

int min(int a, int b)
{
      return a < b ? a : b;
}

int max(int a, int b)
{
      return a > b ? a : b;
}

int min_3(int a, int b, int c)
{
      if(a < b && b < c) 
            return a;
      else if(b < a && b < c) 
            return b;
      else 
            return c;
}

int max_3(int a, int b, int c)
{
      if(a > b && b > c) 
            return a;
      else if(b > a && b > c) 
            return b;
      else 
            return c;
}

// QSORT COMPARE FUNCTIONS

int int_cmp_increasing(const void *a, const void *b)
{
      int n = *((int *) a);
      int m = *((int *) b);
      return n - m;
}

int int_cmp_decreasing(const void *a, const void *b)
{
      int n = *((int *) a);
      int m = *((int *) b);
      return m - n;
}

int str_cmp_increasing(const void *a, const void *b)
{
    return strcmp(*((char **) a), *((char **) b));
}

int str_cmp_decreasing(const void *a, const void *b)
{
    return - strcmp(*((char **) a), *((char **) b));
}

/*
      Vedere hash_15_oggetti.c per qsort con struct.
*/


// ARRAY DI STRINGHE

int main()	
{
      int len, i;
      char **a;
      scanf("%d", &len);
      a = malloc(len * sizeof(char *));
      
      for(i = 0; i < len; i++)
      {
            a[i] = malloc(128 * sizeof(char));
            scanf("%s", a[i]);
      }

      // DO SOMETHING

      for(i = 0; i < len; i++)
            free(a[i]);
      free(a);
      return 0;
}
