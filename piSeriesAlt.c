'''
Codigo para realizar el calculo de pi 
realizado por:
juan angel carrera
juan carlos bajan
jose mariano reyes
'''

#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2
#define N 10000000 // valor de n

int main() {
    double pi = 0.0;

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        // calculo paralelo de pi
        double sum = 0.0;
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        for (long i = thread_id; i < N; i += num_threads) {
            double numerator = (i % 2 == 0) ? 1.0 : -1.0;
            double term = numerator / (2 * i + 1);
            sum += term;
        }

        #pragma omp critical
        pi += sum;
    }

    pi *= 4.0; // x 4 para el resultado final

    printf("Approximation of pi: %.10f\n", pi);
    return 0;
}
