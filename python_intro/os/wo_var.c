//% file: wo_var.c
//% cmd: gcc -O3 -Wall -Wextra -fopenmp -o wo_var wo_var.c

#include <assert.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* write-once 変数
   あるスレッドがwo_var_put(v, x);
   あるスレッドがwo_var_get(v);
   とすると確実にxが読み出される.
   つまりgetがput後に行われることを保証する */

typedef struct {
    long val;
    pthread_mutex_t m[1];
    pthread_cond_t c[1];
} wo_var_t;

/* 初期化 */
void wo_var_init(wo_var_t* v)
{
    pthread_mutex_init(v->m, NULL);
    pthread_cond_init(v->c, NULL);
    v->val = 0;
}

/* v に x を書く */
void wo_var_put(wo_var_t* v, long x)
{
    pthread_mutex_lock(v->m);
    v->val = x;
    pthread_cond_broadcast(v->c);
    pthread_mutex_unlock(v->m);
}

/* v を読み出す. ただし put がされるまで待つ */
long wo_var_get(wo_var_t* v)
{
    pthread_mutex_lock(v->m);
    while (v->val == 0) {
        pthread_cond_wait(v->c, v->m);
    }
    pthread_mutex_unlock(v->m);
    return v->val;
}

int main()
{
    wo_var_t v[1];
    wo_var_init(v);
#pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        if (id == 0) {
            usleep(100);
            wo_var_put(v, 12345);
        } else {
            long x = wo_var_get(v);
            printf("x = %ld\n", x);
            assert(x == 12345);
            printf("OK\n");
        }
    }
    return 0;
}
