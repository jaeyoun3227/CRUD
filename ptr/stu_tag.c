#include <stdio.h>

typedef struct stu_tag { // 구조체 선언
    char name[10];
    int age;
    double gpa;
} std; // 구조체 별칭 선언

int main(void) {
    std std_a = {"kim", 20, 3.0}; // main에 stu_a라는 구조체 선언
    std std_b = {"nam", 21, 3.3}; // main에 stu_b라는 구조체 선언

    return 0;
}
