//% file: hello_omp.c
//% cmd: gcc -fopenmp -o hello_omp hello_omp.c

#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main() {
  /* 以下の { ... } を実行するスレッドを2個作る */
#pragma omp parallel num_threads(2) 
  {
    long id = omp_get_thread_num(); /*  0 または 1 の ID */
    long n = (id + 1) * 5;
    long slp_us = 1000 / n;
    for (int i = 0; i < n; i++) {
      printf("%ld : hello %d\n", id, i);
      usleep(slp_us);                /* 100 μ秒 = 0.0001 秒休眠 */
    }
  }
  return 0;
}
