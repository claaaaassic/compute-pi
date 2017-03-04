CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall -fopenmp -mavx
EXECUTABLE = \
	time_test_baseline time_test_openmp_2 time_test_openmp_4 \
	time_test_avx time_test_avxunroll \
	benchmark_clock_gettime benchmark_clock_gettime_cputime

GIT_HOOKS := .git/hooks/pre-commit

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

default: $(GIT_HOOKS) computepi.o
	$(CC) $(CFLAGS) computepi.o time_test.c -DBASELINE -o time_test_baseline
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2 -o time_test_openmp_2
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4 -o time_test_openmp_4
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVX -o time_test_avx
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVXUNROLL -o time_test_avxunroll
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime.c -o benchmark_clock_gettime

benchmark_clock_gettime_cputime: computepi.o
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime_cputime.c -o benchmark_clock_gettime_cputime

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

check: default
	time ./time_test_baseline
	time ./time_test_openmp_2
	time ./time_test_openmp_4
	time ./time_test_avx
	time ./time_test_avxunroll

gencsv: default
	for i in `seq 100 5000 25000`; do \
		printf "%d," $$i;\
		./benchmark_clock_gettime $$i; \
	done > result_clock_gettime.csv	

real_time_plot: default
	for i in `seq 1000 2000 1000000`; do \
		printf "%d," $$i;\
		./benchmark_clock_gettime $$i; \
	done > result_real_time_plot.csv
	gnuplot result_real_time_plot.gp

cpu_time_plot: default benchmark_clock_gettime_cputime
	for i in `seq 1000 10000 1000000`; do \
		printf "%d," $$i;\
		./benchmark_clock_gettime_cputime $$i; \
	done > result_cpu_time_plot.csv
	gnuplot result_cpu_time_plot.gp

plot: cpu_time_plot real_time_plot

clean:
	rm -f $(EXECUTABLE) *.o *.s *.csv
