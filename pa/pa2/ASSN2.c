// 20210716 최대현 ASSN2, 개발환경은 Dev-C++을 주로 사용하였습니다.  
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 6 
#include<stdio.h>
#include<stdlib.h>	
#include<time.h> 
void print_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE], int score); //board를 출력해주는 함수. 빨간색으로 출력, 비어있게 출력하는 모든 기능을 한 번에 구현함.  
int check_position(int board[][BOARD_SIZE], int col1, int col2, int row1, int row2); // 사용자가 바꿔주고자 하는 두 값이 붙어있고, 배열 범위 내에 있는지 체크해주는 함수. 
void set_color_red(); // 빨간색으로 출력할 수 있게 해주는 함수. 
void reset_color(); // 빨간색으로 바뀌었던 출력 색을 다시 되돌려줌.  
void clean_match_block(int match_block[][BOARD_SIZE]); //match_block 배열 내의 모든 값을 0으로 초기화. 
void swap(int* a, int* b); // call by address 기법으로 두 값을 바꾸어줌.  
void empty_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]); //공백 출력해야 하는 인덱스 값을 인식하고 그에 해당하는 match_block 배열 값을 -1로 전환, 추후 print_board에서 -1을 인식해서 공백으로 출력.   
int check_match_3(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]); //match_3 상황을 인식하여 match_block 배열에 값을 전달하는 함수 
void rand_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]); //배열이 비어있음을 인식하고 그 값을 1~5 범위의 난수로 다시 채워주는 함수 
int sub(int a, int b);

int main(){
	char enter;
	int board[BOARD_SIZE][BOARD_SIZE] = {0}; //이번 게임의 보드 역할을 해 주는 2차원 배열 
	int match_block[BOARD_SIZE][BOARD_SIZE]= {0}; // 보드에서 필요한 부분의 배열 값을 복사해서 가져오거나, 공백 출력/ 빨간색 출력을 인식하는 등의 역할 
	int col1, col2, row1, row2, i, j, score, check;  
	check=1;
	score = 0;
	int turn = 6; // turn값을 처음에 빼 주기 때문에 6으로 선언  
	int pos = 0;
	srand(time(NULL));
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED 101\n");
	printf("Assignment 2\n\n");
	printf("[[ Match-3 Game ]]\n\n");
	printf("Press [Enter] to start\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");

	scanf("%c", &enter); // 엔터키를 입력받기 위해 char형으로 입력받음  
	system("cls"); 
	FILE* infile = fopen("board.txt", "r"); // 초기 보드 파일을 읽기모드로 여는 파일 포인터 변수 선언 및 fopen 함수  
	if (infile == NULL) { // 파일을 열지 못하는 경우 error 표시  
		printf("File Open Error! Game End...");
		return 0;
	}
	for (i = 0; i < BOARD_SIZE; i++) { // fscanf 함수로 BOARD_SIZE*BOARD_SIZE 만큼의 배열을 인식해옴.  
		for (j = 0; j < BOARD_SIZE; j++) {
			fscanf(infile, "%d", &board[i][j]);
		}
	}

	while (turn > 0) { // 큰 while문 - turn이 0이 되면 종료  
		turn--;
		
		if (turn == 0) break;
		
		 	
			
		do { // do while문을 사용하여 케이스 1(index 범위 밖의 수)/ 케이스 2(인접하지 않은 두 인덱스) 이면 다시 입력받음. 
			
			Sleep(1000); //1초 지연 
			system("cls"); // 화면 지우기 
			
			print_board(board, match_block, score);
			printf("*Remaining turns: %d\n", turn); // 현재 남은 턴 알려줌  
			printf("Swap...\n");
			printf("Block 1: "); 
			scanf("%d%d", &row1, &col1); // 행, 열 값을 입력받음.  
			printf("Block 2: ");
			scanf("%d%d", &row2, &col2); // 행, 열 값을 입력받음. 
			pos = check_position(board, row1, row2, col1, col2); // 상황에 따라 0,1을 리턴하는 int형 함수 
			  
		} while ((pos == 1) && turn > 0); 
		system("cls");
		swap(&board[row1][col1], &board[row2][col2]); // 정상적으로 do-while문 빠져나왔다면 swap함수로 바꿔줌 
		match_block[row1][col1] = 1, match_block[row2][col2] = 1; //match_block 이라는 배열 내의 같은 인덱스값에 0이 아닌 1을 대입해줌.  
		print_board(board, match_block, score); //0 이상의 수여야 print_board 함수에서 빨간색으로 출력함.  
		Sleep(1000); 
		system("cls"); 
		clean_match_block(match_block); // match_block 배열 내의 모든 값을 0으로 초기화. 
		while(1){ // 무한루프를 check 값에 따라 break할 수 있게 설계함. 
			check = check_match_3(board, match_block); // check값은 곧 그 라운드에서 획득한 점수임. (check값이 0이라면 곧 다음 턴으로 넘어간다는 것을 의미함.) 
			if(check==0) break;
			else system("cls");
			
			score += check; // score 값을 계속 저장  
			print_board(board, match_block, score); 
			Sleep(1000);
			system("cls");
			empty_board(board, match_block); // 공백 출력을 위한 함수 호출 
			print_board(board, match_block, score);
			Sleep(1000);
			system("cls");
			rand_board(board, match_block); // 공백인 부분을 난수로 채워줌.  
			print_board(board, match_block, score);
			clean_match_block(match_block); // 다음 턴으로 넘어가기 전 match_block 배열을 0으로 초기화해줌. 

		}
	}
	fclose(infile); // 파일 닫아줌.  
	Sleep(1000);  
	system("cls");  
	print_board(board, match_block, score); // while문을 나옴 = 게임 종료 의미. 
	printf("** You've earned %d points! **", score); 
	return 0;
}

void print_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE], int score) { // board, match_block, score 값 매개변수로 가져옴.  

	int i, j;
	int col, row;
	col = 0; row = 0;
	printf("Score : %d\n", score); //현재 점수 출력함.  
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if(match_block[i][j]>=1){ //match_block 값이 1이면 빨간색으로 출력.  
			set_color_red();
			printf("%d ", board[i][j]);
			reset_color();
			}
			else if(match_block[i][j]==-1){ //match_block 값이 -1이면 공백으로 출력.  
				printf("  ");
			}
			else printf("%d ", board[i][j]); // match_block 값이 0이면 원래 색으로 출력  
		}
		printf("| %d\n", row++);
	}
	printf("------------+\n");
	for (col = 0; col < BOARD_SIZE; col++) printf("%d ", col);
	printf("\n====================\n\n");
	
}

int check_position(int board[][6], int row1, int row2, int col1, int col2) {
	int error=0; //error 여부를 처리하는 변수  
	if (col1 >= BOARD_SIZE || col1 < 0 || col2 >= BOARD_SIZE || col2 < 0 || row1 >= BOARD_SIZE || row1 < 0 || row2 >= BOARD_SIZE || row2 < 0) {
		error=1;
		printf("\n***Out of range! ***\n");	//문장 출력  
	} // index 범위를 벗어나면 error값 1로 바꿔줌 
	if ((col1 == col2 && sub(row1, row2)!=1) || (row1 == row2 && sub(col1, col2)!=1) ) {
		error=1;
		printf("\n ***They are not adjacent! ***\n"); //문장 출력
	} // 같은 행이나 열에 있지만 거리가 2 이상인 경우 error 값 1로 바꿔줌
	else if (col1!=col2 && row1!=row2) {
		error=1;
		printf("\n***They are not adjacent! ***\n"); //문장 출력
	}  // 완전히 떨어져 있을 때 error 값 1로 바꿔줌 
	else if ((col1 == col2) && (row1 == row2)) {
		error=1;
		printf("\n***They are not adjacent! ***\n"); //문장 출력
	} //두 수가 완전히 같을 때 error 값 1로 바꿔줌 
	
	if(error==1) return 1; // 설명에서 제시한 2가지 error 중 하나라도 걸리게 되면 1을 리턴 
	else return 0;// 정상적으로 두 수가 처리됐을 경우 0으로 리턴 
}

void swap(int* a, int* b) { //Swap 함수  
	int temp = *b;
	*b = *a;
	*a = temp;
}


void set_color_red() { //출력 색을 빨간색으로 바꿔줌.  
	printf("\033[1;31m");
}

void reset_color() { // 원래 색으로 다시 바꿔줌.  
	printf("\033[0m");
}

void clean_match_block(int match_block[][BOARD_SIZE]){ // match_block 배열 값을 0으로 초기화해줌.  
	int i,j;
	for(i=0; i<BOARD_SIZE; i++){
		
		for(j=0; j<BOARD_SIZE; j++){
			
			match_block[i][j] =0;
		}
	}
}

int check_match_3(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]){ // match_3 을 인식하는 함수, board와 match_block과 sum(라운드마다 더해주는 점수)를 매개변수로 가져옴.  
	
	int i, j;
	int score_round = 0;

	for(i=0; i<BOARD_SIZE; i++){
		for(j=0; j<BOARD_SIZE-2; j++){ // 같은 행에서 match_3 검사  
			if(board[i][j]==board[i][j+1]&&board[i][j+1]==board[i][j+2]){ // 같은 열에서 연속된 3개 행의 값이 같으면 match_block에 복사 
				match_block[i][j]=board[i][j];
				match_block[i][j+1]=board[i][j+1];
				match_block[i][j+2]=board[i][j+2];
			}
		}
	}	
	
	for(j=0; j<BOARD_SIZE; j++){
		for(i=0; i<BOARD_SIZE-2; i++){ // 같은 열에서 match_3 검사  
			if(board[i][j]==board[i+1][j]&&board[i+1][j]==board[i+2][j]){ // 같은 행에서 연속된 3개 열의 값이 같으면 match_block에 복사  
				match_block[i][j]=board[i][j];
				match_block[i+1][j]=board[i+1][j];
				match_block[i+2][j]=board[i+2][j];
			}
		}
	}				
	for(i=0; i<BOARD_SIZE; i++){ // match_block에 저장된 값을 다 더해줌 = 이번 라운드의 점수임.  
		for(j=0; j<BOARD_SIZE; j++){
			score_round += match_block[i][j];
		}
	}
	
	return score_round; // 이 라운드에서 획득한 score를 리턴함.  
}

void empty_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]){ // board를 공백으로 출력하기 위해 match_block을 -1로 바꿔줌.  
	int i,j;
	for(i=0; i<BOARD_SIZE; i++){
		for(j=0; j<BOARD_SIZE; j++){
			if(match_block[i][j]>=1) match_block[i][j]=-1;  
		}
	}
	
}

void rand_board(int board[][BOARD_SIZE], int match_block[][BOARD_SIZE]){ // match_block 값이 -1인 인덱스를 인식해서 그 부분을 난수로 채워줌.  
	int i,j;
	for(i=0; i<BOARD_SIZE; i++){
		for(j=0; j<BOARD_SIZE; j++){
			
			if(match_block[i][j] == -1){
				board[i][j] = rand() % 5+1; // 1~5까지의 난수로 채워줌.  
			}
		}
	}
	
}


int sub(int a, int b){
	if(a>=b) return a-b;
	else return b-a;
}

