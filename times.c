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

  double time = 0;
  int i = 0;
  clock_t inicio, fin;
  int **array = NULL;

  if (!metodo || n_perms <= 0 || N <= 0 || !ptime){
    return ERR;
  }

  array = generate_permutations(n_perms, N);
  if (!array){
    return ERR;
  }


    inicio = clock();

    for (i = 0 ; i < n_perms-1; i++)
    {
      metodo(array, 0, N-1);
    }
    
    fin = clock();

    free(array);



  /*calcula el tiempo de ejecucion*/
  time = (double)(fin - inicio) / CLOCKS_PER_SEC;

  ptime->N = N;
  ptime.





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


