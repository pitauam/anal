set datafile separator "|"
set terminal pngcairo size 800,600 enhanced font "sans,10"
set output "bubble_operaciones.png"

set title "Análisis de Operaciones Básicas: BubbleSort"
set xlabel "Tamaño de la entrada (n_elems)"
set ylabel "Número de Ejecuciones de la Operación Básica"
set grid
set key left top

plot "bubble.log" using (stringcolumn(2)+0):(stringcolumn(4)+0) with linespoints linewidth 2 linecolor rgb "blue" title "Media", \
     "bubble.log" using (stringcolumn(2)+0):(stringcolumn(5)+0) with lines linewidth 1 linecolor rgb "dark-green" title "Mínimo", \
     "bubble.log" using (stringcolumn(2)+0):(stringcolumn(6)+0) with lines linewidth 1 linecolor rgb "dark-red" title "Máximo"
