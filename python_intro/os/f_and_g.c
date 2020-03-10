//% file: f_and_g.c
//% cmd: gcc -O3 -Wall -Wextra -fopenmp -o f_and_g f_and_g.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

void f(int nthreads) {
  /* nthreadsスレッドで実行 */
#pragma omp parallel num_threads(nthreads)
  {
    int id = omp_get_thread_num();
    int nt = omp_get_num_threads();
    printf("%d/%d: f\n", id, nt);
  }
}

void g(int nthreads) {
  /* nthreadsスレッドで実行 */
#pragma omp parallel num_threads(nthreads)
  {
    int id = omp_get_thread_num();
    int nt = omp_get_num_threads();
    printf("%d/%d: g\n", id, nt);
  }
}

int main(int argc, char ** argv) {
  int m = (argc > 1 ? atoi(argv[1]) : 2);
  int n = (argc > 2 ? atoi(argv[2]) : 3);
  /* omp_set_nested(1)を実行しているので, 以降は基本的に指定した数のスレッドが出来る */
  omp_set_nested(1);
  /* 全体としてfをmスレッド, gをnスレッドが実行 */
#pragma omp parallel num_threads(2) 
  {
    int id = omp_get_thread_num();
    if (id == 0) {
      f(m);
    } else if (id == 1) {
      g(n);
    }
  }
  return 0;
}
