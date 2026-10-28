# ==========================================
# Script de GNUplot para MergeSort (Ajustes)
# ==========================================

# 1. Configurar el separador como la barra vertical '|'
set datafile separator "|"

# 2. Definir el modelo teórico para MergeSort: O(n log2 n)
f(x) = a * x * log(x) / log(2) + b
g(x) = c * x * log(x) / log(2) + d

file_data = "tiempos_merge.txt"

# ------------------------------------------
# 3. AJUSTE Y GRÁFICA DE OPERACIONES BÁSICAS (OB)
# ------------------------------------------
# Columna 1: N (tamaño) | Columna 4: average_ob
print "--- Realizando ajuste para Operaciones Básicas ---"
fit f(x) file_data using 1:4 via a, b

set terminal pngcairo enhanced font "Verdana,10" size 800,600
set output "grafica_ob_mergesort.png"

set title "MergeSort: Operaciones Básicas (Empírico vs Teórico O(n log n))"
set xlabel "Tamaño de la tabla (N)"
set ylabel "Número de Operaciones Básicas (OB)"
set grid
set key left top

plot file_data using 1:4 title "Datos Medidos (Media OB)" with points pt 7 lc rgb "blue", \
     f(x) title sprintf("Ajuste: %.4f * n log2(n) + %.4f", a, b) with lines lw 2 lc rgb "red"

# ------------------------------------------
# 4. AJUSTE Y GRÁFICA DE TIEMPO DE CPU
# ------------------------------------------
# Columna 1: N (tamaño) | Columna 3: time
print "--- Realizando ajuste para Tiempo de CPU ---"
fit g(x) file_data using 1:3 via c, d

set output "grafica_tiempo_mergesort.png"

set title "MergeSort: Tiempo de CPU (Empírico vs Teórico O(n log n))"
set xlabel "Tamaño de la tabla (N)"
set ylabel "Tiempo de CPU (segundos)"
set grid
set key left top

plot file_data using 1:3 title "Datos Medidos (Tiempo CPU)" with points pt 7 lc rgb "web-green", \
     g(x) title sprintf("Ajuste: %.4e * n log2(n) + %.4e", c, d) with lines lw 2 lc rgb "dark-orange"

print "¡Gráficas generadas con éxito: grafica_ob_mergesort.png y grafica_tiempo_mergesort.png!"