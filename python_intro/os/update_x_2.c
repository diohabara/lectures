//% file: update_x_2.c
//% cmd: gcc -O3 -Wall -Wextra -fopenmp -o update_x_2 update_x_2.c

/* ------- このセルを修正して解答を書け. write your answer here ------- */

#include <assert.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    volatile long x = 0;
#pragma omp parallel num_threads(2)
    {
        for (long i = 0; i < 1000000; i++) {
            x++;
        }
        printf("x = %ld\n", x);
        fflush(stdout);
    }
    return 0;
}
