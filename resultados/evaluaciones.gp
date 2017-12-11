#tiempo
set terminal eps
set output "evaluaciones.eps"
set grid
set xlabel "Rango"
set ylabel "Evaluaciones Distancias"

plot "datos_1.dat" using 1:3 title "1 Pivote" with linespoints, \
"datos_4.dat" using 1:3 title "4 Pivotes" with linespoints, \
"datos_8.dat" using 1:3 title "8 Pivotes" with linespoints, \
"datos_16.dat" using 1:3 title "16 Pivotes" with linespoints, \
"datos_32.dat" using 1:3 title "32 Pivotes" with linespoints

exit
