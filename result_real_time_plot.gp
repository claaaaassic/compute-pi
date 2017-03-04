set title "Wall-clock time -using clock_gettime()"
set xlabel "N"
set ylabel "Time(sec)"
set grid
set logscale x 10
set term png enhanced
set datafile separator ","
set output "result_real_time_plot.png"
plot [:][:] \
    'result_real_time_plot.csv' using 1:2 smooth csplines title 'Baseline', \
    'result_real_time_plot.csv' using 1:4 smooth csplines title 'OpenMP 2 threads', \
    'result_real_time_plot.csv' using 1:6 smooth csplines title 'OpenMP 4 threads', \
    'result_real_time_plot.csv' using 1:8 smooth csplines title 'AVX', \
    'result_real_time_plot.csv' using 1:10 smooth csplines title 'AVX + Loop unrolling', \
    'result_real_time_plot.csv' using 1:12 smooth csplines title 'Leibniz', \
    'result_real_time_plot.csv' using 1:14 smooth csplines title 'Leibniz + OpenMP with 2 threads', \
    'result_real_time_plot.csv' using 1:16 smooth csplines title 'Leibniz + OpenMP with 4 threads'

set title "Error Rate"
set xlabel "N"
set ylabel "error"
set grid
set logscale x 4
set term png enhanced
set datafile separator ","
set output "error_plot.png"
plot [:][:] \
    'result_real_time_plot.csv' using 1:3 smooth csplines lw 2 title 'Baseline', \
    'result_real_time_plot.csv' using 1:5 smooth csplines lw 2 title 'OpenMP 2 threads', \
    'result_real_time_plot.csv' using 1:7 smooth csplines lw 2 title 'OpenMP 4 threads', \
    'result_real_time_plot.csv' using 1:9 smooth csplines lw 2 title 'AVX', \
    'result_real_time_plot.csv' using 1:11 smooth csplines lw 2 title 'AVX + Loop unrolling', \
    'result_real_time_plot.csv' using 1:13 smooth csplines lw 2 title 'Leibniz', \
    'result_real_time_plot.csv' using 1:15 smooth csplines lw 2 title 'Leibniz + OpenMP with 2 threads', \
    'result_real_time_plot.csv' using 1:17 smooth csplines lw 2 title 'Leibniz + OpenMP with 4 threads'
