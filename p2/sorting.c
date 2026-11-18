/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include <stdlib.h>
#include <stdio.h>


/***************************************************/
/* Function: InsertSort    Date:30/09/26           */
/* Your comment                                    */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
  int i,j,key;
  int count_ob = 0;
  int seguir;

  if(!array || ip < 0 || ip > iu)
  return ERR;

  for (i = ip + 1; i <= iu; i++) {
    key = array[i];
    j = i - 1;
    seguir = 1;
  

       
    while (j >= ip && seguir) {
      count_ob++; 
            
      if (array[j] > key) {            
        array[j + 1] = array[j];
        j--;
      } else {
                
      seguir = 0; 
      }
      }
      array[j + 1] = key;
    }

  return count_ob;  
}


/***************************************************/
/* Function: BubbleSort    Date:07/10/26           */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  int i, j, key;
  int count_ob = 0;
  int seguir;

  if(!array || ip < 0 || ip > iu){
    return ERR;
  }

  i = iu;
  seguir = 1;

  while(i > ip && seguir)
  {
    seguir = 0;

    for(j = ip; j < i; j++)
    {
      count_ob++;
      if(array[j] > array[j+1])
      {
        key = array[j];
        array[j] = array[j+1];
        array[j+1] = key;
        
        seguir = 1;
      }
    }
    
    i--; 
  }
  
  return count_ob;
}


/***************************************************/
/* Function: MergeSort    Date:21/10/26            */
/* Your comment                                    */
/***************************************************/

/*ip: primero, iu: ultimo, im: medio (ult indice de la mitad izq)
ob: comparacion de claves
ordenar de menor a mayor
err si hay un error y numero de ob ejecutadas si no hay error
el recuento debe incluir las llamadas recursivas */
int MergeSort(int* array, int ip, int iu)
{
  int medio = -1;
  int rec_izq = 0;
  int rec_der = 0;
  int rec_merge = 0;

  
  if (!array || ip < 0 || ip > iu){
    return ERR; /*ERR es -1*/
  }

  if (ip == iu){
    return 0;
  }
  

  medio = ip + ((iu-ip) / 2); /*partir*/

  rec_izq = MergeSort(array, ip, medio);
  if (rec_izq == ERR){
    return ERR;
  }

  rec_der = MergeSort(array, medio + 1, iu);
  if (rec_der == ERR){
    return ERR;
  }

  rec_merge = merge(array, ip, iu, medio);
  if (rec_merge == ERR){
    return ERR;
  }

  return rec_izq + rec_der + rec_merge;

}







/***************************************************/
/* Function: merge   (combinar) Date:21/10/26      */
/* Your comment                                    */
/***************************************************/
int merge(int* array, int ip, int iu, int im)
{
  int *array_aux = NULL;
  int i;
  int j;
  int k;
  int count_ob = 0;

  if (!array || ip < 0 || ip > im || im >= iu) {
    return ERR;
  }

  array_aux = (int*)calloc((size_t)iu + 1, sizeof(int));
  if (!array_aux) {
    return ERR;
  }

  i = ip;
  j = im + 1;
  k = ip;
  
  while (i <= im && j <= iu)
  {
    count_ob++;
    if (array[i] < array[j])
    {
      array_aux[k] = array[i];
      i++;
    }
    else
    {
      array_aux[k] = array[j];
      j++;
    }
    k++;
  }

  if (i > im)
  {
    while (j <= iu)
    {
      array_aux[k] = array[j];
      j++;
      k++;
    }
  }
  else if (j > iu)
  {
    while (i <= im)
    {
      array_aux[k] = array[i];
      i++;
      k++;
    }
  }

  for (k = ip; k <= iu; k++) {
    array[k] = array_aux[k];
  }

  free(array_aux);
  return count_ob;
}


/***************************************************/
/* Function: pivot_min                             */
/* Selecciona el primer elemento como pivote       */
/***************************************************/
int pivot_min(int* array, int ip, int iu, int* pos) {
    if (!array || !pos || ip < 0 || ip > iu) return ERR;
    
    *pos = ip;
    return 0; 
}

int partition(int* array, int ip, int iu, int* pos, pfunc_pivot pivot) {
    int k, i, piv_val, temp, ob_pivot = 0, count_ob = 0;

    if (!array || !pos || !pivot || ip < 0 || ip > iu) return ERR;

    ob_pivot = pivot(array, ip, iu, pos);
    if (ob_pivot == ERR) return ERR;
    if (*pos < ip || *pos > iu) return ERR;
    count_ob += ob_pivot;

    piv_val = array[*pos];
    
    temp = array[ip];
    array[ip] = array[*pos];
    array[*pos] = temp;

    k = ip;
    for (i = ip + 1; i <= iu; i++) {
        count_ob++;
        if (array[i] < piv_val) {
            k++;
            temp = array[i];
            array[i] = array[k];
            array[k] = temp;
        }
    }
    
    temp = array[ip];
    array[ip] = array[k];
    array[k] = temp;
    
    *pos = k;
    return count_ob;
}


/***************************************************/
/* Function: QuickSort_min                         */
/* Ordena el array usando el algoritmo QuickSort   */
/***************************************************/
int QuickSort_min(int* array, int ip, int iu) {
    int pos, ob_part, ob_izq, ob_der, count_ob = 0;

    if (!array || ip < 0 || iu < -1) return ERR;
    if (ip >= iu) return 0;

    ob_part = partition(array, ip, iu, &pos, pivot_min);
    if (ob_part == ERR) return ERR;
    count_ob += ob_part;

    ob_izq = QuickSort_min(array, ip, pos - 1);
    if (ob_izq == ERR) return ERR;
    count_ob += ob_izq;

    ob_der = QuickSort_min(array, pos + 1, iu);
    if (ob_der == ERR) return ERR;
    count_ob += ob_der;

    return count_ob;
}
/***************************************************/
/* Function: pivot_median                          */
/* Selecciona la mediana de ip, centro e iu        */
/***************************************************/
int pivot_median(int* array, int ip, int iu, int* pos) {
    int im;
    int count_ob = 0;

    if (!array || !pos || ip < 0 || ip > iu) return ERR;

    im = ip + (iu - ip) / 2;

    count_ob++;
    if (array[ip] < array[im]) {
        count_ob++;
        if (array[im] < array[iu]) {
            *pos = im;
        } else {
            count_ob++;
            if (array[ip] < array[iu]) {
                *pos = iu;
            } else {
                *pos = ip;
            }
        }
    } else {
        count_ob++;
        if (array[ip] < array[iu]) {
            *pos = ip;
        } else {
            count_ob++;
            if (array[im] < array[iu]) {
                *pos = iu;
            } else {
                *pos = im;
            }
        }
    }

    return count_ob;
}

/***************************************************/
/* Function: QuickSort_median                      */
/* QuickSort usando mediana de tres como pivote    */
/***************************************************/
int QuickSort_median(int* array, int ip, int iu) {
    int pos, ob_part, ob_izq, ob_der, count_ob = 0;

    if (!array || ip < 0 || iu < -1) return ERR;
    if (ip >= iu) return 0;

    ob_part = partition(array, ip, iu, &pos, pivot_median);
    if (ob_part == ERR) return ERR;
    count_ob += ob_part;

    ob_izq = QuickSort_median(array, ip, pos - 1);
    if (ob_izq == ERR) return ERR;
    count_ob += ob_izq;

    ob_der = QuickSort_median(array, pos + 1, iu);
    if (ob_der == ERR) return ERR;
    count_ob += ob_der;

    return count_ob;
}

int pivot_mean(int* array, int ip, int iu, int* pos) {
    if (!array || !pos || ip < 0 || ip > iu) return ERR;
    *pos = ip + (iu - ip) / 2;
    return 0;
}

int QuickSort_mean(int* array, int ip, int iu) {
    int pos, ob_part, ob_izq, ob_der, count_ob = 0;

    if (!array || ip < 0 || iu < -1) return ERR;
    if (ip >= iu) return 0;

    ob_part = partition(array, ip, iu, &pos, pivot_mean);
    if (ob_part == ERR) return ERR;
    count_ob += ob_part;

    ob_izq = QuickSort_mean(array, ip, pos - 1);
    if (ob_izq == ERR) return ERR;
    count_ob += ob_izq;

    ob_der = QuickSort_mean(array, pos + 1, iu);
    if (ob_der == ERR) return ERR;
    count_ob += ob_der;

    return count_ob;
}