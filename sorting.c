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

  
  if (!array || ip > iu){
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


}