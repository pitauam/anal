# =========================================================
# Comparación empírica de las tres variantes de QuickSort
# =========================================================

set terminal pngcairo size 1100,650 enhanced font 'Verdana,10'
set datafile separator '|'
set grid
set key left top box
set fit quiet

quick_min = 'exercise5_quick_min.log'
quick_mean = 'exercise5_quick_mean.log'
quick_median = 'exercise5_quick_median.log'

# ---------------------------------------------------------
# 1. Definición de modelos teóricos (O(n log n)) y Ajustes
# ---------------------------------------------------------
# Operaciones Básicas
ob_min(x) = a_min*x*log(x) + b_min*x + c_min
ob_mean(x) = a_mean*x*log(x) + b_mean*x + c_mean
ob_median(x) = a_median*x*log(x) + b_median*x + c_median

a_min = 1.0; b_min = 1.0; c_min = 1.0
a_mean = 1.0; b_mean = 1.0; c_mean = 1.0
a_median = 1.0; b_median = 1.0; c_median = 1.0

fit ob_min(x) quick_min using 1:4 via a_min, b_min, c_min
fit ob_mean(x) quick_mean using 1:4 via a_mean, b_mean, c_mean
fit ob_median(x) quick_median using 1:4 via a_median, b_median, c_median

# Tiempos de CPU
time_min(x) = d_min*x*log(x) + e_min*x
time_mean(x) = d_mean*x*log(x) + e_mean*x
time_median(x) = d_median*x*log(x) + e_median*x

d_min = 1e-9; e_min = 1e-9
d_mean = 1e-9; e_mean = 1e-9
d_median = 1e-9; e_median = 1e-9

fit time_min(x) quick_min using 1:3 via d_min, e_min
fit time_mean(x) quick_mean using 1:3 via d_mean, e_mean
fit time_median(x) quick_median using 1:3 via d_median, e_median


# ---------------------------------------------------------
# 2. Comparativa de Operaciones Básicas (OB)
# ---------------------------------------------------------
set xlabel 'Tamaño de la permutación (N)'
set ylabel 'Comparaciones (OB)'
set xrange [0:500]
set key outside right top box

set output 'quicksort_ob_comparativa.png'
set title 'QuickSort: comparacion de operaciones basicas'
plot quick_min using 1:4:5:6 with yerrorlines pt 7 lw 1.5 lc rgb 'red' title 'Pivote inicial: media y rango min-max', \
     ob_min(x) with lines lw 2 dt 2 lc rgb 'red' title sprintf('Ajuste inicial: %.2f n ln(n) %+.2f n %+.2f', a_min, b_min, c_min), \
     quick_mean using 1:4:5:6 with yerrorlines pt 5 lw 1.5 lc rgb 'blue' title 'Pivote central: media y rango min-max', \
     ob_mean(x) with lines lw 2 dt 2 lc rgb 'blue' title sprintf('Ajuste central: %.2f n ln(n) %+.2f n %+.2f', a_mean, b_mean, c_mean), \
     quick_median using 1:4:5:6 with yerrorlines pt 9 lw 1.5 lc rgb 'dark-green' title 'Mediana: media y rango min-max', \
     ob_median(x) with lines lw 2 dt 2 lc rgb 'dark-green' title sprintf('Ajuste mediana: %.2f n ln(n) %+.2f n %+.2f', a_median, b_median, c_median)


# ---------------------------------------------------------
# 3. Gráfica Comparativa de Tiempos de CPU
# ---------------------------------------------------------
set output 'quicksort_tiempo_comparativa.png'
set title 'Comparativa QuickSort: Tiempo Medio de CPU'
set ylabel 'Tiempo (segundos)'
set yrange [0:*]
set key outside right top box

plot quick_min using 1:3 with points pt 7 lc rgb 'red' title 'Media: Inicial', \
     time_min(x) with lines lw 1.5 dt 2 lc rgb 'red' title 'Ajuste Inicial', \
     quick_mean using 1:3 with points pt 5 lc rgb 'blue' title 'Media: Central', \
     time_mean(x) with lines lw 1.5 dt 2 lc rgb 'blue' title 'Ajuste Central', \
     quick_median using 1:3 with points pt 9 lc rgb 'green' title 'Media: Mediana', \
     time_median(x) with lines lw 1.5 dt 2 lc rgb 'green' title 'Ajuste Mediana'
