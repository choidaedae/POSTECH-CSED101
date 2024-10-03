#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
		
		char name[20];
		int exam[2];
		float avg;
		char grade; 
		
} STUDENT;
	
typedef struct node{
	
	STUDENT data;
	struct node* next;
	
}NODE;	
	
	
typedef struct{
	
	int count; // ������ ����  
	NODE * head; // ù ��� ����Ŵ 
	NODE * tail; // ������ ��� ����Ŵ 	
	
} LIST;

void print_students(STUDENT slist[], int idx);

void add_student(STUDENT *p);

void print_one_student(STUDENT slist, int idx);


int main(){
	
	
	char com[10];
	char sname[20];
	LIST slist; 
	int idx=0; 
	
	//�ʱ�ȭ 
	slist.count = 0; 
	slist.head = NULL;
	slist.tail = NULL;
	
	while(1){
	printf(">> ");
	scanf("%s", com);
	
	
	if(strcmp(com,"add")==0){
		
		insert_node(&slist);	
		printf("\n");
	} 
	
	else if(strcmp(com, "print")==0){
		print_list(&slist);
		printf("\n");
	}	
	
	else if(strcmp(com, "find")==0){
	NODE *temp;	
	printf("�̸�: ");
	scanf("%s", sname);	
	
		int i=0;
		
		printf("��ȣ                �̸�   �߰�   �⸻    ���(����)\n");
		
		for(temp = slist.head; temp != NULL; temp = temp->next){
			
			i++;
			
			if(strcmp(temp->data.name, sname)==0){
				
				print_one_student(temp->data, i);
				
			}
		
		}
		printf("\n");
	
	}
	
	else if(strcmp(com, "quit")==0) break;
	
		
	}	
	
	
	return 0;
}

void print_list(LIST * plist){ // ����� ����� ����ϴ� �Լ�  
	
	NODE *temp;
	int i= 0;
	
		for(temp = plist->head; temp != NULL; temp = temp->next){ //temp�� ����Ű�� ���� ���� ���� �ϳ��� �ű�鼭, ������
		 
		i++; // i�� 1����  
		print_one_student(temp->data , i); // 1�� ��� 
		}
}

void insert_node(LIST *plist){ //node�� �����ϴ� �Լ� 
	
	
	NODE * temp = (NODE *)malloc(sizeof(NODE)); // �����Ҵ� 
	temp->next = NULL;	
	add_student(&temp->data);
	
		if(plist->head == NULL){ //�� ����Ʈ�� ����  
		
		plist->count++;
		plist->head = temp;
		plist->tail = temp;
		
		}
	
		else plist->tail->next = temp; 
		
	plist->tail = temp; 
	plist->count++;
}



void add_student(STUDENT *p){ //slist�� �޾ƿ�  
	
	printf("�̸�: ");
	scanf("%s", p->name); 
	printf("�߰����: ");
	scanf("%d", &p->exam[0]); 
	printf("�⸻���: ");
	scanf("%d", &p->exam[1]); 
	p->avg = (float)(p->exam[0] + p->exam[1]) /2 ; //��� 
	if((p->avg)>=90) p->grade ='A';
	else if((p->avg)>=80) p->grade ='B';
	else if((p->avg)>=70) p->grade ='C';
	else if((p->avg)>=60) p->grade ='D';
	else p->grade = 'F';
}

void print_one_student(STUDENT slist, int idx){
	
	printf("%2d %20s   %4d   %4d   %4.2f (%c)\n", idx, slist.name, slist.exam[0], slist.exam[1], slist.avg, slist.grade);
			
}
void print_students(STUDENT slist[], int idx){
	
	int i;
	
	printf("��ȣ               �̸�   �߰�   �⸻    ���(����)\n");
	for(i=0; i<idx; i++){
		
		print_one_student(slist[i], i);
	}
}


