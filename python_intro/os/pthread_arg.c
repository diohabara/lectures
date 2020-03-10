//% file: pthread_arg.c
//% cmd: gcc -O3 -Wall -Wextra -o pthread_arg pthread_arg.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* スレッドに渡す情報を詰める構造体 */
typedef struct {
  pthread_t tid;
  long id;
  long n;                       /* 繰り返し数 */
  long slp_us;                     /* 繰り返し間のsleep時間 */
} thread_arg_t;

/* スレッドに実行される関数
   引数は void* 1つと決まっているが実際には thread_arg_tへのポインタ */
void * f(void * arg_) {
  thread_arg_t * arg = arg_;
  long id = arg->id;
  long n = arg->n;
  long slp_us = arg->slp_us;
  for (int i = 0; i < n; i++) {
    printf("%ld : hello %d\n", id, i);
    usleep(slp_us);                /* 100 μ秒 = 0.0001 秒休眠 */
  }
  return 0;
}

int main() {
  thread_arg_t args[2];
  /* スレッドを2個作る */
  for (int i = 0; i < 2; i++) {
    /* スレッドに渡す構造体に情報を詰める */
    args[i].id = i;
    args[i].n = (i + 1) * 5;
    args[i].slp_us = 1000 / args[i].n;
    pthread_create(&args[i].tid, NULL, f, &args[i]);
  }
  /* 終了待ち */
  for (int i = 0; i < 2; i++) {
    pthread_join(args[i].tid, NULL);
  }
  return 0;
}
