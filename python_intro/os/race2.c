//% file: race2.c
//% cmd: gcc -O3 -Wall -Wextra -fopenmp -o race2 race2.c

#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    volatile long x = 0;
#pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        if (id == 0) {
            usleep(100);
            x = 12345;
        } else {
            printf("x = %ld\n", x);
            fflush(stdout);
            assert(x == 12345);
        }
    }
    return 0;
}
