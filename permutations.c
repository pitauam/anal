/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "permutations.h"

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  if (inf < 0 || sup < inf) {
    return ERR;
  }

  return inf + rand() % (sup - inf + 1);
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int *array = NULL;
  int i = 0;
  int temp = 0;
  int random = 0;

  if (N <= 0) {
    return NULL;
  }
  
  array = (int*)calloc(N, sizeof(int));
  if (!array){
    /*error*/
    return NULL;
  }
  
  for (i = 0; i < N; i++)
  {
    array[i] = i + 1;
  }

  for (i = 0; i < N; i++)
  {
    random = random_num(i + 1,N);
    if (random == ERR){
      free(array);
      return NULL;
    }
    /*intercambiar perm[i] con perm[random_num(i, N)*/
    temp = array[i];
    array[i] = temp;
    array[i] = array[random -1];
    array[random -1] = temp;

  }

  return array;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int i = 0;
  int j = 0;
  int **matrix;
  matrix = NULL;
  if (N <= 0 || n_perms <= 0) {  
    return NULL;
  }

  matrix = (int**)calloc(n_perms, sizeof(int*));
  if (!matrix){
    return NULL;
  }

  for (i = 0; i < n_perms; i++)
  {
    /*
    matrix[i] = (int*)calloc(1, sizeof(int));
    if (!matrix[i]){
      for (j = i; j >= 0; j--)
      {
        free(matrix[j]);
      }
      free(matrix);
      return NULL;
    }*/

    matrix[i] = generate_perm(N);
    if (!matrix[i]){
      for (j = 0; j < i; j++)
      {
        free(matrix[j]);
      }
      free(matrix);
      return NULL;
    }
  }
  return matrix; 
}


