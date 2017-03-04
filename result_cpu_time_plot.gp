set title "CPU time -using clock()"
set xlabel "N"
set ylabel "Time(sec)"
set grid
set logscale x 10
set term png enhanced
set datafile separator ","
set output "result_cpu_time_plot.png"
plot [:][:] \
    'result_cpu_time_plot.csv' using 1:2 with lines title 'Baseline', \
    'result_cpu_time_plot.csv' using 1:3 with lines title 'OpenMP 2 threads', \
    'result_cpu_time_plot.csv' using 1:4 with lines title 'OpenMP 4 threads', \
    'result_cpu_time_plot.csv' using 1:5 with lines title 'AVX', \
    'result_cpu_time_plot.csv' using 1:6 with lines title 'AVX + Loop unrolling'
