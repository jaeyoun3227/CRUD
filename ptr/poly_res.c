#include <stdio.h>
#define MAX(a,b) (((a) > (b) ? (a) : (b))) // if (a > b) a else b랑 같음.
#define MAX_DEGREE 101

typedef struct {
    int degree; // 차수
    float coef[MAX_DEGREE]; // 계수
} poly;

poly poly_res(poly res_a, poly res_b) {
    poly res_opt; // 결과 값 저장 변수
    int a_pos = 0, b_pos = 0, c_pos = 0; // 배열 인덱스
    int deg_a = res_a->degree;
    int deg_b = res_b->degree;

    res_opt.degree = MAX(res_a->degree, res_b->degree); // 결과 다항식의 차수
    while (a_pos <= res_a->degree && b_pos <= res_b->degree)
    {
        if (deg_a > deg_b) { // a항 > b항이면
            res_opt->coef[c_pos++] = res_a->coef[a_pos++]; // a항 push
            deg_a--;
        } else if (deg_a == deg_b) { a항 = b항이면
            res_opt->coef[c_pos++] = res_a->coef[a_pos++] + res_b->coef[b_pos++]; // 결과 = a + b항
            deg_a--;
            deg_b--;
        } else { // a항 < b항이면
            res_opt->coef[c_pos++] = res_b->coef[b_pos++]; // b항 push
            deg_b--;
        }
    }
}

void print_poly(poly p) {
    for (int i = p->degree; i > 0; i++) {
        printf("%3.1fx^%d + ", p->coef[p->degree - i], i);
    }
    printf("%3.1f \n", p->coef[p.degree]);
}

int main(void) {
    poly a = {2,{3,2,1}}; // 3x^2 + 2x^1 + 1x^0 대입
    poly b = {3,{4,0,2}}; // 4x^2 + 2x^0 대입
    poly res;

    print_poly(a); // 출력
    print_poly(b); // 출력
    res = poly_res(a,b); // 결과 값 연산
    print_poly(res); // 결과 값 출력

    return 0;
}
