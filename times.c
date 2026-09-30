/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include <time.h>
#include "permutations.h"
#include <stdlib.h>


/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{

  double total_time = 0;
  int i = 0;
  clock_t inicio, fin;
  int **array = NULL;
  int obs = 0;
  int max_obs = 0;
  int min_obs = 0;
  int total_obs = 0;

  if (!metodo || n_perms <= 0 || N <= 0 || !ptime){
    return ERR;
  }

  array = generate_permutations(n_perms, N);
  if (!array){
    return ERR;
  }

  inicio = clock();
    
    for (i = 0; i < n_perms; i++)
    {
      obs = metodo(array[i], 0, N - 1);
      
      if (i == 0) {
        min_obs = obs;
        max_obs = obs;
      } else {
        if (obs < min_obs) min_obs = obs;
        if (obs > max_obs) max_obs = obs;
      }
      
      total_obs += obs;
    }
    
  fin = clock();

  /*calcula el tiempo de ejecucion*/
  total_time = (double)(fin - inicio) / CLOCKS_PER_SEC;

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = total_time / n_perms;
  ptime->average_ob = (double)total_obs / n_perms;
  ptime->max_ob = max_obs;
  ptime->min_ob = min_obs;

  if (array){
    for (i = 0; i < n_perms; i++)
    {
      free(array[i]);
    }
    free(array);
  }

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  /* Your code */
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  /* your code */
}


