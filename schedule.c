#include "schedule.h"
Sche* schedule[MAX_SUBJECTS]; // 과목스케줄데이터 (전역)
int count = 0;

int s_is_available(){
    int i;
    for(i=0; i<MAX_SUBJECTS; i++){
        if(schedule[i]==NULL) return 1;
    }
    return 0;
}

int s_first_available(){
    int i;
    for(i=0; i<MAX_SUBJECTS; i++){
        if(schedule[i]==NULL) return i;
    }
    return -1;
}

int s_count(){
#ifdef DEBUG
    printf("[DEBUG]total schedules %d\n",count);
#endif
    return count;
}

void s_create(char* n, char* p, int c, int m, char* h,int d,int di,int sc){
    int index = s_first_available();
#ifdef DEBUG
    printf("[DEBUG]first available index %d\n",index);
#endif
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
#ifdef DEBUG
    printf("[DEBUG]total %d schedules\n",s_count());
#endif
}

Sche* s_search_by_name(char* n){
    for(int i=0; i<MAX_SUBJECTS; i++){
        if((schedule[i]!=NULL) && strcmp(schedule[i]->name, n)==0) {
#ifdef DEBUG    
		printf("[DEBUG]search_name %s",schedule[i]->name);
#endif
		return schedule[i];
        }
    }
    return NULL;
}

Sche* s_search_by_major(int m){
  for(int i=0;i<MAX_SUBJECTS; i++) {
        if((schedule[i]!=NULL) && ((schedule[i]->major)==m))
                return schedule[i];
   }
   return NULL;
}

Sche* s_search_by_code(int c){
    for(int i=0;i<MAX_SUBJECTS; i++) {
	if((schedule[i]!=NULL) && ((schedule[i]->code)==c))
		return schedule[i];
   }
   return NULL;
}

Sche* s_search_by_diff(int di){
  for(int i=0;i<MAX_SUBJECTS; i++) {
        if((schedule[i]!=NULL) && ((schedule[i]->diff)==di))
                return schedule[i];
   }
   return NULL;
}


void s_update(Sche* s, char* h,int d,int sc){
    strcpy(s->hw, h);
    s->due = d;
    s->score=sc;
#ifdef DEBUG
    printf("[DEBUG]due_score %d %d\n",s->due,s->score);
#endif
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
char* s_to_string(Sche* s){
    static char str[80];
#ifdef DEBUG
    printf("[DEBUG]name_prof %s %s\n",s->name,s->prof);
    printf("[DEBUG]code_major %d %d\n",s->code,s->major);
    printf("[DEBUG]hw_due %s %d\n",s->hw,s->due);
    printf("[DEBUG]diff_score %d %d\n",s->diff,s->score);
#endif
    sprintf(str, "[%s] %s / code num: %d / major num: %d / hw: %s / due days: %d / difficulty: %d / score: %d", s->name, s->prof, s->code, s->major, s->hw, s->due,s->diff,s->score);
    return str;
}

void s_get_all(Sche* a[]){
    int i, c=0;
    for(i=0; i<MAX_SUBJECTS; i++){
#ifdef DEBUG
	printf("[DEBUG]MAX_SUBJECTS %d\n",MAX_SUBJECTS);
#endif
        if(schedule[i]!=NULL){
            a[c]=schedule[i];
            c++;
        }
    }
}
void s_get_all2(Sche* a[]) {
    int i;
    for(i=0;i<MAX_SUBJECTS;i++) {
#ifdef DEBUG
	printf("[DEBUG]MAX_SUBJECTS %d\n",MAX_SUBJECTS);
#endif
	a[i]=schedule[i];
    }
}
char* s_getname(Sche* s){
    return s->name;
}

char* s_getprof(Sche* s){
    return s->prof;
}

int s_getcode(Sche* s){
    return s->code;
}

int s_getmajor(Sche* s){
    return s->major;
}
	
char* s_gethw(Sche* s){
    return s->hw;
}

int s_getdue(Sche* s) {
    return s->due;
}
int s_getdiff(Sche *s) {
#ifdef DEBUG
    printf("[DEBUG]diff %d\n",s->diff);
#endif
    return s->diff;
}
int s_getscore(Sche *s) {
#ifdef DEBUG
    printf("[DEBUG]diff %d\n",s->score);
#endif
    return s->score;
}

int s_get_all_by_name(Sche* a[], char* n){
    // 과목이름과 문자열이 일치하는 모든 레코드 포인터의 배열 만들기    
    int i, c=0;
    for(i=0; i<MAX_SUBJECTS; i++){
#ifdef DEBUG
        printf("[DEBUG]get_name %s\n",schedule[i]->name);
#endif
        if((schedule[i]!=NULL) && strcmp(schedule[i]->name, n)==0){
            a[c]=schedule[i];
            c++;
        }
    }
    return c;
} 

int s_get_all_by_major(Sche* a[], int m){
    // 전공번호와 문자열과 일치하는 모든 레코드 포인터의 배열 만들기 
    int i,c=0;
    for(i=0; i<MAX_SUBJECTS; i++){
        if((schedule[i]!=NULL) && ((schedule[i]->major)== m)){
            a[c]=schedule[i];
            c++;
        }
    }
    return c;
}

int s_get_all_by_code(Sche* a[],int c){
    //과목번호와 문자열이 일치하는 모든 스케줄 포인터의 배열 만들기
    int i,d=0;
    for(i=0;i<MAX_SUBJECTS;i++) {
	if((schedule[i]!=NULL) && ((schedule[i]->code)==c)){
	    a[d]=schedule[i];
            d++;
        }
    }
    return d;
}
int s_get_all_by_diff(Sche* a[],int di) {
    int i,d=0;
    for(i=0;i<MAX_SUBJECTS;i++) {
        if((schedule[i]!=NULL) && ((schedule[i]->diff)==di)){
 	    a[d]=schedule[i];
 	    d++;
	}
   }
   return d;
}
void s_init(){
    // 모든 스케줄 제거    
    int i;
    for(i=0; i<MAX_SUBJECTS; i++){
        if(schedule[i]!=NULL) {
            free(schedule[i]);
        }
        schedule[i] = NULL;
    }
    count = 0;
} 

char* s_to_string_save(Sche* s){
    static char str[80];
#ifdef DEBUG
    printf("[DEBUG]name_prof_code_major %s %s %d %d\n",s->name,s->prof,s->code,s->major);
    printf("[DEBUG]hw_due_diff_score %s %d %d %d\n",s->hw,s->due,s->diff,s->score);
#endif
    sprintf(str, "%s %s %d %d %s %d %d %d", s->name, s->prof, s->code, s->major, s->hw, s->due,s->diff,s->score);
    return str;
}

