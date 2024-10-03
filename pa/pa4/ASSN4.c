// 20210716 최대현 ASSN4
// 개발환경은 Visual Studio 2019를 사용하였습니다. 


#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct User {

	char name[21];
	char email[41];
	struct User* next;

} USER;

typedef struct Participant {

	USER* user;
	bool camera;
	bool microphone;
	struct Participant* next;

} PARTICIPANT;

typedef struct Conference {

	char roomName[21];
	int numParticipant;
	int maxParticipant;
	PARTICIPANT* participants;

} CONFERENCE;

typedef struct userlist { // participant의 head node 역할을 하는 Conference처럼, 편의를 위해 user의 head node가 포함된 userlist라는 구조체를 따로 지정하여 사용하였습니다. 

	int count; // userlist 속에 user가 몇 명 있는지 저장하는 변수 
	USER *head;

} USERLIST;

void print_user_list(USERLIST* ulist); // userlist를 출력하는 함수 
void user_add(USERLIST* ulist); // userlist에 user을 추가하고, 사전식으로 정렬하는 함수 
void user_delete(USERLIST* ulist); // userlist에서 user를 제거하는 함수 
void conf_info(CONFERENCE* clist); // 현재 회의실의 이름, 인원, 명단 등을 출력하는 함수 
void conf_join(CONFERENCE* clist, USERLIST* ulist); // 회의실에 userlist에 포함된 user 중 한명을 참가시키는 함수 
void conf_hangup(CONFERENCE* clist); // 회의실에서 participant를 제거하는 함수 
void toggle_camera(CONFERENCE* clist); // participant 중 한 명을 지정하여 카메라를 켜거나 끄는 함수 
void toggle_mic(CONFERENCE* clist); // participant 중 한 명을 지정하여 마이크를 켜거나 끄는 함수 
void dic_sort(USERLIST* ulist); // userlist 속 user들의 이름을 사전식으로 정렬하는 함수 
void insert_user(USERLIST* ulist, USER* uPre, char *sen); // user node를 userlist의 맨 끝에 붙이는 함수  
void del_user(USERLIST* ulist); // userlist의 모든 노드에 대해 동적 할당하는 함수 
void del_conf(CONFERENCE *clist); // conference의 모든 노드에 대해 동적 할당하는 함수 

int main() {

	char com[30]; // 커맨드 
	char filename[30]; // 읽기모드로 불러올 파일 이름 
	char sen[100]; // 파일에서 한 줄씩 불러옴 
	char usermail[41]; 

	PARTICIPANT* par_head = (PARTICIPANT*)malloc(sizeof(PARTICIPANT)); // conf.participants가 향하게 하는 head node (이렇게 하지 않으면 첫 노드를 삽입할 때 conference 구조체가 NULL이 되면서 구현이 어려워짐) 
	par_head->next = NULL;

	CONFERENCE conf;
	conf.participants = par_head; 
	conf.numParticipant = 0;

	USERLIST ulist; //구조체 변수 선언 
	ulist.head = NULL; // 초기화
	ulist.count = 0;
	
	FILE* fp = NULL;

	printf("유저 리스트 파일 이름을 입력해주세요. >>"); 

	do{

		scanf("%s", filename);
		fp = fopen(filename, "r"); // 읽기모드로 열어줌. 
		if (fp == NULL) printf("\n유효하지 않은 입력입니다. 유저 리스트 파일 이름을 입력해주세요 >>"); // 파일이 없을 경우 
		
	} while (fp == NULL);


	USER* u_tail = ulist.head; // userlist의 마지막 부분을 가리켜줄 변수 
	PARTICIPANT* p_tail = conf.participants; // conference의 마지막 부분을 가리켜줄 변수


	USER* u_temp;

	while(!feof(fp)) {
		
		fgets(sen, 100, fp);
		for (u_temp = ulist.head; u_temp != NULL; u_temp = u_temp->next)
			u_tail = u_temp;

		insert_user(&ulist, u_tail, sen);

	}

	dic_sort(&ulist); // userlist 정렬 

	printf("[INFO] %s에서 총 %d명의 유저를 불러왔습니다.\n\n", filename, ulist.count);

	printf("회의실 이름을 입력해주세요. >> ");
	scanf("%s", conf.roomName); 
	printf("최대 사용자 수를 입력해주세요. >> ");
	scanf("%d", &conf.maxParticipant);
	printf("[INFO] test 회의실이 생성되었습니다!\n\n");
	

	while (1) {

		printf("명령어를 입력해주세요. >> ");
		rewind(stdin); // 입력 버퍼 비움 
		fgets(com, 30, stdin);

		if (strcmp(com, "user list\n") == 0) { 

			print_user_list(&ulist);

		}


		else if (strcmp(com, "user add\n") == 0) { 

			user_add(&ulist);
			
		}

		else if (strcmp(com, "user delete\n") == 0) { 

			user_delete(&ulist);

		}

		else if (strcmp(com, "conf info\n") == 0) { 

			conf_info(&conf);

		}

		else if (strcmp(com, "conf join\n") == 0) { 
		
			conf_join(&conf, &ulist);

		}

		else if (strcmp(com, "conf hangup\n") == 0) {

			conf_hangup(&conf); 

		}

		else if (strcmp(com, "conf toggle camera\n") == 0) { 

			toggle_camera(&conf);
		}

		else if (strcmp(com, "conf toggle mic\n") == 0) { 

			toggle_mic(&conf);
		}

		else if (strcmp(com, "quit\n") == 0) { 

			del_user(&ulist); // 동적 할당 해제 
			del_conf(&conf); // 동적 할당 해제 

			printf("[INFO] 회의를 종료합니다!\n\n");
			break;
		}

		else printf("\n유효하지 않은 입력입니다. ");

	}

	return 0;

}

void print_user_list(USERLIST *ulist) {

	int i=0; // 번호 변수 
	USER* temp = NULL; 

	printf("\n\n");
	printf("==============================================================\n");
	printf("번호		이름					이메일\n");
	printf("--------------------------------------------------------------\n");

	for (temp = ulist->head;  temp != NULL ; temp = temp->next) { 
		i++;
		printf("%d%20s %40s\n", i, temp->name, temp->email);

	}
	printf("==============================================================\n\n");

}


void user_add(USERLIST *ulist) {

	char username[21];
	char usermail[41];
	char userinfo[70]; // username \t usermail 형태의 문자열 변수 
	printf("추가할 유저의 이름을 입력해주세요. >> ");
	scanf("%s", username);
	rewind(stdin);
	printf("추가할 유저의 이메일을 입력해주세요.  >> ");
	fgets(usermail, 40, stdin); 
	strtok(usermail, "\n");
	USER* u_temp = NULL;
	USER* u_tail= ulist->head;

	for (u_temp = ulist->head; u_temp != NULL; u_temp = u_temp->next) { // 이미 userlist에 user가 있는 경우 
		if (strcmp(u_temp->name, username) == 0) {

			printf("[INFO] %s, %s 유저가 이미 유저 리스트에 있습니다.", username, usermail);
			return;
		}
	}

	strcpy(userinfo, username);
	strcat(userinfo, "\t");
	strcat(userinfo, usermail); // user를 insert_user 함수로 간편하게 넣기 위해 userinfo를 user.txt 문장과 똑같이 만들었음 

	for (u_temp = ulist->head; u_temp != NULL; u_temp = u_temp->next) 
		u_tail = u_temp; // 최종적으로 u_tail은 가장 마지막 노드의 이전 노드를 가리키게 됨. 

	insert_user(ulist, u_tail, userinfo); // 가장 끝에 삽입함. 

	printf("[INFO] %s, %s 유저가 추가되었습니다.\n\n", username, usermail);

	dic_sort(ulist);
	ulist->count++;


}

void user_delete(USERLIST *ulist) {

	char username[30];
	char yesorno;
	USER* pos = (USER*)malloc(sizeof(USER));
	USER* temp = NULL;
	printf("제거할 유저의 이름을 입력해주세요. >> "); 
	scanf("%s", username);

	for (pos = ulist->head; pos != NULL; pos = pos->next) { //userlist에 제거 대상이 있는지 확인 

		if (strcmp(pos->name, username) == 0) break;
	}

	if (pos == NULL) { // for문이 끝까지 돌았을 경우 (user가 없는 경우)
		printf("[INFO] 해당 유저는 존재하지 않습니다!\n\n");
		return;

	}

	else{ 
		printf("%s, %s 유저를 제거하시겠습니까? (y/n) ", pos->name, pos->email);

		rewind(stdin);
		scanf("%c", &yesorno);

		if (yesorno == 'n') return;

		else if(yesorno == 'y'){

			if (ulist->head == pos) ulist->head = pos->next;
			
			else  {

				for (temp = ulist->head; temp->next !=NULL; temp = temp->next) {
					if (temp->next == pos) break;
				}
				
				temp->next = pos->next;


			}

			printf("[INFO] %s, %s 유저를 제거하였습니다.\n\n", pos->name, pos->email);
			ulist->count--;

			free(pos); // 동적 할당 해제 

		}
		
	}




}


void conf_join(CONFERENCE* clist, USERLIST* ulist) {

	if (clist->numParticipant == clist->maxParticipant) {
		printf("[INFO] 회의에 최대 인원 %d 명이 참여하고 있습니다!\n\n", clist->maxParticipant);
		return;
	}

	PARTICIPANT* par_temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));
	PARTICIPANT* par_tail = NULL;
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));

	USER* u_temp;
	char yesorno;
	char username[30];
	int error = 0;
	
	printf("추가할 유저의 이름을 입력해주세요. >> ");
	
	scanf("%s", username);

	for (u_temp = ulist->head; u_temp != NULL; u_temp = u_temp->next) {

		if (strcmp(u_temp->name, username) == 0) break;
	}

	if (u_temp==NULL) {
		printf("[INFO] 해당 유저는 존재하지 않습니다!\n\n");
		return;
	}




	if (clist->participants->next == NULL) { // 가장 첫 노드일 때 (CONFERENCE가 비었을 때)
		
		temp->user = u_temp;
		printf("카메라를 켠 상태로 시작하시겠습니까? (y/n) >> ");
		rewind(stdin);
		scanf("%c", &yesorno);
		if (yesorno == 'y') temp->camera = true;
		else if(yesorno == 'n') temp->camera = false;

		printf("마이크를 켠 상태로 시작하시겠습니까? (y/n) >> ");
		rewind(stdin);
		scanf("%c", &yesorno);
		if (yesorno == 'y') temp->microphone = true;
		else if (yesorno == 'n') temp->microphone = false;


		clist->participants->next = temp; // 노드를 붙여줌.
		temp->next = NULL;	//temp 를 끝으로 만듦

		clist->numParticipant++;
		printf("[INFO] %s 이(가) 회의에 참여했습니다!\n\n", username);

		
		return;
	}

	else {  // 중간 노드일 때

		temp->user = u_temp; // 

		for (par_temp = clist->participants->next; par_temp != NULL; par_temp = par_temp->next) {

			par_tail = par_temp; 
			if (strcmp(par_temp->user->name, username) == 0) error = 1; //이미 회의에 참여한 경우 

		}

		if (error==1) { // 이미 clist에 있을 때 

			printf("[INFO] %s 이(가) 회의에 이미 참여했습니다!\n\n", username);
			return;
		}

		else {
			
			printf("카메라를 켠 상태로 시작하시겠습니까? (y/n) >> ");
			rewind(stdin);
			scanf("%c", &yesorno);
			if (yesorno == 'y') temp->camera = true;
			else temp->camera = false;

			printf("마이크를 켠 상태로 시작하시겠습니까? (y/n) >> ");
			rewind(stdin);
			scanf("%c", &yesorno);
			if (yesorno == 'y') temp->microphone = true;
			else temp->microphone = false;

			par_tail->next = temp; // 노드를 붙여줌
			temp->next = NULL; // par_temp를 끝으로 만듦 

			clist->numParticipant++;
			printf("[INFO] %s 이(가) 회의에 참여했습니다!\n\n", username);
		

		}
	}

}

void conf_info(CONFERENCE* clist) {

	int i;
	PARTICIPANT* par_temp = NULL;
	char cam[5];
	char mic[5];

	printf("회의실 이름: %s\n", clist->roomName);
	printf("최대 사용자 수 : %d\n", clist->maxParticipant);
	printf("참여자 목록: \n\n");
	printf("================================================================================\n");
	printf("		이름   			       이메일		카메라	  마이크\n");
	printf("--------------------------------------------------------------------------------\n");

	par_temp = clist->participants->next;

	for (i = 0; i < clist->numParticipant; i++) {

		if (par_temp->camera == true) strcpy(cam, "ON");
		else strcpy(cam, "OFF");

		if (par_temp->microphone == true) strcpy(mic, "ON");
		else strcpy(mic, "OFF"); 

		printf("%20s%40s%10s%10s\n", par_temp->user->name, par_temp->user->email, cam, mic);

		par_temp = par_temp->next;
	}

	
	printf("================================================================================\n\n");

	return;

}

void conf_hangup(CONFERENCE *clist) {
	char username[21];
	char yesorno;
	PARTICIPANT* par_temp;
	PARTICIPANT* pos;
	printf("제외할 유저의 이름을 입력해주세요. >> ");
	scanf("%s", username);
	
	for (pos = clist->participants->next; pos != NULL; pos = pos->next) {

		if (strcmp(pos->user->name, username) == 0) break;

	}
	
	if (pos == NULL) {

		printf("[INFO] 해당 유저는 회의에 존재하지 않습니다!\n\n");
		return;
		
	}

	else {
		printf("정말로 회의에서 내보내시겠습니까? (y/n) >>");
		rewind(stdin);
		scanf("%c", &yesorno);
		if (yesorno == 'y') {
			if (clist->participants->next == pos) clist->participants->next = pos->next;

			else {

				for (par_temp = clist->participants->next; par_temp->next != NULL; par_temp = par_temp->next) {
					if (par_temp->next == pos) break;
				}

				par_temp->next = pos->next;


			}

			printf("[INFO] %s 이(가) 회의에서 나갔습니다!\n\n", pos->user->name);
			clist->numParticipant--;

			free(pos); // 동적할당 해제 
		}

		else if (yesorno == 'n') return;
	}



}

void toggle_camera(CONFERENCE *clist) { // clist에 속한 participant의 카메라를 on/off하는 함수 

	PARTICIPANT* par_temp;
	char username[30];

	if (clist->numParticipant == 0) {
		printf("[INFO] 회의 참석자가 없습니다.\n\n");
		return;
	}

	printf("카메라 상태를 변경할 유저의 이름을 입력해주세요. >> ");

	fgets(username, 30, stdin);
	strtok(username, "\n");
	for (par_temp = clist->participants->next; par_temp != NULL; par_temp = par_temp->next) {

		if (strcmp(par_temp->user->name, username) == 0) {

			if ((par_temp->camera) == false) {
				par_temp->camera = true;
				printf("[INFO] %s 의 카메라가 OFF->ON 되었습니다!\n", par_temp->user->name);
				break;
			}

			else if ((par_temp->camera) == true) {
				par_temp->camera = false;
				printf("[INFO] %s 의 카메라가 ON->OFF 되었습니다!\n", par_temp->user->name);
				break;
			}

		}
	}

	if (par_temp == NULL) {
		printf("INFO] 해당 유저는 회의에 존재하지 않습니다!\n");
	}
	printf("\n");
}

void toggle_mic(CONFERENCE* clist) {  // clist에 속한 participant의 마이크를 on/off하는 함수 

	PARTICIPANT* par_temp;
	char username[30];


	if (clist->numParticipant == 0) {
		printf("[INFO] 회의 참석자가 없습니다.\n\n");
		return;
	}

	printf("마이크 상태를 변경할 유저의 이름을 입력해주세요. >> ");

	fgets(username, 30, stdin);
	strtok(username, "\n");

	for (par_temp = clist->participants->next; par_temp != NULL; par_temp = par_temp->next) {

		if (strcmp(par_temp->user->name, username) == 0) {

			if ((par_temp->microphone) == false) {
				par_temp->microphone = true;
				printf("[INFO] %s 의 마이크가 OFF->ON 되었습니다!\n", par_temp->user->name);
				break;
			}

			else if ((par_temp->microphone) == true) {
				par_temp->microphone = false;
				printf("[INFO] %s 의 마이크가 ON->OFF 되었습니다!\n", par_temp->user->name);
				break;
			}

		}
	}

	if (par_temp == NULL) {
		printf("INFO] 해당 유저는 회의에 존재하지 않습니다!\n");
	}
	printf("\n");
}

void dic_sort(USERLIST * ulist) { 

	int i, j;
	char tname[21]; //이름을 임시로 저장할 변수 
	char tmail[41]; //이메일을 임시로 저장할 변수 
	USER* u_temp =  ulist -> head;
	for (i = 0; i < ulist->count; i++) { // 버블정렬 기법 

		for (j = 0; j < ulist->count - 1; j++) {

			if (strcmp(u_temp->name, u_temp->next->name) > 0) { // 앞 노드의 이름이 사전식으로 뒤의 위치에 있으면 

				strcpy(tname, u_temp->name);
				strcpy(u_temp->name, u_temp->next->name);
				strcpy(u_temp->next->name, tname);

				strcpy(tmail, u_temp->email);
				strcpy(u_temp->email, u_temp->next->email);
				strcpy(u_temp->next->email, tmail);

			}
			u_temp = u_temp->next;
		}
		u_temp = ulist->head; //for문의 시작 node를 한 칸 오른쪽으로 옮김 
	}


}


void insert_user(USERLIST* ulist, USER *uPre, char *sen) { // username과 usermail이 들어있는 문장 가공해서 사용 

	USER* u_temp = (USER*)malloc(sizeof(USER)); // 동적 할당
	
	strcpy(u_temp->name, strtok(sen, "\t")); // 이름 저장 
	strcpy(u_temp->email, strtok(NULL, "\n")); // 메일 저장 

	if (ulist->head == NULL) {	// ulist가 비어있을 때 
		ulist->head = u_temp;   // head가 u_temp를 가리키게 함 
		u_temp->next = NULL;	//u_temp 를 끝으로 만듦 
	}
	else if(uPre->next == NULL){ // 1개 이상의 NODE가 포함되어 있을 때 
		uPre->next = u_temp;
		u_temp->next = NULL;
	}

	ulist->count++;
	
	return;
}



void del_user(USERLIST *ulist) { //USERLIST 연결 리스트에 대해서 할당 해제 

	int i;

	USER* target = ulist->head;
	USER* temp = NULL;

	for (i = 0; i < ulist->count; i++) {
		temp = target->next;
		free(target);
		target = temp;

	}
	
	
}

void del_conf(CONFERENCE* clist) { //CONFERENCE 연결 리스트에 대해서 할당 해제 

	int i;

	PARTICIPANT* target = clist->participants->next;
	PARTICIPANT* temp = NULL;

	for (i = 0; i < clist->numParticipant; i++) {
		temp = target->next;
		free(target);
		target = temp; 

	}
}



