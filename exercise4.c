/**************************************************/
/* Programa: exercise4                            */
/* Authors: Santiago Pita y Matias Cantalejo      */
/*                                                */
/* Program that checks InsertSort and BubbleSort  */
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
  int ret_insert, ret_bubble;
  int* perm = NULL;
  int* perm_insert = NULL;
  int* perm_bubble = NULL;
 
  int segmento_insert[] = {10, 50, 40, 30, 20};
  int segmento_bubble[] = {10, 50, 40, 30, 20}; 
  int ob_seg_ins, ob_seg_bub;
  
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
  
  printf("Practice number 1, section 4\n");
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
  perm_insert = (int*)malloc(tamano * sizeof(int));
  perm_bubble = (int*)malloc(tamano * sizeof(int));
  
  if (perm_insert == NULL || perm_bubble == NULL) {
    printf("Error: Out of memory for copies\n");
    free(perm);
    if(perm_insert) free(perm_insert);
    if(perm_bubble) free(perm_bubble);
    exit(-1);
  }

  for (j = 0; j < tamano; j++) {
      perm_insert[j] = perm[j];
      perm_bubble[j] = perm[j];
  }

  /*PRUEBA 1: ORDENACION DE LA TABLA COMPLETA*/
  printf("--- 1. ORDENACION COMPLETA (Tamanio: %d) ---\n", tamano);
  
  ret_insert = InsertSort(perm_insert, 0, tamano - 1);
  if (ret_insert == -1) { /* Usando -1 en lugar de ERR por si acaso */
    printf("Error: Error in InsertSort\n");
    free(perm); free(perm_insert); free(perm_bubble);
    exit(-1);
  }

  ret_bubble = BubbleSort(perm_bubble, 0, tamano - 1);
  if (ret_bubble == -1) {
    printf("Error: Error in BubbleSort\n");
    free(perm); free(perm_insert); free(perm_bubble);
    exit(-1);
  }

  printf("InsertSort -> OB ejecutadas: %d\n", ret_insert);
  for(j = 0; j < tamano; j++) {
    printf("%d ", perm_insert[j]);
  }
  printf("\n\n");

  printf("BubbleSort -> OB ejecutadas: %d\n", ret_bubble);
  for(j = 0; j < tamano; j++) {
    printf("%d ", perm_bubble[j]);
  }
  printf("\n\n");

  /*PRUEBA 2: SEGMENTOS QUE NO EMPIEZAN EN 0*/
  printf("--- 2. PRUEBA DE SEGMENTO (Indices 1 a 3) ---\n");
  
  ob_seg_ins = InsertSort(segmento_insert, 1, 3);
  ob_seg_bub = BubbleSort(segmento_bubble, 1, 3);
  
  printf("Array original: 10 50 40 30 20\n");
  
  printf("InsertSort (1 a 3) -> OB: %d | Array: ", ob_seg_ins);
  for(j = 0; j < 5; j++) printf("%d ", segmento_insert[j]);
  printf("\n");
  
  printf("BubbleSort (1 a 3) -> OB: %d | Array: ", ob_seg_bub);
  for(j = 0; j < 5; j++) printf("%d ", segmento_bubble[j]);
  printf("\n\n");

  /*PRUEBA 3: TABLA DE UN SOLO ELEMENTO */
  printf("--- 3. PRUEBA DE UN SOLO ELEMENTO ---\n");
  
  ob_uno = InsertSort(tabla_un_elemento, 0, 0);
  printf("InsertSort (0 a 0) -> OB: %d | Elemento: %d\n", ob_uno, tabla_un_elemento[0]);

  /* Liberar toda la memoria dinamica */
  free(perm);
  free(perm_insert);
  free(perm_bubble);

  return 0;
}