/* 以下の指示は消してはいけない(以降も同様) */
/* ------- このセルを修正して解答を書け. write your answer here ------- */

//% file: hello_world.c
//% cmd: gcc -O3 -Wall -Wextra -o hello_world hello_world.c

#include <stdio.h>
int main() {
    for (int i = 0; i < 3; ++i) {
        printf("hello world\n");
    }
    return 0;
}