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