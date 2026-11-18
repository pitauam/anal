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
#include <stdio.h> /*para fopen*/

/***************************************************/
/* Function: average_sorting_time Date:   23/09/26 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  
  if (!metodo || n_perms <= 0 || N <= 0 || !ptime){
    return ERR;
  }

  int i = 0;
  int j = 0;
  clock_t inicio, fin;
  int **array = NULL;
  int obs = 0;
  int max_obs = 0;
  int min_obs = 0;
  long total_obs = 0;
  double total_time = 0.0;


  array = generate_permutations(n_perms, N);
  if (!array){
    return ERR;
  }

  for (i = 0; i < n_perms; i++) {

    inicio = clock();
    obs = metodo(array[i], 0, N - 1);
    fin = clock();

    if (obs == ERR){
      for (j = 0; j < n_perms; j++)
      {
        free(array[j]);
      } 

      free(array);

      return ERR;
    }

    total_time += (double)(fin - inicio) / CLOCKS_PER_SEC; /*casting para que devuelva todo*/

    if (i == 0)
    {
      min_obs = obs;
      max_obs = obs;
    }
    else
    {
      if (obs < min_obs)
      {
        min_obs = obs;
      }

      if (obs > max_obs)
      {
        max_obs = obs;
      }
    }
    total_obs += obs;
  }

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = total_time / n_perms;
  ptime->average_ob = (double)total_obs / n_perms;
  ptime->max_ob = max_obs;
  ptime->min_ob = min_obs;

  for (i = 0; i < n_perms; i++)
  {
    free(array[i]);
  }
  
  free(array);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:  7/10/26 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  if (!method || !file || num_min <= 0 || num_max <= 0 || incr <= 0 || n_perms <= 0 || num_min > num_max){
    return ERR;
  }

  int n_times = 0;
  int current_N = 0;
  int i = 0;
  PTIME_AA table = NULL;
  short status = OK;


  n_times = ((num_max - num_min) / incr) + 1;

  table = (PTIME_AA)calloc(n_times, sizeof(TIME_AA));
  if (!table){
    return ERR;
  }

  current_N = num_min;

  for (i = 0; current_N <= num_max; i++)
  {
    status = average_sorting_time(method, n_perms, current_N, &table[i]);
    if (status == ERR)
    {
      free(table);

      return ERR;
    }
    current_N += incr;
  }

  status = save_time_table(file, table, n_times);
  
  free(table);

  return status;
}

  








/***************************************************/
/* Function: save_time_table Date:   7/10/26       */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  if (!file || !ptime || n_times <= 0){
    return ERR;
  }

  int i = 0;

  /*una fila por tamaño, 6 columnas,*/
  FILE *f = NULL;
  f = fopen(file, "w");
  if (!f){
    return ERR;
  }

  fprintf(f, "# N     |  n_elems  |     time     |     average_ob     |     min_ob     |     max_ob\n");
  for (i = 0; i < n_times; i++)
  {
    fprintf(f, "  %-5d | %-9d | %-12.6f | %-18.2f | %-12d | %-12d\n", ptime[i].N, ptime[i].n_elems, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob);
  }


  fclose(f);

  return OK;
}
