#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define N 100000000 // Ajusta el valor según tu necesidad

double pi = 0.0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *calculate_pi(void *thread_id) {
    long id = (long)thread_id;
    double sum = 0.0;

    for (long i = id; i < N; i += NUM_THREADS) {
        double numerator = (i % 2 == 0) ? 1.0 : -1.0;
        double term = numerator / (2 * i + 1);
        sum += term;
    }

    pthread_mutex_lock(&mutex);
    pi += sum;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, calculate_pi, (void *)t);
        if (rc) {
            printf("Error creating thread: %d\n", rc);
            return -1;
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    pi *= 4.0; // multiplicamos por 4 para la aproximacion final

    printf("Approximation of pi: %.10f\n", pi);
    return 0;
}