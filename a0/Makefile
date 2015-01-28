include base.mk

all: my_rec_minmax my_iter_minmax bench_iter_minmax bench_rec_minmax plot.png

plot.png: plot.plt bench_iter_minmax bench_rec_minmax
	./bench_rec_minmax > rec.data
	./bench_iter_minmax > iter.data
	gnuplot plot.plt
my_rec_minmax: driver.cpp minmax.h
	$(CC) $(CFLAGS) -o $@ -DRECURSIVE driver.cpp

my_iter_minmax: driver.cpp minmax.h
	$(CC) $(CFLAGS) -o $@ driver.cpp

bench_rec_minmax: driver.cpp minmax.h
	$(CC) $(CFLAGS) -o $@ -DRECURSIVE -DBENCHMARK driver.cpp

bench_iter_minmax: driver.cpp minmax.h
	$(CC) $(CFLAGS) -o $@ -DBENCHMARK driver.cpp

clean:
	rm -f *.o my_iter_minmax my_rec_minmax bench_rec_minmax bench_iter_minmax plot.png iter.data rec.data
