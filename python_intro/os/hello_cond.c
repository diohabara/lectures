//% file: hello_cond.c
//% cmd: gcc -fopenmp -o hello_cond hello_cond.c

#include <assert.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    volatile long x = 0;
    pthread_mutex_t m[1];
    pthread_cond_t c[1];
    pthread_mutex_init(m, NULL); /* mutex初期化 */
    pthread_cond_init(c, NULL); /* 条件変数初期化 */
#pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        if (id == 0) {
            usleep(100);
            pthread_mutex_lock(m);
            x = 12345;
            pthread_cond_broadcast(c); /* スレッド1が寝てたら起こす */
            pthread_mutex_unlock(m);
        } else {
            pthread_mutex_lock(m);
            while (x == 0) {
                pthread_cond_wait(c, m); /* まだ書かれてなかったら寝る(mは解放する. 起きたときはまた取得している) */
            }
            pthread_mutex_unlock(m);
            printf("x = %ld\n", x);
            assert(x == 12345);
            printf("OK\n");
        }
    }
    return 0;
}
