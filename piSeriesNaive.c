#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Uso: %s <número de términos> <número de hilos>\n", argv[0]);
        return 1;
    }

    double factor = 1.0;
    double sum = 0.0;
    // Puedes ajustar n según sea necesario
    int n = atoi(argv[1]);
    // Puedes ajustar la cantidad de hilos según sea necesario
    int thread_count = atoi(argv[2]);

#pragma omp parallel for num_threads(thread_count) reduction(+ : sum)
    for (int k = 0; k < n; k++)
    {
        sum += factor / (2 * k + 1);
        factor = -factor;
    }

    double pi_approx = 4.0 * sum;
    printf("Aproximación de PI: %.15f\n", pi_approx);

    return 0;
}
