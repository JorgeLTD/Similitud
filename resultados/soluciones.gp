#tiempo
set terminal eps
set output "soluciones.eps"
set grid
set xlabel "Rango"
set ylabel "Cantidad"

plot "datos_1.dat" using 1:5 title "1 Pivote" with linespoints

exit
