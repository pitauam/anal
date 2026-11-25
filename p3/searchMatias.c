#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "search.h"
#include "permutations.h"


PDICT init_dictionary(int size, char order);

void free_dictionary(PDICT pdict);

int insert_dictionary(PDICT pdict, int key);

int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys);

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method);

int bin_search(int *table, int F, int L, int key, int *ppos)
{
    int mid, ob = 0;

    if (table == NULL || ppos == NULL || F < 0 || F > L) {
        return ERR;
    }

    *ppos = NOT_FOUND;

    while (F <= L) {
        mid = F + (L - F) / 2;
        ob++;
        if (table[mid] == key) {
            *ppos = mid;
            return ob;
        } else if (key < table[mid]) {
            L = mid - 1;
        } else {
            F = mid + 1;
        }
    }

    return ob;
}

int lin_search(int *table, int F, int L, int key, int *ppos)
{
    int i, ob = 0;

    if (table == NULL || ppos == NULL || F < 0 || F > L) {
        return ERR;
    }   

    *ppos = NOT_FOUND;

    for (i = F; i <= L; i++) {
        ob++;
        if (table[i] == key) {
            *ppos = i;
            return ob;
        }
    }

    return ob;
}

int lin_auto_search(int *table, int F, int L, int key, int *ppos)
{
    int i, temp, ob = 0;

    if (table == NULL || ppos == NULL || F < 0 || F > L) {
        return ERR;
    }

    *ppos = NOT_FOUND;

    for (i = F; i <= L; i++) {
        ob++;
        if (table[i] == key) {
            if (i > F) {
                temp = table[i];
                table[i] = table[i - 1];
                table[i - 1] = temp;
                *ppos = i - 1;
            } else {
                *ppos = i;
            }
            return ob;
        }
    }

    return ob;
}

void uniform_key_generator(int *keys, int n_keys, int max);

void potential_key_generator(int *keys, int n_keys, int max);

void gaussian_key_generator(int *keys, int n_keys, int max);