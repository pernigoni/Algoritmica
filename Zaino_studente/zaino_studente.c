#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
      Esame del 13/06/2014 - PIATTAFORMA
*/
// HO FATTO UN ALGO GREEDY (quindi non va troppo bene)

typedef struct _exam
{
      char *id;
      int credits;
      int difficulty;
} exam;

int struct_int_cmp_decreasing(const void *a, const void *b)
{
      exam *n = (exam *) a;
      exam *m = (exam *) b;
      return m->credits - n->credits;
}

int struct_int_cmp_increasing_ifCreditsAreTheSame(const void *a, const void *b)
{
      /*
            A parità di credits ordina in modo crescente su difficulty.
      */
      exam *n = (exam *) a;
      exam *m = (exam *) b;

      if(n->credits == m->credits)
            return n->difficulty - m->difficulty;
      else
            return 0;
}

int struct_str_cmp_increasing_ifDifficultyIsTheSame(const void *a, const void *b)
{     
      /*
            A parità di difficulty ordina in modo alfabetico crescente su id.
      */
      exam *n = (exam *) a;
      exam *m = (exam *) b;

      if(n->difficulty == m->difficulty)
            return strcmp(n->id, m->id);
      else
            return 0;
}

int str_cmp_increasing(const void *a, const void *b)
{
      return strcmp(*((char**) a), *((char**) b));
}

int main()
{
      int k, n;
      scanf("%d %d", &k, &n);
      if(k <= 0 || n <= 0)
            return 0;

      exam *a = malloc(n * sizeof(exam)); // array di esami

      for(int i = 0; i < n; i++)
      {
            char *id = malloc(101 * sizeof(char));
            int credits, difficulty;
            scanf("%s %d %d", id, &credits, &difficulty);
            a[i].id = id;
            a[i].credits = credits;
            a[i].difficulty = difficulty;
      }

      qsort(a, n, sizeof(exam), struct_int_cmp_decreasing);
      qsort(a, n, sizeof(exam), struct_int_cmp_increasing_ifCreditsAreTheSame);
      qsort(a, n, sizeof(exam), struct_str_cmp_increasing_ifDifficultyIsTheSame);

      int sum_credits = 0, j = 0;
      char *res[n];     // array in cui copio il risultato, ha massimo n elementi
      for(int i = 0; i < n; i++)
      {
            if(k >= sum_credits + a[i].credits)
            {
                  sum_credits += a[i].credits;

                  res[j] = malloc(101 * sizeof(char));
                  strcpy(res[j], a[i].id);      
                  j++;
            }
      }

      qsort(res, j, sizeof(char *), str_cmp_increasing);
      for(int i = 0; i < j; i++) // ciclo fino a j perché res non è detto che sia pieno fino a n
      {
            printf("%s\n", res[i]);
            free(res[i]);
      }

      for(int i = 0; i < n; i++)
            free(a[i].id);
      free(a);

      return 0;
}













