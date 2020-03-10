//% file: hello_pthread.c
//% cmd: gcc -O3 -Wall -Wextra -o hello_pthread hello_pthread.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* スレッドによって実行される関数 */
void * f(void * args_) {
  (void)args_;
  pthread_t tid = pthread_self();
  for (int i = 0; i < 3; i++) {
    printf("%ld : hello %d\n", tid, i);
    usleep(100);                /* 100 μ秒 = 0.0001 秒休眠 */
  }
  return 0;
}

int main() {
  pthread_t tid[2];
  /* スレッドを2個作る */
  for (int i = 0; i < 2; i++) {
    pthread_create(&tid[i], NULL, f, NULL);
  }
  /* 終了待ち */
  for (int i = 0; i < 2; i++) {
    pthread_join(tid[i], NULL);
  }
  return 0;
}
