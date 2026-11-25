#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "search.h"
#include "permutations.h"


/*La funci ́on init dictionary crear ́a un diccionario vac ́ıo (sin datos) y reservar ́a espacio para una tabla de al
menos size posiciones. El argumento size indica la capacidad inicial, y order debe tomar el valor SORTED o
NOT SORTED para indicar si la tabla se mantendr ́a ordenada o desordenada.*/
PDICT init_dictionary(int size, char order){
    /*Si order no es ni NOT_SORTED (0) o SORTED (1), entonces devuelve NULL para evitar escribir en dict-> order algo que no tenga sentido*/
    if (size < 0 || (order != NOT_SORTED && order != SORTED)){
        return NULL;
    }

    PDICT dict = NULL;
    dict = (PDICT)calloc(1, sizeof(DICT));
    if (!dict){
        return NULL;
    }

    dict->size = size;
    dict->n_data = 0;
    dict->order = order;
    dict->table = (int*)calloc(size, sizeof(int));

    if (!dict->table){
        free(dict);
        return NULL;
    }

    return dict;
}

void free_dictionary(PDICT pdict){
    if (!pdict || !pdict->table){
        return;
    }

    free(pdict->table);
    free(pdict);

    return;
}

/*La funci ́on insert dictionary insertar ́a la clave en el diccionario apuntado por pdict. Si el campo order vale
NOT SORTED, a ̃nadir ́a la clave al final de la tabla*/


/*En cambio, si el campo order vale SORTED, la funci ́on insertar ́a la clave en la posici ́on que permita conservar el
orden ascendente de la tabla. Tras a ̃nadirla en la posici ́on U, desplazar ́a hacia la derecha las claves anteriores
que sean mayores que ella. En el pseudoc ́odigo, P es el primer  ́ındice de la tabla:
A = T[U]; j = U - 1;
while (j >= P && T[j] > A)
T[j + 1] = T[j];
j--;
T[j + 1] = A;
Aviso: no es necesario llamar a ning ́un algoritmo de ordenaci ́on; basta con incorporar el c ́odigo anterior a la
funci ́on insert dictionary para mantener ordenadas las claves del diccionario.*/
int insert_dictionary(PDICT pdict, int key){

    int i = 0;
    int ultimo = pdict->n_data -1;
    int j = 0;
    int temp = 0;

    if (!pdict || (pdict->order != NOT_SORTED && pdict->order != SORTED) || pdict->n_data >= pdict->size){
        return ERR;
    }

    if (pdict->order == NOT_SORTED)
    {
        pdict->table[pdict->n_data] = key;
        pdict->n_data++;
    }
    else
    {
        /*si esta vacio hay indices negativos*/
        if (pdict->n_data <= 0)
        {
            pdict->table[pdict->n_data] = key;
            pdict->n_data++;
            return OK;
        }

        i = 0;

        /*avanzo hasta el elemento donde key es mayor o igual que el elemento i*/
        while(key < pdict->table[i] && i < ultimo)
        {
            i++;
        }

        /*i es donde entra el elemento*/
        temp = pdict->table[i];
        pdict->table[i] = key;
        i++;
        pdict->n_data++;

        while(i < ultimo)
        {
            pdict->table[i] = temp;
            temp = pdict->table[i+1];
            i++;
        }

    }

    return OK;
}

int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys);

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method);

int bin_search(int *table, int F, int L, int key, int *ppos);

int lin_search(int *table, int F, int L, int key, int *ppos);

int lin_auto_search(int *table, int F, int L, int key, int *ppos);

void uniform_key_generator(int *keys, int n_keys, int max);

void potential_key_generator(int *keys, int n_keys, int max);

void gaussian_key_generator(int *keys, int n_keys, int max);