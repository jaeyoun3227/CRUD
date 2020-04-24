#include "schedule.h"
#define MAX_LENTH 512
#ifndef DEBUG
#define DEBUG
#endif
// 애플리케이션용 함수 원형
void create_sche(); //과목별 스케줄 생성
void read_sche(); //특정 조건에 부합하는 정보 출력(다수개 가능)
void update_sche(); //특정 조건에 부합하는 정보 필드 값 변경
void delete_sche(); //특정 조건에 부합하는 정보 전체 스케줄 제거
void update_sches();
void delete_sches();
void list_sche(); //모든 과목 스케줄 출력
void search_name(); //과목 이름 검색
void search_major(); //과목의 전공번호 검색
void search_code(); //과목번호 검색
void search_diff();
void sort_score(); //점수 낮은 순으로 과목 스케줄 정렬
void read_file(); //과목스케줄의 데이터 파일 읽어오기
void read_report(); //과목 스케줄 보고서 읽어오기
void save_file(); //과목 스케줄의 데이터 파일 저장하기
void save_report(); //과목 스케줄의 데이터파일 보고서로 저장하기
void debug_records(); //for debug

int main(){
    s_init();
    int menu;
    printf("\nLoad schedule data to start => choose Menu 16 \n");
    printf("Create new schedule data without load file => choose Menu 1 \n\n");
    while(1){
	printf("-------------------------------Menu--------------------------------\n");
        printf("1.Create \t\t2.Read \t\t\t3.Update \t\n4.Delete \t\t5.Update(by major) \t6.Delete(by diff) \t\n7.List \t\t\t8.Search(name) \t\t9.Search(major) \t\n10.Search(code) \t11.Search(diff) \t12.Sort(score) \t\n13.Read(data,report) \t14.Save(update file) \t15.Debug \t\t\n16.Load file \t\t0.Quit \n-------------------------------------------------------------------\nSelect Menu > ");
        scanf("%d", &menu);
        	printf("\n");
        	switch(menu){
            		case 1: 
                		create_sche();
                		break;
            		case 2: 
                		read_sche();
                		break;
	    		case 3: 
                		update_sche();
                		break;
            		case 4: 
                		delete_sche();
                		break;
			case 5: 
				update_sches();
				break;
			case 6: 
				delete_sches();
				break;
            		case 7: 
                		list_sche();
                		break;
            		case 8:
				search_name();
                		break;
            		case 9:
                		search_major();
                		break;
            		case 10: 
                		search_code();
                		break;
	    		case 11:
                		search_diff();
                		break;
	    		case 12: 
                		sort_score();
                		break;
            		case 13: 
                		read_file();
				read_report();
                		break;
            		case 14:
				save_file();
				save_report();
				break;
	    		case 15:
				debug_records();
				break;
	    		case 16:
				input_count(load_file());
				printf("load all subject schedules\n");
				break;
	    		case 0: 
            		default:
				return 0; 
	}
    }
    return 0;
}

void create_sche(){
    if(!s_is_available()) {
        printf("There is no space!\n");
        return;
    }
    char name[20], prof[20], hw[20];
    int code, major, due, diff, score;  
    printf("Enter a new schedule.\n");
    printf("Subject name (in English,no space)> ");
    scanf("%s", name);
    if(s_search_by_name(name)) {
        printf("Duplicated name!\n");
        return;
    }
    printf("Professor name (in English,no space)> ");
    scanf("%s",prof);
    printf("Code number (integer number) > ");
    scanf("%d",&code);
    if(s_search_by_code(code)) {
	printf("Duplicated code!\n");
	return;
    } 
    printf("Major number (computer:0, biology:1, nonmajor:2)> ");
    scanf("%d",&major);
    if(s_search_by_major(major)) {
 	printf("There are same majors\n");
    }	
    printf("Homework (in English,no space)> ");
    scanf("%s",hw);
    printf("Remaining due days (in integer)> ");
    scanf("%d",&due);
    printf("Difficulty (major:2,non-major:1)> ");
    scanf("%d",&diff);
    score=due+diff;
    printf("Score > %d\n",score);
    s_create(name, prof, code, major, hw, due, diff, score); 
}

void read_sche(){
    char name[20];
    printf("Read subject in the list.\n");
    list_sche();
    printf("\nEnter a subject name > ");
    scanf("%s", name);

    Sche* s = s_search_by_name(name);
    if(s) {
        printf("Schedule info.\n");
        printf("Name : %s\n", s_getname(s));
        printf("Professor : %s\n", s_getprof(s));
        printf("Code num : %d\n", s_getcode(s));
        printf("Major num : %d\n", s_getmajor(s));
        printf("Homework : %s\n", s_gethw(s));
        printf("Remaining due days : %d\n", s_getdue(s));
        printf("Difficulty : %d\n", s_getdiff(s));
        printf("Score : %d\n", s_getscore(s));
    }
    else {
        printf("No such schedule!\n");
    }
}
 
void update_sche(){
    char name[20];
    char hw[20];
    int due,score;
    printf("Update subject in the list.\n");
    list_sche();
    printf("\nEnter a subject name to update > ");
    scanf("%s",name);
    Sche* s=s_search_by_name(name);
    if(s) {
    	printf("Enter a updated info.\n");
    	printf("Homework (in English, no space)> ");
    	scanf("%s",hw);
    	printf("Remaining due days (integer number)> ");
    	scanf("%d",&due);
    	score=due+s_getdiff(s);
    	s_update(s, hw, due,score);
    	}
    else {
	printf("No such member!\n");
    }
}

void delete_sche(){
    char name[20];
    printf("Delete subject in the list.\n");
    list_sche();
    printf("\nEnter a subject name to delete > ");
    scanf("%s",name);
    Sche* s=s_search_by_name(name);
    if(s) {
	s_delete(s);
	printf("The record is deleted!\n");
    }
    else {
	printf("No such schedule!\n");
    }
}

void update_sches(){
    char hw[20];
    int due,score,major;
    printf("Update subjects in the list.\n");
    list_sche();
    Sche* schedule[MAX_SUBJECTS];
    printf("\nEnter a subject major num to update (computer:0, biology:1, nonmajor:2) > ");
    scanf("%d",&major);
    int size = s_get_all_by_major(schedule,major);
    printf("Enter a updated info.\n");
    printf("Homework (in English,no space)> ");
    scanf("%s",hw);
    printf("Remaining due days (integer number)> ");
    scanf("%d",&due);
    for(int i=0;i<size;i++) {
        Sche* s = schedule[i];
        score=due+s_getdiff(s);
        s_update(s, hw, due,score);
    }
}
void delete_sches(){
    int diff;
    printf("Delete subjects in the list.\n");
    list_sche();
    int c=s_count();
    Sche* schedule[c];
    printf("\nEnter a subject difficulty to delete (major:2, nonmajor:1) > ");
    scanf("%d", &diff);
    int size = s_get_all_by_diff(schedule, diff);
    for(int i=0;i<size;i++) {
        Sche* s=schedule[i];
        s_delete(s);
    }
    printf("The records are deleted!\n");
}

void list_sche(){
    // 전체 리스트 출력
    printf("All schedules.\n");
    int size = s_count();
    Sche* schedule[MAX_SUBJECTS];
    s_get_all(schedule);
    for(int i=0; i<size; i++){
        Sche* s = schedule[i];
        printf("%d. %s\n", i+1, s_to_string(s));
    }
}

void search_name(){
    //이름 일부문자열로 검색
    char name[20];
    printf("Search subject by name in the list.\n");
    list_sche();
    printf("\nEnter a subject name > ");
    scanf("%s", name);

    Sche* schedule[MAX_SUBJECTS];
    int size = s_get_all_by_name(schedule, name);
    printf("%d schedules found.\n", size);
    for(int i=0; i<size; i++){
        Sche* s = schedule[i];
        printf("%d. %s\n", i+1, s_to_string(s));
    }
}
void search_major(){
    int major;
    printf("Search subject by major num in the list.\n");
    list_sche();
    printf("\nEnter a major num (computer:0, biology:1, nonmajor:2) > ");
    scanf("%d", &major);
    Sche* schedule[MAX_SUBJECTS];
    int size = s_get_all_by_major(schedule, major);
    printf("%d schedules found.\n", size);
    for(int i=0; i<size; i++){
        Sche* s = schedule[i];
        printf("%d. %s\n", i+1, s_to_string(s));
    }
}
void search_code(){
    int code;
    printf("Search subject by code num in the list.\n");
    list_sche();
    printf("\nEnter a code num (integer number) > ");
    scanf("%d", &code);

    Sche* schedule[MAX_SUBJECTS];
    int size = s_get_all_by_code(schedule,code);
    printf("%d schedules found.\n", size);
    for(int i=0; i<size; i++){
        Sche* s = schedule[i];
        printf("%d. %s\n", i+1, s_to_string(s));
    }
}
void search_diff(){
    int diff;
    printf("Search subject by difficulty in the list.\n");
    list_sche();
    printf("\nEnter a difficulty (major:2, nonmajor:1) > ");
    scanf("%d", &diff);

    Sche* schedule[MAX_SUBJECTS];
    int size = s_get_all_by_diff(schedule, diff);
    printf("%d schedules found.\n", size);
    for(int i=0; i<size; i++){
        Sche* s = schedule[i];
        printf("%d. %s\n", i+1, s_to_string(s));
    }
}

void sort_score(){
    printf("Sort schedules by subject scores.\n");
    Sche* schedule[MAX_SUBJECTS];
    s_get_all(schedule);
    Sche temp;
    int size=s_count(); 
    for(int i=0;i<size;i++) {
	for(int j=0;j<i;j++){
		if(schedule[i]->score<schedule[j]->score){
			temp=*schedule[i];
			*schedule[i]=*schedule[j];
        		*schedule[j]=temp;
		}
	}
    }
    printf("Priority of subjects.\n");
    for(int i=0;i<size;i++) {
	Sche*s= schedule[i];
	printf("%d.%s\n",i+1,s_to_string(s));
    }
}

void read_file(){
    // 데이터파일 읽기
    char ch;
    FILE* f1=fopen("schedule.txt","rt");
    if(f1==NULL) {
        printf("data open failed!\n");
        return;
    }
    printf("data file open!\n");
    while(1){
        ch=fgetc(f1);
        if(ch==EOF)
            break;
        putchar(ch);
    }
    printf("\n");
    fclose(f1); 
}

void read_report(){
    // 데이터파일 읽기
    char ch;
    FILE* f2 = fopen("report.txt", "rt");
    if(f2==NULL) {
	printf("report open failed!\n");
        return;
    }
    printf("report file open!\n");
    while(1){
	ch=fgetc(f2);
	if(ch==EOF)
	    break;
	putchar(ch);
    }
    printf("\n");
    fclose(f2);
}

void save_file(){
    // 데이터파일 저장
    FILE *f3=NULL;
    f3 = fopen("schedule_update.txt","w");
    Sche* schedule[MAX_SUBJECTS];
    s_get_all(schedule);
    if(f3==NULL) {
	printf("update schedule open failed!\n");
    }
    printf("update schedule open!\n");
    if(f3!=NULL) {
	for(int i=0;i<s_count();i++) {
	    Sche* s =schedule[i];
	    fprintf(f3,"%s\n",s_to_string_save(s));
	}
    }	
    fclose(f3);
    int line_count=0;
    char buffer[MAX_LENTH];
    FILE *f4=NULL;
    f4=fopen("schedule_update.txt","rt");
    if(f4!=NULL) {
        printf("update schedule read!\n");
        while(fgets(buffer,MAX_LENTH,f4)!=NULL) {
	     line_count++;
             printf("%d.%s",line_count,buffer);
        }
	printf("\n");
        fclose(f4);
    }	
}
void save_report(){
    // 데이터파일 저장
    FILE *f5=NULL;
    f5 = fopen("report_update.txt", "w");
    Sche* schedule[MAX_SUBJECTS];
    s_get_all(schedule);
    if(f5==NULL) {
        printf("update report open failed!\n");
    }
    printf("update report open!\n");
    if(f5!=NULL) {
	for(int i= 0;i<s_count();i++){
		fprintf(f5,"%d.%s\t score: %d\n",(i+1), schedule[i]->name, schedule[i]->score); 
	}
    }
    fclose(f5);
    char buffer[MAX_LENTH];
    FILE *f6=NULL;
    f6=fopen("report_update.txt","rt");
    if(f6!=NULL) {
        printf("update report read!\n");
        while(fgets(buffer,MAX_LENTH,f6)!=NULL) {
             printf("%s",buffer);
        }
	printf("\n");
        fclose(f6);
    }

}
  
void debug_records(){
    // for debug  
    Sche* schedule[MAX_SUBJECTS]={0};
    s_get_all2(schedule);
    for(int i=0; i<MAX_SUBJECTS; i++){
        printf("%d - %p\n",i+1, schedule[i]);
    }    
}

