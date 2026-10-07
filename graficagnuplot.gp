# 1. Configurar el formato de salida (Genera una imagen PNG)
set terminal png size 800,600
set output "histograma.png"

# 2. Títulos y etiquetas de los ejes
set title "Histograma de Frecuencias - random_num"
set xlabel "Valores del Intervalo"
set ylabel "Frecuencia (Número de apariciones)"

# 3. Estilo de las barras (semi-transparente con borde negro)
set style fill solid 0.5 border -1
set boxwidth 0.8
set grid y

# 4. Definir la línea teórica esperada (Equiprobable)
# Ejemplo: si lanzas 10,000 muestras en un rango de 10 números, la media es 1000
frecuencia_teorica = 1000 

# Definimos una función para agrupar los datos en cajas (ancho de barra = 1)
hist(x, width) = width * floor(x / width) + width / 2.0


# 5. Dibujar los datos reales (barras) frente a la teoría (línea discontinua)
plot "histograma.log" using (hist($1, 1)):(1.0) smooth frequency with boxes title "Frecuencia Observada", \
     1000 with lines linewidth 2 linecolor rgb "red" title "Frecuencia Teórica"


