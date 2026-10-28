#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

#somos grupo 12

CC = gcc -ansi -pedantic
CFLAGS = -Wall -Wextra -pedantic -std=c99 # flags para los warnings
EXE = exercise1 exercise2 exercise3 exercise4 exercise5

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE) *.log
#añadido eliminar los .log

$(EXE) : % : %.o sorting.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o times.o permutations.o

permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

sorting.o : sorting.c sorting.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

 times.o : times.c times.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<
	
exercise1_test:
	@echo Running exercise1
	@./exercise1 -limInf 1 -limSup 5 -numN 10

exercise2_test:
	@echo Running exercise2
	@./exercise2 -size 1 -numP 5

exercise3_test:
	@echo Running exercise3
	@./exercise3 -size 1 -numP 5

exercise4_test:
	@echo Running exercise4
	@./exercise4 -size 1

exercise5_test:
	@echo Running exercise5
	@./exercise5 -num_min 1 -num_max 5 -incr 1 -numP 5 -outputFile exercise5.log

grafica: clean exercise4 exercise5 exercise5_insertsort
	@echo "Generando datos de tiempos para InsertSort..."
	./exercise5_insertsort -num_min 100 -num_max 2000 -incr 100 -numP 500 -outputFile insert.log
	@echo "Generando datos de tiempos para BubbleSort..."
	./exercise5 -num_min 100 -num_max 2000 -incr 100 -numP 500 -outputFile bubble.log
	@echo "Iniciando gnuplot para generar las 3 gráficas..."
	gnuplot tiempos_comparativa.gp
	gnuplot operaciones_insert.gp
	gnuplot operaciones_bubble.gp

#instrucciones para compilar exercise5_insertsort

exercise5_insertsort: exercise5_insertsort.o sorting.o times.o permutations.o
	$(CC) $(CFLAGS) -o exercise5_insertsort exercise5_insertsort.o sorting.o times.o permutations.o

exercise5_insertsort.o: exercise5_insertsort.c
	$(CC) $(CFLAGS) -c $<




exercise4_mergesort: exercise4_mergesort.o sorting.o times.o permutations.o
	$(CC) $(CFLAGS) -o exercise4_mergesort exercise4_mergesort.o sorting.o times.o permutations.o

exercise4_mergesort.o: exercise4_mergesort.c
	$(CC) $(CFLAGS) -c $<

exercise4_mergesort_test:
	make exercise4_mergesort
	./exercise4_mergesort -size 20

exercise5_mergesort: exercise5_mergesort.o sorting.o times.o permutations.o
	$(CC) $(CFLAGS) -o exercise5_mergesort exercise5_mergesort.o sorting.o times.o permutations.o

exercise5_mergesort.o: exercise5_mergesort.c
	$(CC) $(CFLAGS) -c $<

exercise5_mergesort_test:
	make exercise5_mergesort
	./exercise5_mergesort -num_min 3 -num_max 503 -incr 3 -numP 500 -outputFile tiempos_merge.txt

exercise4_quicksort: exercise4_quicksort.o sorting_quicksort.o times.o permutations.o
	$(CC) $(CFLAGS) -o exercise4_quicksort exercise4_quicksort.o sorting_quicksort.o times.o permutations.o

exercise4_quicksort.o: exercise4_quicksort.c
	$(CC) $(CFLAGS) -c $<

sorting_quicksort.o: sorting_quicksort.c
	$(CC) $(CFLAGS) -c $<

exercise4_quicksort_test:
	make exercise4_quicksort
	./exercise4_quicksort -size 20



exercises:
	make all
	@echo running exercises
	@echo ---------running exercise 1------------------
	make exercise1_test
	@echo ------------------running exercise 2------------------
	make exercise2_test
	@echo ------------------running exercise 3------------------
	make exercise3_test
	@echo ------------------running exercise 4------------------
	make exercise4_test
	@echo ------------------running exercise 5------------------
	make exercise5_test



histograma: exercise1
	@echo "Generando datos para el histograma..."
	./exercise1 -limInf 0 -limSup 9 -numN 100000 > histograma.log
	@echo "Creando la gráfica random_num.png..."
	gnuplot histograma.gp

	

# Regla para generar los gráficos y hacer el ajuste con GNUplot
plot_tiempos_merge: tiempos_merge.txt fit_mergesort.gp
	gnuplot fit_mergesort.gp