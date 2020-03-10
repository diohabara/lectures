//% file: hello_omp_for.c
//% cmd: gcc -fopenmp -o hello_omp_for hello_omp_for.c

#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(2) 
  {
    int id = omp_get_thread_num();
    /* 以下のfor文の繰り返し(10回)が2スレッドで分割されて実行(つまり並列実行)される */
#pragma omp for
    for (int i = 0; i < 10; i++) {
      printf("thread %d executes iteration %d\n", id, i);
    }
  }
  return 0;
}
