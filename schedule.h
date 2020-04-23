#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBJECTS 55       // 저장할 수 있는 과목 최대 갯수
// 과목 스케줄  데이터 타입을 정의함
typedef struct schedule{
    char name[20];  // 과목이름
    char prof[20]; // 교수님성함
    int code; //과목 번호
    int major; //전공 번호
    char hw[20]; //해야할 일
    int due; //마감 일수
    int diff; //과목별 난이도
    int score; //과목별 점수 (due+diff=sc)-> sort위함
} Sche;
void input_count(int num); 
int load_file();
// 라이브러리 함수 원형을 선언함
int s_is_available(); // 현재 추가할 수 있는 데이터 공간이 있는가?
int s_first_available(); // 추가할 수 있는 가장 빠른 포인터 배열의 인덱스 찾기
int s_count(); // 현재 저장된 과목의 갯수 가져오기
void s_create(char* n, char* p, int c, int m, char* h, int d,int di,int sc); // 스케줄로 신규 과목  레코드 추가
Sche* s_search_by_name(char* n); // 이름이 일치하는 과목 레코드 포인터 찾기
Sche* s_search_by_major(int m); // 전공번호가 일치하는 과목 레코드 포인터 찾기
Sche* s_search_by_code(int c); // 과목번호가 일치하는 과목 레코드 포인터 찾기
Sche* s_search_by_diff(int di); // 난이도가 일치하는 과목 레코드 포인터 찾기
void s_update(Sche* s, char* h, int d,int sc); // 특정 과목의 해야할일과 마감일,점수  업데이트
void s_delete(Sche* s); // 다 끝난 과목 스케줄삭제
void s_get_all(Sche* a[]); // 과목 스케줄 정보가 들어있는 모든 레코드 포인터의 배열을 만들기
void s_get_all2(Sche* a[]); //과목 스케줄 정보가 들어있는 모든 레코드 포인터의 배열 만들기(for debug)
char* s_to_string(Sche* s); // 특정 과목 레코드의 내용을 문자열로 가져오기
char* s_getname(Sche* s);  // 특정 과목 레코드의 과목이름 가져오기
char* s_getprof(Sche* s); // 특정 과목 레코드의 교수님 성함 가져오기
int s_getcode(Sche* s); // 특정 과목 레코드의 과목번호 가져오기
int s_getmajor(Sche* s); // 특정 과목 레코드의 전공번호 가져오기
char* s_gethw(Sche* s); // 특정 과목 레코드의 해야할일 가져오기
int s_getdue(Sche* s);// 특정 과목 레코드의 마감일수 가져오기
int s_getdiff(Sche* s);// 특정 과목 레코드의 난이도 가져오기
int s_getscore(Sche* s);// 특정 과목 레코드의 점수 가져오기
int s_get_all_by_name(Sche* a[], char* n); // 과목이름과 문자열이 일치하는 모든 스케줄 포인터의 배열 만들기  
int s_get_all_by_major(Sche* a[], int m); // 전공번호와 문자열이 일치하는 모든 스케줄 포인터의 배열 만들기 
int s_get_all_by_code(Sche* a[], int c); // 과목번호와 문자열이 일치하는 모든 스케줄 포인터의 배열 만들기 
int s_get_all_by_diff(Sche* a[], int di); // 난이도와 문자열이 일치하는 모든 스케줄 포인터의 배열 만들기 
void s_init(); // 모든과목 스케줄 제거
char* s_to_string_save(Sche* s); // 특정과목 레코드의 내용을파일저장용 문자열로 가져오기
