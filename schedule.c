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
void input_count(int num){
    count = num;
}

int s_count(){
#ifdef DEBUG
    printf("%d",count);
#endif
    return count;
}

void s_create(char* n, char* p, int c, int m, char* h,int d,int di,int sc){
    int index = s_first_available();
#ifdef DEBUG
    printf("%d",index);
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
}

Sche* s_search_by_name(char* n){
    int size=s_count();
    for(int i=0; i<size; i++){
        if((schedule[i]!=NULL) && strcmp(schedule[i]->name, n)==0) {
#ifdef DEBUG    
		printf("%s",schedule[i]->name);
#endif
		return schedule[i];
        }
    }
    return NULL;
}

Sche* s_search_by_major(int m){
    int size=s_count();
    char s1[10];
    sprintf(s1,"%d",m);
    int i;
    char s2[20];
    for(i=0; i<size; i++) {
        sprintf(s2,"%d",schedule[i]->major);
	if((schedule[i]!=NULL) && strcmp(s2,s1)==0)
		 return schedule[i];
   }
   return NULL;
}

Sche* s_search_by_code(int c){
    int size=s_count();
    char s1[10];
    sprintf(s1,"%d",c);
    int i;
    char s2[20];
    for(i=0;i<size; i++) {
        sprintf(s2,"%d",schedule[i]->code);
	if((schedule[i]!=NULL) && strcmp(s2,s1)==0) 
		return schedule[i];
   }
   return NULL;
}

Sche* s_search_by_diff(int di){
    int size=s_count();
    char s1[10];
    sprintf(s1,"%d",di);
    int i;
    char s2[20];
    for(i=0;i<size; i++) {
        sprintf(s2,"%d",schedule[i]->diff);
        if((schedule[i]!=NULL) && strcmp(s2,s1)==0)
                return schedule[i];
   }
   return NULL;
}

void s_update(Sche* s, char* h,int d,int sc){
    strcpy(s->hw, h);
    s->due = d;
    s->score=sc;
#ifdef DEBUG
    printf("%d %d",s->due,s->score);
#endif
}

void s_delete(Sche* s){
    int size=s_count();
    int i,j;
    for(i=0; i<size; i++) {
        if(schedule[i]==s) {
	   for(j=i;j<size-1;j++) {
		schedule[j]=schedule[j+1];
	   }
        }
    }
    count--;
}
char* s_to_string(Sche* s){
    static char str[80];
#ifdef DEBUG
    printf("%s %s\n",s->name,s->prof);
    printf("%d %d\n",s->code,s->major);
    printf("%s %d\n",s->hw,s->due);
    printf("%d %d\n",s->diff,s->score);
#endif
    sprintf(str, "[%s] %s / code num: %d / major num: %d / hw: %s / due days: %d / difficulty: %d / score: %d", s->name, s->prof, s->code, s->major, s->hw, s->due,s->diff,s->score);
    return str;
}

void s_get_all(Sche* a[]){
    int size=s_count();
    int i, c=0;
    for(i=0; i<size; i++){
#ifdef DEBUG
	printf("%d",size);
#endif
        if(schedule[i]!=NULL){
            a[c]=schedule[i];
            c++;
        }
    }
}
void s_get_all2(Sche* a[]) {
    int size=s_count();
    int i;
    for(i=0;i<size;i++) {
#ifdef DEBUG
	printf("%d",size);
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
    printf("%d",s->diff);
#endif
    return s->diff;
}
int s_getscore(Sche *s) {
#ifdef DEBUG
    printf("%d",s->score);
#endif
    return s->score;
}

int s_get_all_by_name(Sche* a[], char* n){
    int size=s_count();
    // 과목이름과 문자열이 일치하는 모든 레코드 포인터의 배열 만들기    
    int i, c=0;
    for(i=0; i<size; i++){
#ifdef DEBUG
        printf("%s",schedule[i]->name);
#endif
        if((schedule[i]!=NULL) && strcmp(schedule[i]->name, n)==0){
            a[c]=schedule[i];
            c++;
        }
    }
    return c;
} 

int s_get_all_by_major(Sche* a[], int m){
    int size=s_count();
    // 전공번호와 문자열과 일치하는 모든 레코드 포인터의 배열 만들기 
    char s1[10];
    int i, c=0;
    char s2[20]; 
    sprintf(s1,"%d",m);
    for(i=0; i<size; i++){
        sprintf(s2,"%d",schedule[i]->major);
        if((schedule[i]!=NULL) && strcmp(s2, s1)==0){
            a[c]=schedule[i];
            c++;
        }
    }
    return c;
}

int s_get_all_by_code(Sche* a[],int c){
    int size=s_count();
    //과목번호와 문자열이 일치하는 모든 스케줄 포인터의 배열 만들기
    char s1[10];
    int i,d=0;
    char s2[20];
    sprintf(s1,"%d",c);
    for(i=0;i<size;i++) {
        sprintf(s2,"%d",schedule[i]->code);
	if((schedule[i]!=NULL) && strcmp(s2,s1)==0){
	    a[d]=schedule[i];
            d++;
        }
    }
    return d;
}
int s_get_all_by_diff(Sche* a[],int di) {
   int size=s_count();
   char s1[10];
   int i,d=0;
   char s2[20];
   sprintf(s1,"%d",di);
   for(i=0;i<size;i++) {
	sprintf(s2,"%d",schedule[i]->diff);
        if((schedule[i]!=NULL) && strcmp(s2,s1)==0){
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
    printf("%s %s %d %d\n",s->name,s->prof,s->code,s->major);
    printf("%s %d %d %d\n",s->hw,s->due,s->diff,s->score);
#endif
    sprintf(str, "%s %s %d %d %s %d %d %d", s->name, s->prof, s->code, s->major, s->hw, s->due,s->diff,s->score);
    return str;
}
int load_file(){
	FILE *pf;
	int curcount = 0;
	pf = fopen("schedule.txt", "rt");
	for(int i = 0 ;; i++){
		Sche* s = (Sche*)malloc(sizeof(Sche));
		fscanf(pf,"%s %s %d %d %s %d %d %d", s->name, s->prof, &s->code, &s->major, s->hw, &s->due,&s->diff,&s->score);
		schedule[i] = s;
		curcount++;
		if(feof(pf))
			break;
	}
	fclose(pf);
	curcount--;
	return curcount;
}
