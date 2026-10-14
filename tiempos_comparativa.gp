set datafile separator "|"
set terminal pngcairo size 800,600 enhanced font "sans,10"
set output "comparativa_tiempos.png"

set title "Comparativa de Tiempos Medios de CPU: InsertSort vs BubbleSort"
set xlabel "Tamaño de la entrada (n_elems)"
set ylabel "Tiempo de CPU (segundos)"
set grid
set key left top

# Usamos 'strcol' para limpiar espacios en blanco y asegurar que lea las columnas 2 y 3
plot "insert.log" using (stringcolumn(2)+0):(stringcolumn(3)+0) with linespoints linewidth 2 linecolor rgb "blue" title "InsertSort (Media)", \
     "bubble.log" using (stringcolumn(2)+0):(stringcolumn(3)+0) with linespoints linewidth 2 linecolor rgb "red" title "BubbleSort (Media)"
