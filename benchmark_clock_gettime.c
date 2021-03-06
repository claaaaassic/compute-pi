#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "computepi.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 25;

    double pi = 1.0;
    double diff = 1.0;
    double error = 1.0;

    // Baseline
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_baseline(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // Baseline error rate
    pi = compute_pi_baseline(N);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);

    // OpenMP with 2 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_openmp(N, 2);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // OpenMP with 2 threads error rate
    pi = compute_pi_openmp(N, 2);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);

    // OpenMP with 4 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_openmp(N, 4);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // OpenMP with 4 threads error rate
    pi = compute_pi_openmp(N, 4);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);

    // AVX SIMD
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_avx(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // AVX SIMD error rate
    pi = compute_pi_avx(N);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);

    // AVX SIMD + Loop unrolling
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_avx_unroll(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // AVX SIMD + Loop unrolling error rate
    pi = compute_pi_avx_unroll(N);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);

    // LEIBNIZ
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_leibniz(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // LEIBNIZ error rate
    pi = compute_pi_leibniz(N);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);

    // LEIBNIZ + OpenMP with 2 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_leibniz_openmp(N, 2);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // LEIBNIZ + OpenMP with 2 threads error rate
    pi = compute_pi_leibniz_openmp(N, 2);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);

    // LEIBNIZ + OpenMP with 4 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_leibniz_openmp(N, 4);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // LEIBNIZ + OpenMP with 4 threads error rate
    pi = compute_pi_leibniz_openmp(N, 4);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf\n", error);

    return 0;
}
