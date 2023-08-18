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

    double sum = 0.0;
    int n = atoi(argv[1]);
    int thread_count = atoi(argv[2]);
    double factor;

    // Establece la política de planificación según las variables de entorno
    omp_sched_t kind;
    int modifier;
    omp_get_schedule(&kind, &modifier);
    omp_set_schedule(kind, modifier);

    double start_time = omp_get_wtime();

    #pragma omp parallel for num_threads(thread_count) reduction(+ : sum) private(factor) schedule(runtime)
    for (int k = 0; k < n; k++)
    {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * k + 1);
    }

    double pi_approx = 4.0 * sum;
    printf("Aproximación de PI: %.15f\n", pi_approx);

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    printf("Tiempo de ejecución: %f segundos\n", elapsed_time);

    return 0;
}
