set terminal png size 1024,768 enhanced font 'Sans,10'
set output 'plot.png'
f(x) = (3./2.) * x - 2
plot 'iter.data' using 1:4 title 'Iterative' w lines ls 1, \
     'rec.data' using 1:4 title 'Recursive' w lines ls 2, \
     f(x) title '(3/2)N - 2' w lines ls 3
