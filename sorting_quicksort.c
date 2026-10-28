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
/* Function: SelectSort    Date:07/10/26           */
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
/* Function: pivot_min                             */
/* Selecciona el primer elemento como pivote       */
/***************************************************/
int pivot_min(int* array, int ip, int iu, int* pos) {
    if (!array || !pos || ip < 0 || ip > iu) return ERR;
    
    *pos = ip;
    return 0; 
}


int partition(int* array, int ip, int iu, int* pos, pfunc_pivot pivot) {
    int k, i, piv_val, temp, count_ob = 0;

    if (!array || !pos || !pivot || ip < 0 || ip > iu) return ERR;

    if (pivot(array, ip, iu, pos) == ERR) return ERR;

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

    if (!array) return ERR;
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


