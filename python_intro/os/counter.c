//% file: counter.c
//% cmd: gcc -O3 -Wall -Wextra -fopenmp -o counter counter.c

#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* counter_t : スレッドセーフなカウンタ(同期が内包されたデータ構造) */
typedef struct {
    pthread_mutex_t m[1]; /* mutexを内包 */
    volatile long x;
} counter_t;

/* counterの初期化 */
void counter_init(counter_t* c)
{
    pthread_mutex_init(c->m, NULL);
    c->x = 0;
}

/* counterに+1 */
void counter_inc(counter_t* c)
{
    pthread_mutex_lock(c->m);
    c->x++;
    pthread_mutex_unlock(c->m);
}

/* counterの値を取り出す */
long counter_get(counter_t* c)
{
    return c->x;
}

int main()
{
    counter_t c[1];
    counter_init(c);
#pragma omp parallel
    {
        for (long i = 0; i < 10000000; i++) {
            counter_inc(c);
        }
    }
    printf("x = %ld\n", counter_get(c));
    return 0;
}
