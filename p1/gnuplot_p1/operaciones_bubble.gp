set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'grafica_bubblesort.png'
set datafile separator "|"
set title "BubbleSort: Ejecuciones de la Operación Básica"
set xlabel "Tamaño de entrada (N)"
set ylabel "Número de comparaciones (OB)"
set key top left
set grid
plot "bubble.log" every ::1 using 1:6 with linespoints lw 2 pt 2 title "Máximo de OB", \
     "bubble.log" every ::1 using 1:4 with linespoints lw 2 pt 7 title "Media de OB", \
     "bubble.log" every ::1 using 1:5 with linespoints lw 2 pt 6 title "Mínimo de OB"