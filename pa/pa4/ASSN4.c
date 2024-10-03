// 20210716 �ִ��� ASSN4
// ����ȯ���� Visual Studio 2019�� ����Ͽ����ϴ�. 


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

typedef struct userlist { // participant�� head node ������ �ϴ� Conferenceó��, ���Ǹ� ���� user�� head node�� ���Ե� userlist��� ����ü�� ���� �����Ͽ� ����Ͽ����ϴ�. 

	int count; // userlist �ӿ� user�� �� �� �ִ��� �����ϴ� ���� 
	USER *head;

} USERLIST;

void print_user_list(USERLIST* ulist); // userlist�� ����ϴ� �Լ� 
void user_add(USERLIST* ulist); // userlist�� user�� �߰��ϰ�, ���������� �����ϴ� �Լ� 
void user_delete(USERLIST* ulist); // userlist���� user�� �����ϴ� �Լ� 
void conf_info(CONFERENCE* clist); // ���� ȸ�ǽ��� �̸�, �ο�, ��� ���� ����ϴ� �Լ� 
void conf_join(CONFERENCE* clist, USERLIST* ulist); // ȸ�ǽǿ� userlist�� ���Ե� user �� �Ѹ��� ������Ű�� �Լ� 
void conf_hangup(CONFERENCE* clist); // ȸ�ǽǿ��� participant�� �����ϴ� �Լ� 
void toggle_camera(CONFERENCE* clist); // participant �� �� ���� �����Ͽ� ī�޶� �Ѱų� ���� �Լ� 
void toggle_mic(CONFERENCE* clist); // participant �� �� ���� �����Ͽ� ����ũ�� �Ѱų� ���� �Լ� 
void dic_sort(USERLIST* ulist); // userlist �� user���� �̸��� ���������� �����ϴ� �Լ� 
void insert_user(USERLIST* ulist, USER* uPre, char *sen); // user node�� userlist�� �� ���� ���̴� �Լ�  
void del_user(USERLIST* ulist); // userlist�� ��� ��忡 ���� ���� �Ҵ��ϴ� �Լ� 
void del_conf(CONFERENCE *clist); // conference�� ��� ��忡 ���� ���� �Ҵ��ϴ� �Լ� 

int main() {

	char com[30]; // Ŀ�ǵ� 
	char filename[30]; // �б���� �ҷ��� ���� �̸� 
	char sen[100]; // ���Ͽ��� �� �پ� �ҷ��� 
	char usermail[41]; 

	PARTICIPANT* par_head = (PARTICIPANT*)malloc(sizeof(PARTICIPANT)); // conf.participants�� ���ϰ� �ϴ� head node (�̷��� ���� ������ ù ��带 ������ �� conference ����ü�� NULL�� �Ǹ鼭 ������ �������) 
	par_head->next = NULL;

	CONFERENCE conf;
	conf.participants = par_head; 
	conf.numParticipant = 0;

	USERLIST ulist; //����ü ���� ���� 
	ulist.head = NULL; // �ʱ�ȭ
	ulist.count = 0;
	
	FILE* fp = NULL;

	printf("���� ����Ʈ ���� �̸��� �Է����ּ���. >>"); 

	do{

		scanf("%s", filename);
		fp = fopen(filename, "r"); // �б���� ������. 
		if (fp == NULL) printf("\n��ȿ���� ���� �Է��Դϴ�. ���� ����Ʈ ���� �̸��� �Է����ּ��� >>"); // ������ ���� ��� 
		
	} while (fp == NULL);


	USER* u_tail = ulist.head; // userlist�� ������ �κ��� �������� ���� 
	PARTICIPANT* p_tail = conf.participants; // conference�� ������ �κ��� �������� ����


	USER* u_temp;

	while(!feof(fp)) {
		
		fgets(sen, 100, fp);
		for (u_temp = ulist.head; u_temp != NULL; u_temp = u_temp->next)
			u_tail = u_temp;

		insert_user(&ulist, u_tail, sen);

	}

	dic_sort(&ulist); // userlist ���� 

	printf("[INFO] %s���� �� %d���� ������ �ҷ��Խ��ϴ�.\n\n", filename, ulist.count);

	printf("ȸ�ǽ� �̸��� �Է����ּ���. >> ");
	scanf("%s", conf.roomName); 
	printf("�ִ� ����� ���� �Է����ּ���. >> ");
	scanf("%d", &conf.maxParticipant);
	printf("[INFO] test ȸ�ǽ��� �����Ǿ����ϴ�!\n\n");
	

	while (1) {

		printf("��ɾ �Է����ּ���. >> ");
		rewind(stdin); // �Է� ���� ��� 
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

			del_user(&ulist); // ���� �Ҵ� ���� 
			del_conf(&conf); // ���� �Ҵ� ���� 

			printf("[INFO] ȸ�Ǹ� �����մϴ�!\n\n");
			break;
		}

		else printf("\n��ȿ���� ���� �Է��Դϴ�. ");

	}

	return 0;

}

void print_user_list(USERLIST *ulist) {

	int i=0; // ��ȣ ���� 
	USER* temp = NULL; 

	printf("\n\n");
	printf("==============================================================\n");
	printf("��ȣ		�̸�					�̸���\n");
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
	char userinfo[70]; // username \t usermail ������ ���ڿ� ���� 
	printf("�߰��� ������ �̸��� �Է����ּ���. >> ");
	scanf("%s", username);
	rewind(stdin);
	printf("�߰��� ������ �̸����� �Է����ּ���.  >> ");
	fgets(usermail, 40, stdin); 
	strtok(usermail, "\n");
	USER* u_temp = NULL;
	USER* u_tail= ulist->head;

	for (u_temp = ulist->head; u_temp != NULL; u_temp = u_temp->next) { // �̹� userlist�� user�� �ִ� ��� 
		if (strcmp(u_temp->name, username) == 0) {

			printf("[INFO] %s, %s ������ �̹� ���� ����Ʈ�� �ֽ��ϴ�.", username, usermail);
			return;
		}
	}

	strcpy(userinfo, username);
	strcat(userinfo, "\t");
	strcat(userinfo, usermail); // user�� insert_user �Լ��� �����ϰ� �ֱ� ���� userinfo�� user.txt ����� �Ȱ��� ������� 

	for (u_temp = ulist->head; u_temp != NULL; u_temp = u_temp->next) 
		u_tail = u_temp; // ���������� u_tail�� ���� ������ ����� ���� ��带 ����Ű�� ��. 

	insert_user(ulist, u_tail, userinfo); // ���� ���� ������. 

	printf("[INFO] %s, %s ������ �߰��Ǿ����ϴ�.\n\n", username, usermail);

	dic_sort(ulist);
	ulist->count++;


}

void user_delete(USERLIST *ulist) {

	char username[30];
	char yesorno;
	USER* pos = (USER*)malloc(sizeof(USER));
	USER* temp = NULL;
	printf("������ ������ �̸��� �Է����ּ���. >> "); 
	scanf("%s", username);

	for (pos = ulist->head; pos != NULL; pos = pos->next) { //userlist�� ���� ����� �ִ��� Ȯ�� 

		if (strcmp(pos->name, username) == 0) break;
	}

	if (pos == NULL) { // for���� ������ ������ ��� (user�� ���� ���)
		printf("[INFO] �ش� ������ �������� �ʽ��ϴ�!\n\n");
		return;

	}

	else{ 
		printf("%s, %s ������ �����Ͻðڽ��ϱ�? (y/n) ", pos->name, pos->email);

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

			printf("[INFO] %s, %s ������ �����Ͽ����ϴ�.\n\n", pos->name, pos->email);
			ulist->count--;

			free(pos); // ���� �Ҵ� ���� 

		}
		
	}




}


void conf_join(CONFERENCE* clist, USERLIST* ulist) {

	if (clist->numParticipant == clist->maxParticipant) {
		printf("[INFO] ȸ�ǿ� �ִ� �ο� %d ���� �����ϰ� �ֽ��ϴ�!\n\n", clist->maxParticipant);
		return;
	}

	PARTICIPANT* par_temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));
	PARTICIPANT* par_tail = NULL;
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));

	USER* u_temp;
	char yesorno;
	char username[30];
	int error = 0;
	
	printf("�߰��� ������ �̸��� �Է����ּ���. >> ");
	
	scanf("%s", username);

	for (u_temp = ulist->head; u_temp != NULL; u_temp = u_temp->next) {

		if (strcmp(u_temp->name, username) == 0) break;
	}

	if (u_temp==NULL) {
		printf("[INFO] �ش� ������ �������� �ʽ��ϴ�!\n\n");
		return;
	}




	if (clist->participants->next == NULL) { // ���� ù ����� �� (CONFERENCE�� ����� ��)
		
		temp->user = u_temp;
		printf("ī�޶� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >> ");
		rewind(stdin);
		scanf("%c", &yesorno);
		if (yesorno == 'y') temp->camera = true;
		else if(yesorno == 'n') temp->camera = false;

		printf("����ũ�� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >> ");
		rewind(stdin);
		scanf("%c", &yesorno);
		if (yesorno == 'y') temp->microphone = true;
		else if (yesorno == 'n') temp->microphone = false;


		clist->participants->next = temp; // ��带 �ٿ���.
		temp->next = NULL;	//temp �� ������ ����

		clist->numParticipant++;
		printf("[INFO] %s ��(��) ȸ�ǿ� �����߽��ϴ�!\n\n", username);

		
		return;
	}

	else {  // �߰� ����� ��

		temp->user = u_temp; // 

		for (par_temp = clist->participants->next; par_temp != NULL; par_temp = par_temp->next) {

			par_tail = par_temp; 
			if (strcmp(par_temp->user->name, username) == 0) error = 1; //�̹� ȸ�ǿ� ������ ��� 

		}

		if (error==1) { // �̹� clist�� ���� �� 

			printf("[INFO] %s ��(��) ȸ�ǿ� �̹� �����߽��ϴ�!\n\n", username);
			return;
		}

		else {
			
			printf("ī�޶� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >> ");
			rewind(stdin);
			scanf("%c", &yesorno);
			if (yesorno == 'y') temp->camera = true;
			else temp->camera = false;

			printf("����ũ�� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >> ");
			rewind(stdin);
			scanf("%c", &yesorno);
			if (yesorno == 'y') temp->microphone = true;
			else temp->microphone = false;

			par_tail->next = temp; // ��带 �ٿ���
			temp->next = NULL; // par_temp�� ������ ���� 

			clist->numParticipant++;
			printf("[INFO] %s ��(��) ȸ�ǿ� �����߽��ϴ�!\n\n", username);
		

		}
	}

}

void conf_info(CONFERENCE* clist) {

	int i;
	PARTICIPANT* par_temp = NULL;
	char cam[5];
	char mic[5];

	printf("ȸ�ǽ� �̸�: %s\n", clist->roomName);
	printf("�ִ� ����� �� : %d\n", clist->maxParticipant);
	printf("������ ���: \n\n");
	printf("================================================================================\n");
	printf("		�̸�   			       �̸���		ī�޶�	  ����ũ\n");
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
	printf("������ ������ �̸��� �Է����ּ���. >> ");
	scanf("%s", username);
	
	for (pos = clist->participants->next; pos != NULL; pos = pos->next) {

		if (strcmp(pos->user->name, username) == 0) break;

	}
	
	if (pos == NULL) {

		printf("[INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n\n");
		return;
		
	}

	else {
		printf("������ ȸ�ǿ��� �������ðڽ��ϱ�? (y/n) >>");
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

			printf("[INFO] %s ��(��) ȸ�ǿ��� �������ϴ�!\n\n", pos->user->name);
			clist->numParticipant--;

			free(pos); // �����Ҵ� ���� 
		}

		else if (yesorno == 'n') return;
	}



}

void toggle_camera(CONFERENCE *clist) { // clist�� ���� participant�� ī�޶� on/off�ϴ� �Լ� 

	PARTICIPANT* par_temp;
	char username[30];

	if (clist->numParticipant == 0) {
		printf("[INFO] ȸ�� �����ڰ� �����ϴ�.\n\n");
		return;
	}

	printf("ī�޶� ���¸� ������ ������ �̸��� �Է����ּ���. >> ");

	fgets(username, 30, stdin);
	strtok(username, "\n");
	for (par_temp = clist->participants->next; par_temp != NULL; par_temp = par_temp->next) {

		if (strcmp(par_temp->user->name, username) == 0) {

			if ((par_temp->camera) == false) {
				par_temp->camera = true;
				printf("[INFO] %s �� ī�޶� OFF->ON �Ǿ����ϴ�!\n", par_temp->user->name);
				break;
			}

			else if ((par_temp->camera) == true) {
				par_temp->camera = false;
				printf("[INFO] %s �� ī�޶� ON->OFF �Ǿ����ϴ�!\n", par_temp->user->name);
				break;
			}

		}
	}

	if (par_temp == NULL) {
		printf("INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n");
	}
	printf("\n");
}

void toggle_mic(CONFERENCE* clist) {  // clist�� ���� participant�� ����ũ�� on/off�ϴ� �Լ� 

	PARTICIPANT* par_temp;
	char username[30];


	if (clist->numParticipant == 0) {
		printf("[INFO] ȸ�� �����ڰ� �����ϴ�.\n\n");
		return;
	}

	printf("����ũ ���¸� ������ ������ �̸��� �Է����ּ���. >> ");

	fgets(username, 30, stdin);
	strtok(username, "\n");

	for (par_temp = clist->participants->next; par_temp != NULL; par_temp = par_temp->next) {

		if (strcmp(par_temp->user->name, username) == 0) {

			if ((par_temp->microphone) == false) {
				par_temp->microphone = true;
				printf("[INFO] %s �� ����ũ�� OFF->ON �Ǿ����ϴ�!\n", par_temp->user->name);
				break;
			}

			else if ((par_temp->microphone) == true) {
				par_temp->microphone = false;
				printf("[INFO] %s �� ����ũ�� ON->OFF �Ǿ����ϴ�!\n", par_temp->user->name);
				break;
			}

		}
	}

	if (par_temp == NULL) {
		printf("INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n");
	}
	printf("\n");
}

void dic_sort(USERLIST * ulist) { 

	int i, j;
	char tname[21]; //�̸��� �ӽ÷� ������ ���� 
	char tmail[41]; //�̸����� �ӽ÷� ������ ���� 
	USER* u_temp =  ulist -> head;
	for (i = 0; i < ulist->count; i++) { // �������� ��� 

		for (j = 0; j < ulist->count - 1; j++) {

			if (strcmp(u_temp->name, u_temp->next->name) > 0) { // �� ����� �̸��� ���������� ���� ��ġ�� ������ 

				strcpy(tname, u_temp->name);
				strcpy(u_temp->name, u_temp->next->name);
				strcpy(u_temp->next->name, tname);

				strcpy(tmail, u_temp->email);
				strcpy(u_temp->email, u_temp->next->email);
				strcpy(u_temp->next->email, tmail);

			}
			u_temp = u_temp->next;
		}
		u_temp = ulist->head; //for���� ���� node�� �� ĭ ���������� �ű� 
	}


}


void insert_user(USERLIST* ulist, USER *uPre, char *sen) { // username�� usermail�� ����ִ� ���� �����ؼ� ��� 

	USER* u_temp = (USER*)malloc(sizeof(USER)); // ���� �Ҵ�
	
	strcpy(u_temp->name, strtok(sen, "\t")); // �̸� ���� 
	strcpy(u_temp->email, strtok(NULL, "\n")); // ���� ���� 

	if (ulist->head == NULL) {	// ulist�� ������� �� 
		ulist->head = u_temp;   // head�� u_temp�� ����Ű�� �� 
		u_temp->next = NULL;	//u_temp �� ������ ���� 
	}
	else if(uPre->next == NULL){ // 1�� �̻��� NODE�� ���ԵǾ� ���� �� 
		uPre->next = u_temp;
		u_temp->next = NULL;
	}

	ulist->count++;
	
	return;
}



void del_user(USERLIST *ulist) { //USERLIST ���� ����Ʈ�� ���ؼ� �Ҵ� ���� 

	int i;

	USER* target = ulist->head;
	USER* temp = NULL;

	for (i = 0; i < ulist->count; i++) {
		temp = target->next;
		free(target);
		target = temp;

	}
	
	
}

void del_conf(CONFERENCE* clist) { //CONFERENCE ���� ����Ʈ�� ���ؼ� �Ҵ� ���� 

	int i;

	PARTICIPANT* target = clist->participants->next;
	PARTICIPANT* temp = NULL;

	for (i = 0; i < clist->numParticipant; i++) {
		temp = target->next;
		free(target);
		target = temp; 

	}
}



