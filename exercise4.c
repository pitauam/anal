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


/*funcion para comprobar si el array está ordenado*/
static int is_sorted(int* array, int ip, int iu)
{
  int i;

  for (i = ip + 1; i <= iu; i++) {
    if (array[i - 1] > array[i]) return 0;
  }
  return 1;
}

int main(int argc, char** argv)
{
  int tamano = 0, i, j;
  int ret_insert, ret_bubble, ret_merge;
  int ret_quick, ret_quick_mean, ret_quick_median;
  int* perm = NULL;
  int* perm_insert = NULL;
  int* perm_bubble = NULL;
  int* perm_merge = NULL;
  int* perm_quick = NULL;
  int* perm_quick_mean = NULL;
  int* perm_quick_median = NULL;
 
  int segmento_insert[] = {10, 50, 40, 30, 20};
  int segmento_bubble[] = {10, 50, 40, 30, 20}; 
  int segmento_merge[] = {10, 50, 40, 30, 20};
  int segmento_quick[] = {10, 50, 40, 30, 20};
  int segmento_quick_mean[] = {10, 50, 40, 30, 20};
  int segmento_quick_median[] = {10, 50, 40, 30, 20};
  int ob_seg_ins, ob_seg_bub, ob_seg_merge;
  int ob_seg_quick, ob_seg_quick_mean, ob_seg_quick_median;
  
  int tabla_un_elemento[] = {42};
  int ob_uno;
  int ob_uno_merge, ob_uno_quick, ob_uno_quick_mean, ob_uno_quick_median;
  int tabla_vacia[] = {7, 3, 9};
  int ob_vacio_quick, ob_vacio_quick_mean, ob_vacio_quick_median;
  int tabla_mediana[] = {1, 3, 5, 4, 2};
  int pos_min, pos_mean, pos_mediana;
  int ob_pivot_min, ob_pivot_mean, ob_pivot_mediana;

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
  printf("Group: 12\n\n");

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
  perm_merge = (int*)malloc(tamano * sizeof(int));
  perm_quick = (int*)malloc(tamano * sizeof(int));
  perm_quick_mean = (int*)malloc(tamano * sizeof(int));
  perm_quick_median = (int*)malloc(tamano * sizeof(int));
  
  if (perm_insert == NULL || perm_bubble == NULL || perm_merge == NULL ||
      perm_quick == NULL || perm_quick_mean == NULL || perm_quick_median == NULL) {
    printf("Error: Out of memory for copies\n");
    free(perm);
    if(perm_insert) free(perm_insert);
    if(perm_bubble) free(perm_bubble);
    if(perm_merge) free(perm_merge);
    if(perm_quick) free(perm_quick);
    if(perm_quick_mean) free(perm_quick_mean);
    if(perm_quick_median) free(perm_quick_median);
    exit(-1);
  }

  for (j = 0; j < tamano; j++) {
      perm_insert[j] = perm[j];
      perm_bubble[j] = perm[j];
      perm_merge[j] = perm[j];
      perm_quick[j] = perm[j];
      perm_quick_mean[j] = perm[j];
      perm_quick_median[j] = perm[j];
  }

  /*PRUEBA 1: ORDENACION DE LA TABLA COMPLETA*/
  printf("--- 1. ORDENACION COMPLETA (Tamanio: %d) ---\n", tamano);
  
  ret_insert = InsertSort(perm_insert, 0, tamano - 1);
  if (ret_insert == -1) { /* Usando -1 en lugar de ERR por si acaso */
    printf("Error: Error in InsertSort\n");
    free(perm); free(perm_insert); free(perm_bubble); free(perm_merge);
    free(perm_quick); free(perm_quick_mean); free(perm_quick_median);
    exit(-1);
  }

  ret_bubble = BubbleSort(perm_bubble, 0, tamano - 1);
  if (ret_bubble == -1) {
    printf("Error: Error in BubbleSort\n");
    free(perm); free(perm_insert); free(perm_bubble); free(perm_merge);
    free(perm_quick); free(perm_quick_mean); free(perm_quick_median);
    exit(-1);
  }

  ret_merge = MergeSort(perm_merge, 0, tamano - 1);
  if (ret_merge == ERR || !is_sorted(perm_merge, 0, tamano - 1)) {
    printf("Error: Error in MergeSort\n");
    free(perm); free(perm_insert); free(perm_bubble); free(perm_merge);
    free(perm_quick); free(perm_quick_mean); free(perm_quick_median);
    exit(-1);
  }

  ret_quick = QuickSort_min(perm_quick, 0, tamano - 1);
  if (ret_quick == ERR || !is_sorted(perm_quick, 0, tamano - 1)) {
    printf("Error: Error in QuickSort_min\n");
    free(perm); free(perm_insert); free(perm_bubble); free(perm_merge);
    free(perm_quick); free(perm_quick_mean); free(perm_quick_median);
    exit(-1);
  }

  ret_quick_mean = QuickSort_mean(perm_quick_mean, 0, tamano - 1);
  if (ret_quick_mean == ERR || !is_sorted(perm_quick_mean, 0, tamano - 1)) {
    printf("Error: Error in QuickSort_mean\n");
    free(perm); free(perm_insert); free(perm_bubble); free(perm_merge);
    free(perm_quick); free(perm_quick_mean); free(perm_quick_median);
    exit(-1);
  }

  ret_quick_median = QuickSort_median(perm_quick_median, 0, tamano - 1);
  if (ret_quick_median == ERR || !is_sorted(perm_quick_median, 0, tamano - 1)) {
    printf("Error: Error in QuickSort_median\n");
    free(perm); free(perm_insert); free(perm_bubble); free(perm_merge);
    free(perm_quick); free(perm_quick_mean); free(perm_quick_median);
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

  printf("MergeSort -> OB ejecutadas: %d\n", ret_merge);
  for(j = 0; j < tamano; j++) printf("%d ", perm_merge[j]);
  printf("\n\n");

  printf("QuickSort_min -> OB ejecutadas: %d\n", ret_quick);
  for(j = 0; j < tamano; j++) printf("%d ", perm_quick[j]);
  printf("\n\n");

  printf("QuickSort_mean -> OB ejecutadas: %d\n", ret_quick_mean);
  for(j = 0; j < tamano; j++) printf("%d ", perm_quick_mean[j]);
  printf("\n\n");

  printf("QuickSort_median -> OB ejecutadas: %d\n", ret_quick_median);
  for(j = 0; j < tamano; j++) printf("%d ", perm_quick_median[j]);
  printf("\n\n");

  /*PRUEBA 2: SEGMENTOS QUE NO EMPIEZAN EN 0*/
  printf("--- 2. PRUEBA DE SEGMENTO (Indices 1 a 3) ---\n");
  
  ob_seg_ins = InsertSort(segmento_insert, 1, 3);
  ob_seg_bub = BubbleSort(segmento_bubble, 1, 3);
  ob_seg_merge = MergeSort(segmento_merge, 1, 3);
  ob_seg_quick = QuickSort_min(segmento_quick, 1, 3);
  ob_seg_quick_mean = QuickSort_mean(segmento_quick_mean, 1, 3);
  ob_seg_quick_median = QuickSort_median(segmento_quick_median, 1, 3);
  
  printf("Array original: 10 50 40 30 20\n");
  
  printf("InsertSort (1 a 3) -> OB: %d | Array: ", ob_seg_ins);
  for(j = 0; j < 5; j++) printf("%d ", segmento_insert[j]);
  printf("\n");
  
  printf("BubbleSort (1 a 3) -> OB: %d | Array: ", ob_seg_bub);
  for(j = 0; j < 5; j++) printf("%d ", segmento_bubble[j]);
  printf("\n\n");

  printf("MergeSort (1 a 3) -> OB: %d | Array: ", ob_seg_merge);
  for(j = 0; j < 5; j++) printf("%d ", segmento_merge[j]);
  printf("\n");
  printf("QuickSort_min (1 a 3) -> OB: %d | Array: ", ob_seg_quick);
  for(j = 0; j < 5; j++) printf("%d ", segmento_quick[j]);
  printf("\n");
  printf("QuickSort_mean (1 a 3) -> OB: %d | Array: ", ob_seg_quick_mean);
  for(j = 0; j < 5; j++) printf("%d ", segmento_quick_mean[j]);
  printf("\n");
  printf("QuickSort_median (1 a 3) -> OB: %d | Array: ", ob_seg_quick_median);
  for(j = 0; j < 5; j++) printf("%d ", segmento_quick_median[j]);
  printf("\n\n");

  if (ob_seg_merge == ERR || !is_sorted(segmento_merge, 1, 3) ||
      segmento_merge[0] != 10 || segmento_merge[4] != 20 ||
      ob_seg_quick == ERR || !is_sorted(segmento_quick, 1, 3) ||
      segmento_quick[0] != 10 || segmento_quick[4] != 20 ||
      ob_seg_quick_mean == ERR || !is_sorted(segmento_quick_mean, 1, 3) ||
      segmento_quick_mean[0] != 10 || segmento_quick_mean[4] != 20 ||
      ob_seg_quick_median == ERR || !is_sorted(segmento_quick_median, 1, 3) ||
      segmento_quick_median[0] != 10 || segmento_quick_median[4] != 20) {
    printf("Error: MergeSort or QuickSort failed\n");
    exit(-1);
  }

  /*PRUEBA 3: TABLA DE UN SOLO ELEMENTO */
  printf("--- 3. PRUEBA DE UN SOLO ELEMENTO ---\n");
  
  ob_uno = InsertSort(tabla_un_elemento, 0, 0);
  printf("InsertSort (0 a 0) -> OB: %d | Elemento: %d\n", ob_uno, tabla_un_elemento[0]);

  ob_uno = BubbleSort(tabla_un_elemento, 0, 0);
  printf("BubbleSort (0 a 0) -> OB: %d | Elemento: %d\n", ob_uno, tabla_un_elemento[0]);
  ob_uno_merge = MergeSort(tabla_un_elemento, 0, 0);
  printf("MergeSort (0 a 0) -> OB: %d | Elemento: %d\n", ob_uno_merge, tabla_un_elemento[0]);
  ob_uno_quick = QuickSort_min(tabla_un_elemento, 0, 0);
  printf("QuickSort_min (0 a 0) -> OB: %d | Elemento: %d\n", ob_uno_quick, tabla_un_elemento[0]);
  ob_uno_quick_mean = QuickSort_mean(tabla_un_elemento, 0, 0);
  printf("QuickSort_mean (0 a 0) -> OB: %d | Elemento: %d\n", ob_uno_quick_mean, tabla_un_elemento[0]);
  ob_uno_quick_median = QuickSort_median(tabla_un_elemento, 0, 0);
  printf("QuickSort_median (0 a 0) -> OB: %d | Elemento: %d\n", ob_uno_quick_median, tabla_un_elemento[0]);

  ob_vacio_quick = QuickSort_min(tabla_vacia, 2, 1);
  ob_vacio_quick_mean = QuickSort_mean(tabla_vacia, 2, 1);
  ob_vacio_quick_median = QuickSort_median(tabla_vacia, 2, 1);
  printf("QuickSort_min (segmento vacio 2 a 1) -> OB: %d\n", ob_vacio_quick);
  printf("QuickSort_mean (segmento vacio 2 a 1) -> OB: %d\n", ob_vacio_quick_mean);
  printf("QuickSort_median (segmento vacio 2 a 1) -> OB: %d\n", ob_vacio_quick_median);

  if (ob_uno_merge != 0 || ob_uno_quick != 0 || ob_uno_quick_mean != 0 || ob_uno_quick_median != 0 ||
      ob_vacio_quick != 0 || ob_vacio_quick_mean != 0 || ob_vacio_quick_median != 0 ||
      tabla_vacia[0] != 7 || tabla_vacia[1] != 3 || tabla_vacia[2] != 9) {
    printf("Error: QuickSort failed with 0 or 1 element(s)\n");
    exit(-1);
  }

  ob_pivot_min = pivot_min(tabla_mediana, 0, 4, &pos_min);
  ob_pivot_mean = pivot_mean(tabla_mediana, 0, 4, &pos_mean);
  ob_pivot_mediana = pivot_median(tabla_mediana, 0, 4, &pos_mediana);
  if (ob_pivot_min != 0 || pos_min != 0 || ob_pivot_mean != 0 || pos_mean != 2 ||
      ob_pivot_mediana != 3 || pos_mediana != 4) {
    printf("Error: pivot selector failed\n");
    exit(-1);
  }
  printf("pivot_min (0 a 4) -> OB: %d | pos: %d\n", ob_pivot_min, pos_min);
  printf("pivot_mean (0 a 4) -> OB: %d | pos: %d\n", ob_pivot_mean, pos_mean);
  printf("pivot_median (0 a 4) -> OB: %d | pos: %d\n", ob_pivot_mediana, pos_mediana);

  /* Liberar toda la memoria dinamica */
  free(perm);
  free(perm_insert);
  free(perm_bubble);
  free(perm_merge);
  free(perm_quick);
  free(perm_quick_mean);
  free(perm_quick_median);

  return 0;
}
