// 20210716 �ִ��� ASSN2, ����ȯ���� Dev-C++�� �ַ� ����Ͽ����ϴ�.  
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 6 
#include<stdio.h>
#include<stdlib.h>	
#include<time.h> 
void print_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE], int score); //board�� ������ִ� �Լ�. ���������� ���, ����ְ� ����ϴ� ��� ����� �� ���� ������.  
int check_position(int board[][BOARD_SIZE], int col1, int col2, int row1, int row2); // ����ڰ� �ٲ��ְ��� �ϴ� �� ���� �پ��ְ�, �迭 ���� ���� �ִ��� üũ���ִ� �Լ�. 
void set_color_red(); // ���������� ����� �� �ְ� ���ִ� �Լ�. 
void reset_color(); // ���������� �ٲ���� ��� ���� �ٽ� �ǵ�����.  
void clean_match_block(int match_block[][BOARD_SIZE]); //match_block �迭 ���� ��� ���� 0���� �ʱ�ȭ. 
void swap(int* a, int* b); // call by address ������� �� ���� �ٲپ���.  
void empty_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]); //���� ����ؾ� �ϴ� �ε��� ���� �ν��ϰ� �׿� �ش��ϴ� match_block �迭 ���� -1�� ��ȯ, ���� print_board���� -1�� �ν��ؼ� �������� ���.   
int check_match_3(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]); //match_3 ��Ȳ�� �ν��Ͽ� match_block �迭�� ���� �����ϴ� �Լ� 
void rand_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]); //�迭�� ��������� �ν��ϰ� �� ���� 1~5 ������ ������ �ٽ� ä���ִ� �Լ� 
int sub(int a, int b);

int main(){
	char enter;
	int board[BOARD_SIZE][BOARD_SIZE] = {0}; //�̹� ������ ���� ������ �� �ִ� 2���� �迭 
	int match_block[BOARD_SIZE][BOARD_SIZE]= {0}; // ���忡�� �ʿ��� �κ��� �迭 ���� �����ؼ� �������ų�, ���� ���/ ������ ����� �ν��ϴ� ���� ���� 
	int col1, col2, row1, row2, i, j, score, check;  
	check=1;
	score = 0;
	int turn = 6; // turn���� ó���� �� �ֱ� ������ 6���� ����  
	int pos = 0;
	srand(time(NULL));
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED 101\n");
	printf("Assignment 2\n\n");
	printf("[[ Match-3 Game ]]\n\n");
	printf("Press [Enter] to start\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");

	scanf("%c", &enter); // ����Ű�� �Է¹ޱ� ���� char������ �Է¹���  
	system("cls"); 
	FILE* infile = fopen("board.txt", "r"); // �ʱ� ���� ������ �б���� ���� ���� ������ ���� ���� �� fopen �Լ�  
	if (infile == NULL) { // ������ ���� ���ϴ� ��� error ǥ��  
		printf("File Open Error! Game End...");
		return 0;
	}
	for (i = 0; i < BOARD_SIZE; i++) { // fscanf �Լ��� BOARD_SIZE*BOARD_SIZE ��ŭ�� �迭�� �ν��ؿ�.  
		for (j = 0; j < BOARD_SIZE; j++) {
			fscanf(infile, "%d", &board[i][j]);
		}
	}

	while (turn > 0) { // ū while�� - turn�� 0�� �Ǹ� ����  
		turn--;
		
		if (turn == 0) break;
		
		 	
			
		do { // do while���� ����Ͽ� ���̽� 1(index ���� ���� ��)/ ���̽� 2(�������� ���� �� �ε���) �̸� �ٽ� �Է¹���. 
			
			Sleep(1000); //1�� ���� 
			system("cls"); // ȭ�� ����� 
			
			print_board(board, match_block, score);
			printf("*Remaining turns: %d\n", turn); // ���� ���� �� �˷���  
			printf("Swap...\n");
			printf("Block 1: "); 
			scanf("%d%d", &row1, &col1); // ��, �� ���� �Է¹���.  
			printf("Block 2: ");
			scanf("%d%d", &row2, &col2); // ��, �� ���� �Է¹���. 
			pos = check_position(board, row1, row2, col1, col2); // ��Ȳ�� ���� 0,1�� �����ϴ� int�� �Լ� 
			  
		} while ((pos == 1) && turn > 0); 
		system("cls");
		swap(&board[row1][col1], &board[row2][col2]); // ���������� do-while�� �������Դٸ� swap�Լ��� �ٲ��� 
		match_block[row1][col1] = 1, match_block[row2][col2] = 1; //match_block �̶�� �迭 ���� ���� �ε������� 0�� �ƴ� 1�� ��������.  
		print_board(board, match_block, score); //0 �̻��� ������ print_board �Լ����� ���������� �����.  
		Sleep(1000); 
		system("cls"); 
		clean_match_block(match_block); // match_block �迭 ���� ��� ���� 0���� �ʱ�ȭ. 
		while(1){ // ���ѷ����� check ���� ���� break�� �� �ְ� ������. 
			check = check_match_3(board, match_block); // check���� �� �� ���忡�� ȹ���� ������. (check���� 0�̶�� �� ���� ������ �Ѿ�ٴ� ���� �ǹ���.) 
			if(check==0) break;
			else system("cls");
			
			score += check; // score ���� ��� ����  
			print_board(board, match_block, score); 
			Sleep(1000);
			system("cls");
			empty_board(board, match_block); // ���� ����� ���� �Լ� ȣ�� 
			print_board(board, match_block, score);
			Sleep(1000);
			system("cls");
			rand_board(board, match_block); // ������ �κ��� ������ ä����.  
			print_board(board, match_block, score);
			clean_match_block(match_block); // ���� ������ �Ѿ�� �� match_block �迭�� 0���� �ʱ�ȭ����. 

		}
	}
	fclose(infile); // ���� �ݾ���.  
	Sleep(1000);  
	system("cls");  
	print_board(board, match_block, score); // while���� ���� = ���� ���� �ǹ�. 
	printf("** You've earned %d points! **", score); 
	return 0;
}

void print_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE], int score) { // board, match_block, score �� �Ű������� ������.  

	int i, j;
	int col, row;
	col = 0; row = 0;
	printf("Score : %d\n", score); //���� ���� �����.  
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if(match_block[i][j]>=1){ //match_block ���� 1�̸� ���������� ���.  
			set_color_red();
			printf("%d ", board[i][j]);
			reset_color();
			}
			else if(match_block[i][j]==-1){ //match_block ���� -1�̸� �������� ���.  
				printf("  ");
			}
			else printf("%d ", board[i][j]); // match_block ���� 0�̸� ���� ������ ���  
		}
		printf("| %d\n", row++);
	}
	printf("------------+\n");
	for (col = 0; col < BOARD_SIZE; col++) printf("%d ", col);
	printf("\n====================\n\n");
	
}

int check_position(int board[][6], int row1, int row2, int col1, int col2) {
	int error=0; //error ���θ� ó���ϴ� ����  
	if (col1 >= BOARD_SIZE || col1 < 0 || col2 >= BOARD_SIZE || col2 < 0 || row1 >= BOARD_SIZE || row1 < 0 || row2 >= BOARD_SIZE || row2 < 0) {
		error=1;
		printf("\n***Out of range! ***\n");	//���� ���  
	} // index ������ ����� error�� 1�� �ٲ��� 
	if ((col1 == col2 && sub(row1, row2)!=1) || (row1 == row2 && sub(col1, col2)!=1) ) {
		error=1;
		printf("\n ***They are not adjacent! ***\n"); //���� ���
	} // ���� ���̳� ���� ������ �Ÿ��� 2 �̻��� ��� error �� 1�� �ٲ���
	else if (col1!=col2 && row1!=row2) {
		error=1;
		printf("\n***They are not adjacent! ***\n"); //���� ���
	}  // ������ ������ ���� �� error �� 1�� �ٲ��� 
	else if ((col1 == col2) && (row1 == row2)) {
		error=1;
		printf("\n***They are not adjacent! ***\n"); //���� ���
	} //�� ���� ������ ���� �� error �� 1�� �ٲ��� 
	
	if(error==1) return 1; // ������ ������ 2���� error �� �ϳ��� �ɸ��� �Ǹ� 1�� ���� 
	else return 0;// ���������� �� ���� ó������ ��� 0���� ���� 
}

void swap(int* a, int* b) { //Swap �Լ�  
	int temp = *b;
	*b = *a;
	*a = temp;
}


void set_color_red() { //��� ���� ���������� �ٲ���.  
	printf("\033[1;31m");
}

void reset_color() { // ���� ������ �ٽ� �ٲ���.  
	printf("\033[0m");
}

void clean_match_block(int match_block[][BOARD_SIZE]){ // match_block �迭 ���� 0���� �ʱ�ȭ����.  
	int i,j;
	for(i=0; i<BOARD_SIZE; i++){
		
		for(j=0; j<BOARD_SIZE; j++){
			
			match_block[i][j] =0;
		}
	}
}

int check_match_3(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]){ // match_3 �� �ν��ϴ� �Լ�, board�� match_block�� sum(���帶�� �����ִ� ����)�� �Ű������� ������.  
	
	int i, j;
	int score_round = 0;

	for(i=0; i<BOARD_SIZE; i++){
		for(j=0; j<BOARD_SIZE-2; j++){ // ���� �࿡�� match_3 �˻�  
			if(board[i][j]==board[i][j+1]&&board[i][j+1]==board[i][j+2]){ // ���� ������ ���ӵ� 3�� ���� ���� ������ match_block�� ���� 
				match_block[i][j]=board[i][j];
				match_block[i][j+1]=board[i][j+1];
				match_block[i][j+2]=board[i][j+2];
			}
		}
	}	
	
	for(j=0; j<BOARD_SIZE; j++){
		for(i=0; i<BOARD_SIZE-2; i++){ // ���� ������ match_3 �˻�  
			if(board[i][j]==board[i+1][j]&&board[i+1][j]==board[i+2][j]){ // ���� �࿡�� ���ӵ� 3�� ���� ���� ������ match_block�� ����  
				match_block[i][j]=board[i][j];
				match_block[i+1][j]=board[i+1][j];
				match_block[i+2][j]=board[i+2][j];
			}
		}
	}				
	for(i=0; i<BOARD_SIZE; i++){ // match_block�� ����� ���� �� ������ = �̹� ������ ������.  
		for(j=0; j<BOARD_SIZE; j++){
			score_round += match_block[i][j];
		}
	}
	
	return score_round; // �� ���忡�� ȹ���� score�� ������.  
}

void empty_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]){ // board�� �������� ����ϱ� ���� match_block�� -1�� �ٲ���.  
	int i,j;
	for(i=0; i<BOARD_SIZE; i++){
		for(j=0; j<BOARD_SIZE; j++){
			if(match_block[i][j]>=1) match_block[i][j]=-1;  
		}
	}
	
}

void rand_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]){ // match_block ���� -1�� �ε����� �ν��ؼ� �� �κ��� ������ ä����.  
	int i,j;
	for(i=0; i<BOARD_SIZE; i++){
		for(j=0; j<BOARD_SIZE; j++){
			
			if(match_block[i][j] == -1){
				board[i][j] = rand() % 5+1; // 1~5������ ������ ä����.  
			}
		}
	}
	
}


int sub(int a, int b){
	if(a>=b) return a-b;
	else return b-a;
}

