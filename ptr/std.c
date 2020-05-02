#include <stdio.h>

typedef struct stu_tag { // 구조체 선언
    char name[10];
    int age;
    double gpa;
} std; // 구조체 별칭 선언

int main(void) {
    std *std_p;
    std_p = (std *)malloc(sizeof(std)); // 동적 메모리 할당
    if (std_p == NULL) { // 만약 NULL이면
        fprintf(stderr, "no available memory"); // 메모리 할당 불가
        exit(1);
    }
    strcpy(std_p->name, "nam"); // .이나 -> 사용
    std_p->age = 20;
    std_p->gpa = 3.3;

    free(); // 메모리 할당 후 반환
    return 0;
}
