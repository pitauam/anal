/***********************************************************/
/* Program: exercise5                  Date:               */
/* Authors:                                                */
/*                                                         */
/* Programa that writes in a file                          */
/* the average times of the algorithm                      */
/* of sorting algorithms                                    */
/*                                                         */
/* Input: Command Line                                     */
/* -num_min: lowest number of table elements               */
/* -num_max: highest number of table elements              */
/* -incr: increment\n                                      */
/* -numP: number of permutations to average                */
/* -outputFile: Output file name                           */
/* Output: -1 in case of error                              */
/* 0 otherwise                                            */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sorting.h"
#include "times.h"

/*funcion auxiliar para que los .log generados se distingan*/
static void set_output_name(char* output, const char* base, const char* suffix)
{
  size_t length;

  strcpy(output, base);
  length = strlen(output);
  if (length >= 4 && strcmp(output + length - 4, ".log") == 0) {
    output[length - 4] = '\0';
    strcat(output, "_");
    strcat(output, suffix);
    strcat(output, ".log");
  } else {
    strcat(output, "_");
    strcat(output, suffix);
  }
}

int main(int argc, char** argv)
{
  int i, num_min, num_max, incr, n_perms;
  char nombre[256];
  char nombre_insert[300], nombre_merge[300];
  char nombre_min[300], nombre_mean[300], nombre_median[300];
  short ret;

  srand(time(NULL));

  if (argc != 11) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -numP <int> -outputFile <string> \n");
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, "-num_min: lowest number of table elements\n");
    fprintf(stderr, "-num_max: highest number of table elements\n");
    fprintf(stderr, "-incr: increment\n");
    fprintf(stderr, "-numP: number of permutations to average\n");
    fprintf(stderr, "-outputFile: Output file name\n");
    exit(-1);
  }

  printf("Practice number 1, section 5\n");
  printf("Done by: Santiago Pita y Matias Cantalejo\n");
  printf("Group: 12\n");
  
  /* check command line */
  for(i = 1; i < argc ; i++) {
    if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-outputFile") == 0) {
      strcpy(nombre, argv[++i]);
    } else {
      fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
    }
  }

  /* compute times */
  set_output_name(nombre_insert, nombre, "insert");
  set_output_name(nombre_merge, nombre, "merge");
  set_output_name(nombre_min, nombre, "quick_min");
  set_output_name(nombre_mean, nombre, "quick_mean");
  set_output_name(nombre_median, nombre, "quick_median");

  ret = generate_sorting_times(BubbleSort, nombre, num_min, num_max, incr, n_perms);
  if (ret == ERR) { /* ERR_TIME should be a negative number */
    printf("Error in function generate_sorting_times (BubbleSort)\n");
    exit(-1);
  }

  ret = generate_sorting_times(InsertSort, nombre_insert, num_min, num_max, incr, n_perms);
  if (ret == ERR) {
    printf("Error in function generate_sorting_times (InsertSort)\n");
    exit(-1);
  }

  ret = generate_sorting_times(MergeSort, nombre_merge, num_min, num_max, incr, n_perms);
  if (ret == ERR) {
    printf("Error in function generate_sorting_times (MergeSort)\n");
    exit(-1);
  }

  ret = generate_sorting_times(QuickSort_min, nombre_min, num_min, num_max, incr, n_perms);
  if (ret == ERR) {
    printf("Error in function generate_sorting_times (QuickSort_min)\n");
    exit(-1);
  }

  ret = generate_sorting_times(QuickSort_mean, nombre_mean, num_min, num_max, incr, n_perms);
  if (ret == ERR) {
    printf("Error in function generate_sorting_times (QuickSort_mean)\n");
    exit(-1);
  }

  ret = generate_sorting_times(QuickSort_median, nombre_median, num_min, num_max, incr, n_perms);
  if (ret == ERR) {
    printf("Error in function generate_sorting_times (QuickSort_median)\n");
    exit(-1);
  }
  printf("Correct output \n");

  return 0;
}

