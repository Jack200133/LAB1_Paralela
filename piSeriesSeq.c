#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <número de términos>\n", argv[0]);
        return 1;
    }

    double factor = 1.0;
    double sum = 0.0;
    int n = atoi(argv[1]);

    for (int k = 0; k < n; k++)
    {
        sum += factor / (2 * k + 1);
        factor = -factor;
    }

    double pi_approx = 4.0 * sum;
    printf("Aproximación de PI: %.15f\n", pi_approx);

    return 0;
}
