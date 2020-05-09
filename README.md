# CRUD project #

Creating, reading, updating, deleting subject schedules

* main.c : 애플리케이션 구현 
* schedule.c : 원형 함수 정의
* schedule.h : 원형 함수 선언 

## CRUD menu ##

1. create_sche : 과목별 스케줄 생성
2. read_sche : 과목별 스케줄 출력
3. update_sche : 과목별 스케줄 업데이트
4. delete_sche : 과목별 스케줄 삭제
5. update_sches : 과목별 스케줄 업데이트(다수 개)
6. delete_sches : 과목별 스케줄 삭제(다수 개)
7. list_sche : 모든 과목 스케줄 출력
8. search_name : 과목 이름 검색
9. search_major : 과목 전공번호 검색
10. search_code : 과목번호 검색
11. search_diff : 과목별 난이도 검색
12. sort_score : 점수 순으로 과목 스케줄 정렬
13. read_file : 과목 스케줄 데이터 읽어오기
14. read_report : 과목 스케줄 보고서 읽어오기
15. save_file : 과목 스케줄 데이터 저장하기
16. save_report : 과목 스케줄 보고서 저장하기
17. debug records : 디버깅
18. load_file : 과목 스케줄 데이터 가져와서 로딩하기 

## Makefile ##

        CC = gcc
        CFLAGS = -g -Wall
        TARGETS = main
        OBJECTS = main.c schedule.o
        .SUFFIXES = .c .o
        main_debug : $(TARGETS)
        main_debug : DEBUGOPTION = -DDEBUG

        $(TARGETS) : $(OBJECTS)
                $(CC) $(CFLAGS) $(DEBUGOPTION) -o $@ $^

        .c.o :
                $(CC) $(CFLAGS) $(DEBUGOPTION) -c $<

        clean :
                rm *.o $(TARGETS)

Source code 

```C
void s_create(char* n, char* p, int c, int m, char* h,int d,int di,int sc){
    int index = s_first_available();
    schedule[index] = (Sche*)malloc(sizeof(Sche));
    Sche* s = schedule[index];
    strcpy(s->name, n);
    strcpy(s->prof, p);
    s->code = c;
    s->major = m;
    strcpy(s->hw, h);
    s->due = d;
    s->diff = di;
    s->score = sc;
    count++;
}

Sche* s_search_by_name(char* n){
    for(int i=0; i<MAX_SUBJECTS; i++){
        if((schedule[i]!=NULL) && strcmp(schedule[i]->name, n)==0) {
                return schedule[i];
        }
    }
    return NULL;
}

void s_update(Sche* s, char* h,int d,int sc){
    strcpy(s->hw, h);
    s->due = d;
    s->score=sc;
}

void s_delete(Sche* s){
    int i,index;
    for(i=0; i<MAX_SUBJECTS; i++) {
        if(schedule[i]==s) {
                index=i;
                break;
        }
    }
    free(s);
    schedule[index] = NULL;
    count--;
    for(i=index+1;i<MAX_SUBJECTS;i++)
        schedule[i-1]=schedule[i];
}
```
