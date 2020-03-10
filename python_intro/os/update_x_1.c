//% file: update_x_1.c
//% cmd: gcc -O3 -Wall -Wextra -fopenmp -o update_x_1 update_x_1.c


#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include <pthread.h>

int main() {
  volatile long x = 0;
  for (long i = 0; i < 1000000; i++) {
    x++;
  }
  printf("x = %ld\n", x); fflush(stdout);
  return 0;
}
