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
/* Function: InsertSort    Date:                   */
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
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  /* Your code */
}






