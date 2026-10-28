/**************************************************/
/* Programa: exercise4                            */
/* Authors: Santiago Pita y Matias Cantalejo      */
/*                                                */
/* Program that checks MergeSort                  */
/*                                                */
/* Input: Command Line                            */
/* -size: number of elements of each permutation  */
/* Output: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"
#include "sorting.h"

int main(int argc, char** argv)
{
  int tamano = 0, i, j;
  int ret_merge;
  int* perm = NULL;
  int* perm_merge = NULL;
 
  int segmento_merge[] = {10, 50, 40, 30, 20};
  int ob_seg_mer;
  
  int tabla_un_elemento[] = {42};
  int ob_uno;

  srand(time(NULL));

  if (argc != 3) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -size <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -size : number of elements in the permutation.\n");
    return 0;
  }
  
  printf("Practice number 1, section 4 (MergeSort)\n");
  printf("Done by: Santiago Pita y Matias Cantalejo\n");
  printf("Group: 1261\n\n");

  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      tamano = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong parameter %s\n", argv[i]);
    }
  }

  /* Generate original permutation */
  perm = generate_perm(tamano);
  if (perm == NULL) {
    printf("Error: Out of memory\n");
    exit(-1);
  }

  /* Reservamos memoria para las copias */
  perm_merge = (int*)malloc(tamano * sizeof(int));
  
  if (perm_merge == NULL) {
    printf("Error: Out of memory for copies\n");
    free(perm);
    if(perm_merge) free(perm_merge);
    exit(-1);
  }

  for (j = 0; j < tamano; j++) {
      perm_merge[j] = perm[j];
  }

  /*PRUEBA 1: ORDENACION DE LA TABLA COMPLETA*/
  printf("--- 1. ORDENACION COMPLETA (Tamanio: %d) ---\n", tamano);
  
  ret_merge = MergeSort(perm_merge, 0, tamano - 1);
  if (ret_merge == -1) { 
    printf("Error: Error in MergeSort\n");
    free(perm); free(perm_merge);
    exit(-1);
  }

  printf("MergeSort  -> OB ejecutadas: %d\n", ret_merge);
  for(j = 0; j < tamano; j++) {
    printf("%d ", perm_merge[j]);
  }
  printf("\n\n");

  /*PRUEBA 2: SEGMENTOS QUE NO EMPIEZAN EN 0 (Indices 1 a 3)*/
  printf("--- 2. PRUEBA DE SEGMENTO (Indices 1 a 3) ---\n");
  
  ob_seg_mer = MergeSort(segmento_merge, 1, 3);
  
  printf("Array original: 10 50 40 30 20\n");

  printf("MergeSort  (1 a 3) -> OB: %d | Array: ", ob_seg_mer);
  for(j = 0; j < 5; j++) printf("%d ", segmento_merge[j]);
  printf("\n\n");
  
  
  /*PRUEBA 3: TABLA DE UN SOLO ELEMENTO */
  printf("--- 3. PRUEBA DE UN SOLO ELEMENTO ---\n");

  ob_uno = MergeSort(tabla_un_elemento, 0, 0);
  printf("MergeSort (0 a 0) -> OB: %d | Elemento: %d\n", ob_uno, tabla_un_elemento[0]);

  /* Liberar toda la memoria dinamica */
  free(perm);
  free(perm_merge);

  return 0;
}