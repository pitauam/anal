set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'random_num.png'

set title "Histograma de Distribución Aleatoria (100000 muestras, Rango 0-9)"
set xlabel "Valor Generado"
set ylabel "Frecuencia Observada"

# Configuración visual de las barras
set boxwidth 0.8 relative
set style fill solid 0.7 border -1
set grid y
set yrange [0:12000] 
set xrange [-1:10]

# Función matemática para agrupar los números de 1 en 1
binwidth = 1
bin(x,width) = width*floor(x/width)

# 'every ::3' se salta las 3 líneas de texto (Practice, Done by, Grupo)
# 'smooth freq' le dice a gnuplot que cuente cuántas veces aparece cada número
plot "histograma.log" every ::3 using (bin($1,binwidth)):(1.0) smooth freq with boxes lc rgb "royalblue" title "Frecuencia real", \
     10000 with lines lw 2 lc rgb "red" title "Frecuencia esperada (10000)"