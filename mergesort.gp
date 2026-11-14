# ==========================================================
# Script de GNUPlot para análisis de MergeSort
# Archivo de entrada: tiempos_merge.txt
# ==========================================================

# Configuración general de salida
set terminal pngcairo size 900,600 enhanced font 'Verdana,10'
set datafile separator "|" # El delimitador en el txt es el pipe '|'
set grid
set key top left box

# ==========================================================
# 1. Gráfica de Operaciones Básicas (OB)
# ==========================================================
set output 'mergesort_ob.png'
set title "MergeSort: Operaciones Básicas vs Tamaño del Array (N)"
set xlabel "Tamaño de la permutación (N)"
set ylabel "Número de Operaciones Básicas (OB)"

# Modelo teórico para MergeSort: O(n log n)
# NOTA: log(x) en gnuplot es el logaritmo neperiano (ln).
# La base del logaritmo es absorbida por la constante 'a'.
f(x) = a * x * log(x) + b * x + c

# Valores iniciales para que el algoritmo de ajuste (Levenberg-Marquardt) converja
a = 1.0; b = 1.0; c = 1.0 

# Ajustar el modelo usando los datos de OB Medio (N en col 1, Medio en col 4)
fit f(x) 'tiempos_merge.txt' using 1:4 via a, b, c

# Dibujar la gráfica
plot 'tiempos_merge.txt' using 1:5 with linespoints pt 7 lc rgb "blue" title "Mínimo OB", \
     'tiempos_merge.txt' using 1:6 with linespoints pt 7 lc rgb "red" title "Máximo OB", \
     'tiempos_merge.txt' using 1:4 with linespoints pt 7 lc rgb "forest-green" lw 2 title "Medio OB", \
     f(x) lc rgb "black" lw 2 dashtype 2 title sprintf("Ajuste teórico: f(n) = %.2f*n*ln(n) %+.2f*n %+.2f", a, b, c)

# ==========================================================
# 2. Gráfica de Tiempos de CPU
# ==========================================================
set output 'mergesort_tiempo.png'
set title "MergeSort: Tiempo de CPU vs Tamaño del Array (N)"
set ylabel "Tiempo de CPU (segundos)"
set key top left

# Modelo teórico para el Tiempo
g(x) = d * x * log(x) + e * x + h

# Valores iniciales muy pequeños (los tiempos están cerca de 0)
d = 1e-6; e = 1e-6; h = 1e-6 

# Ajustar el modelo usando los datos de tiempo (N en col 1, Tiempo en col 3)
fit g(x) 'tiempos_merge.txt' using 1:3 via d, e, h

# Dibujar la gráfica (usamos notación científica %e para el tiempo porque es muy pequeño)
plot 'tiempos_merge.txt' using 1:3 with linespoints pt 7 lc rgb "purple" lw 2 title "Tiempo de CPU", \
     g(x) lc rgb "black" lw 2 dashtype 2 title sprintf("Ajuste teórico: t(n) = %.2e*n*ln(n) %+.2e*n", d, e)
