#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "search.h"
#include "permutations.h"

/*valores para las funciones de generar keys*/
#define ALPHA 1.5
#define PI 3.14159265358979323846


PDICT init_dictionary(int size, char order);

void free_dictionary(PDICT pdict);

int insert_dictionary(PDICT pdict, int key);

int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys);

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method);

int bin_search(int *table, int F, int L, int key, int *ppos);

int lin_search(int *table, int F, int L, int key, int *ppos);

int lin_auto_search(int *table, int F, int L, int key, int *ppos);

void uniform_key_generator(int *keys, int n_keys, int max);

void potential_key_generator(int *keys, int n_keys, int max);

void gaussian_key_generator(int *keys, int n_keys, int max);