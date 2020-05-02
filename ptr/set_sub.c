#include <stdio.h>
#define MAX_SIZE 10

void set_sub(int var, int list[]) {
    var = 10; // .1
    list[0] = 10; // .2
}
int main(void) {
    int var;
    int list[MAX_SIZE];

    var = 0; // var = 0;
    list[0] = 0; // 0번째 배열의 값 = 0;
    set_sub(var, list);
    printf("%d, %d", var, list[0]); // 0, 10 출력

    return 0;
}
