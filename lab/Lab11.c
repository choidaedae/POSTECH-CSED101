#include<stdio.h>
#include<string.h>


typedef struct {
		
		char name[20];
		int exam[2];
		float avg;
		char grade; 
		
} STUDENT;
	
void print_students(STUDENT slist[], int idx);
void add_student(STUDENT *p);
void print_one_student(STUDENT slist, int idx);


int main(){
	
	char com[10];
	char sname[20];
	STUDENT slist[10];
	int idx=0; 
	
	while(1){
	printf(">> ");
	scanf("%s", com);
	
	
	if(strcmp(com,"add")==0){
		
		add_student(&slist[idx]);
		idx++; 
		printf("\n");
	} 
	
	else if(strcmp(com, "print")==0){
		
		print_students(slist, idx);
	}	
	
	else if(strcmp(com, "find")==0){
	printf("이름: ");
	scanf("%s", sname);	
	
		int i;
		printf("번호                이름   중간   기말    평균(학점)\n");
		for(i=0; i<idx; i++){
			if(strcmp(slist[i].name, sname)==0){
				print_one_student(slist[i], i);
				
			}
		
		}
	
	}
	
	
	else if(strcmp(com, "quit")==0) break;
	
	
	}	
	
	
	return 0;
}


void add_student(STUDENT *p){
	printf("이름: ");
	scanf("%s", p->name);
	printf("중간고사: ");
	scanf("%d", &p->exam[0]);
	printf("기말고사: ");
	scanf("%d", &p->exam[1]); 
	p->avg = (p->exam[0] + p->exam[1]) /2 ;
	if((p->avg)>=90) p->grade ='A';
	else if((p->avg)>=80) p->grade ='B';
	else if((p->avg)>=70) p->grade ='C';
	else if((p->avg)>=60) p->grade ='D';
	else p->grade = 'F';
}

void print_one_student(STUDENT slist, int idx){
	
	printf("%2d %20s   %4d   %4d   %4.2f (%c)\n", idx+1, slist.name, slist.exam[0], slist.exam[1], slist.avg, slist.grade);
			
}
void print_students(STUDENT slist[], int idx){
	
	int i;
	
	printf("번호               이름   중간   기말    평균(학점)\n");
	for(i=0; i<idx; i++){
		
		print_one_student(slist[i], i);
	}
}


