set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'grafica_tiempos.png'
set datafile separator "|"
set title "Comparativa de Tiempos Medios de CPU"
set xlabel "Tamaño de entrada (N)"
set ylabel "Tiempo de CPU (segundos)"
set key top left
set grid
plot "insert.log" every ::1 using 1:3 with linespoints lw 2 pt 7 title "InsertSort", \
     "bubble.log" every ::1 using 1:3 with linespoints lw 2 pt 5 title "BubbleSort"