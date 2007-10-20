set xlabel 'generation'
set ylabel 'fitness'

set autoscale x
set yrange [0:1]

set term png small size 480,320

set key outside
set key box
set output './logs/20071019-170326.png'
set title 'Unsorted'
set key title 'Legend'
set style data linespoints
plot './logs/20071019-170326' index 0 title 'max', './logs/20071019-170326' index 1 title 'min', './logs/20071019-170326' index 2 title 'avg'
