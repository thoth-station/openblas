#include <stdio.h>
#include "/opt/OpenBLAS/cblas.h"
#include <time.h>
#include <stdlib.h>

// MAINTAINER Courtney Pacheco <cpacheco@redhat.com>
// RedHat Inc License 2018
extern void openblas_set_num_threads(int num_threads);
void openblas_set_num_threads_(int* num_threads){
        openblas_set_num_threads(*num_threads);
};

/***************************************************/
// We're using 10,000 x 10,000 square matrices, so the leading dimension (ld) is 10,000
#define LDA 16000
#define LDB 16000
#define LDC 16000

// Define alpha and beta
#define ALPHA 0.1
#define BETA 0.0

// Define m, n, and k
#define M 16000
#define N 16000
#define K 16000


/***************************************************/
// Fills an array with random numbers
void fill_arr(float *arr, int arr_len){

    for(int i=0; i<arr_len; i++){
        float val = (float)(rand() % 1000);
        arr[i] = val;
    }
    return;
};


/***************************************************/

static float a[LDA * LDA];
static float b[LDB * LDB];
static float c[LDC * LDC];

int main(void){

    openblas_set_num_threads(24);

    // Initialize arrays 'a' and 'b' to random floats
    fill_arr(a, LDA*LDA);
    fill_arr(b, LDB*LDB);

    // Initialize arr 'c' to zeros
    for (int i=0; i<(LDC * LDC); i++){
        c[i] = 0.0;
    }

    // Compute sgemm while getting execution time


    struct timeval start, stop, result;
    double execution_time;
    double execution_time_ms;

    // Start clock
    gettimeofday(&start, NULL);

    cblas_sgemm(CblasColMajor,
                CblasNoTrans,
                CblasNoTrans,
                M,
                N,
                K,
                ALPHA,
                a,
                LDA,
                b,
                LDB,
                BETA,
                c,
                LDC);

    // Stop clock
    gettimeofday(&stop, NULL);

    // Compute execution time
    execution_time = (stop.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    execution_time += (stop.tv_usec - start.tv_usec) / 1000.0;   // us to ms

    execution_time *= (1.0e-3);

    // Compute GFlops
    double num_ops = (2.0 * M * N * K) / (1e9);

    printf("%0.3f sec execution time;  ", execution_time * (1.0));
    printf("%0.3f N operations;  ", num_ops);
    printf("%0.3f GFlops", num_ops / execution_time);
    printf("%s", "\n");

    return 0;
};
