//% file: hello_omp_for_wrong.c
//% cmd: gcc -O3 -Wall -Wextra -fopenmp -o hello_omp_for_wrong hello_omp_for_wrong.c

#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main() {
  /* これはfor文の繰り返し全部(10回)をそれぞれのスレッドが実行するもの */
#pragma omp parallel num_threads(2) 
  {
    int id = omp_get_thread_num();
    for (int i = 0; i < 10; i++) {
      printf("thread %d executes iteration %d\n", id, i);
    }
  }
  return 0;
}
