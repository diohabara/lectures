//% file: update_x_3.c
//% cmd: gcc -O3 -Wall -Wextra -fopenmp -o update_x_3 update_x_3.c

/* ------- このセルを修正して解答を書け. write your answer here ------- */

#include <assert.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    pthread_mutex_t m[1];
    volatile long x;
} counter_t;

void counterInit(counter_t* c)
{
    pthread_mutex_init(c->m, NULL);
    c->x = 0;
}

void counterInc(counter_t* c)
{
    pthread_mutex_lock(c->m);
    c->x++;
    pthread_mutex_unlock(c->m);
}

long counterGet(counter_t* c)
{
    return c->x;
}

int main()
{
    counter_t c[1];
    counterInit(c);
#pragma omp parallel num_threads(2)
    {
        for (long i = 0; i < 1000000; i++) {
            counterInc(c);
        }
    }
    printf("x = %ld\n", counterGet(c));
    return 0;
}
