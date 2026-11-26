#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "search.h"
#include "permutations.h"

/*valores para las funciones de generar keys*/
#define ALPHA 1.5
#define PI 3.14159265358979323846


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



/*La funci ́on free dictionary liberar ́a la memoria reservada para el diccionario, incluida la tabla de claves y la
propia estructura.*/
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


/*La funci ́on massive insertion dictionary insertar ́a en el diccionario las n keys claves almacenadas en la tabla
keys, mediante n keys llamadas a insert dictionary (una por clave).*/
int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys){

    int i = 0;

    if (!pdict || (pdict->order != NOT_SORTED && pdict->order != SORTED) || pdict->n_data >= pdict->size || !keys || n_keys <= 0 || n_keys > (pdict->size-pdict->n_data)){
        return ERR;
    }

    for (i= 0; i < n_keys; i++)
    {
        if (insert_dictionary(pdict, keys[i]) == ERR){
            return ERR;
        }
    }



    return OK;
}

/*La funci ́on search dictionary buscar ́a la clave en el diccionario apuntado por pdict mediante el m ́etodo
indicado por method. Escribir ́a en *ppos el  ́ındice de la clave encontrada o NOT FOUND si no est ́a; devolver ́a el
n ́umero de operaciones b ́asicas realizadas o ERR si se produce un error*/
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){

    int ret = NOT_FOUND;

    if (!pdict || (pdict->order != NOT_SORTED && pdict->order != SORTED) || pdict->n_data >= pdict->size || !ppos || !method){
        return ERR;
    }

    ret = method(pdict, 0, pdict->n_data, key, ppos);

    if (ret == NOT_FOUND)
    {
        return ERR;
    }
    
    return ret;
}

int bin_search(int *table, int F, int L, int key, int *ppos);

int lin_search(int *table, int F, int L, int key, int *ppos);

int lin_auto_search(int *table, int F, int L, int key, int *ppos);

/*genera claves enteras entre [1, max]*/
void uniform_key_generator(int *keys, int n_keys, int max){
    int i = 0;

    if (!keys || n_keys <= 0 || max <= 0){
        return;
    }

    for (i = 0; i < n_keys; i++){
        keys[i] = 1 + (int)(((double)rand() / ((double)RAND_MAX + 1.0)) * max);
    }
}

/*genera claves con distribucion proporcional a k^(-ALPHA)*/
void potential_key_generator(int *keys, int n_keys, int max){
    int i = 0;
    int k = 0;
    double total = 0.0;
    double r = 0.0;
    double acumulado = 0.0;

    if (!keys || n_keys <= 0 || max <= 0){
        return;
    }

    for (k = 1; k <= max; k++){
        total += pow(k, -ALPHA);
    }

    for (i = 0; i < n_keys; i++){
        r = ((double)rand() / ((double)RAND_MAX + 1.0)) * total;
        acumulado = 0.0;

        for (k = 1; k <= max; k++){
            acumulado += pow(k, -ALPHA);
            if (r < acumulado){
                break;
            }
        }

        keys[i] = k;
    }
}

/*genera claves con distribución de gauss centrada en el punto medio*/
void gaussian_key_generator(int *keys, int n_keys, int max){
    int i = 0;
    double mu = 0.0;
    double sigma = 0.0;
    double u1 = 0.0;
    double u2 = 0.0;
    double z = 0.0;
    double x = 0.0;

    if (!keys || n_keys <= 0 || max <= 0){
        return;
    }

    mu = (max + 1.0) / 2.0;
    sigma = max / 12.0;

    for (i = 0; i < n_keys; i++){
        do{
            u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
            u2 = (double)rand() / ((double)RAND_MAX + 1.0);

            z = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
            x = mu + sigma * z;
        } while (x < 0.5 || x >= max + 0.5);

        keys[i] = (int)floor(x + 0.5);
    }
}