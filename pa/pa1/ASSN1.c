#define _CRT_SECURE_NO_WARNINGS

// 20210716 최대현 assn1
// 개발환경은 dev-C++을 사용하였습니다.  

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int print_menu(); // 메뉴를 출력하는 함수 
int rescan_menu(); // 메뉴를 다시 입력받는 함수 
int game_info(); //게임의 규칙을 설명하는 함수 
int game_start(); // 게임을 시작하는 함수 
void print_drink(int user_pos, int user_count, int comp_count); //주량을 출력하는 함수 
void print_map(int user_pos); //user의 위치가 포함된 맵을 출력하는 함수  
char set_position(int user_pos, int pos);
int play_juru(int user_pos); // 과제에서는 void형으로 제시했지만, int형으로 바꾸어서 사용하였습니다.  
int game_369(); // 369 게임을 진행하는 함수  
int game_31(); // 배스킨라빈스 31 게임을 진행하는 함수  
int mission(); //미션 칸에 도달했을 때 369게임과 배스킨라빈스 31 게임을 랜덤으로 진행하는 함수  
int game_end(int user_pos, int user_count, int comp_count); //게임이 끝나는 조건에서 호출되어 게임을 종료하는 함수  


int print_menu() {
    int menu_num;
    printf("[주루마블]\n");
    printf("=======================================\n");
    printf("1. 게임 설명\n");
    printf("2. 게임 시작\n");
    printf("3. 게임 종료\n");
    printf("=======================================\n");
    printf("입력: ");
    scanf("%d", &menu_num);
    return menu_num;

}

int rescan_menu() {
    int menu_num = print_menu();
    while (menu_num < 1 || menu_num > 3) { 
        system("cls");
        printf("메뉴를 다시 입력하세요.\n");
        menu_num = print_menu();
    }
    return menu_num;
}


int main() {

    srand(time(NULL));
    int a = 1;
    int menu_num;
    int info, start;

    while (a == 1) {
        info, start = 0;
        menu_num = 0;
        menu_num = print_menu();
        if (menu_num < 1 || menu_num>3) { // 메뉴에서 1~3 번이 아닌 경우 다시 입력하도록 함.  
            system("cls");
            printf("메뉴를 다시 입력하세요.\n");
            menu_num = rescan_menu();

        }

        switch (menu_num) {

        case 1:   //메뉴에서 1을 선택했을 경우 화면을 지우고 게임 규칙 설명 
            system("cls");
            info = game_info();
            break;

        case 2:  //메뉴에서 2를 선택했을 경우 화면을 지우고 게임 시작  
            system("cls");
            start = game_start();
            break;

        case 3: //메뉴에서 3을 선택했을 경우 게임 종료 
            printf("프로그램을 종료합니다...");
            a = 0;
            break;
        }

    }
    return 0;
}


int game_start() {
    int user_pos = 0; // user의 위치 
    int comp_pos = 0; // 컴퓨터의 위치 
    int user_count = 0; //user의 주량 
    int comp_count = 0; // 컴퓨터의 주량 
    int choice; //user가 주사위를 굴리거나, 원하는 칸을 입력하거나, 게임을 포기할 때 입력받는 변수  
    int dice;
    int round = 1; //게임의 라운드, 처음 시작할 때 1이므로 1로 초기화  
    int juru_result; // play_juru 함수의 결과 (주량)반환 

    system("cls");
    printf("[주루마블 게임]\n"); // 초기 화면  
    printf("=======================================\n");
    printf("+--------+--------+--------+--------+\n");
    printf("| 미션   | 찬스   | 일반   | 휴식   |\n");
    printf("+--------+--------+--------+--------+\n");
    printf("| 일반   |                 | 일반   |\n");
    printf("+--------+                 +--------+\n");
    printf("| 일반   |                 | 일반   |\n");
    printf("+--------+--------+--------+--------+\n");
    printf("| 시작 0 | 일반   | 찬스   | 미션   |\n");
    printf("+--------+--------+--------+--------+\n");
    printf("=======================================\n");
    printf("[USER - 0] ( 0/14)\n");
    printf("□□□□□□□□□□□□□□□\n\n");
    printf("[COMP - 0] ( 0/14)\n");
    printf("□□□□□□□□□□□□□□□\n");
    printf("=======================================\n\n");
    printf("주사위를 굴리시겠습니까?(0-굴림, -1-게임포기)\n");

    while (user_count < 14 && comp_count < 14) { // 한 쪽의 주량이 14잔이 되면 게임 끝 

        scanf("%d", &choice);
        while (choice < -1 || choice > 6) {
            scanf("%d", &choice);
        }
        if (choice == -1) {
            system("cls"); //-1을 리턴하고 game_start() 함수 종료  
            return -1;
        }
        else if (choice == 0) {
            dice = rand() % 6 + 1; //난수 생성 
        }
        else if (choice >= 1 && choice <= 6) {
            dice = choice;
        }

        system("cls");
        printf("=======================================\n");
        printf("▶▶▶ ROUND %d ▶▶▶▶▶▶▶▶▶▶▶▶\n", round); // 라운드 출력  
        printf("=======================================\n");
        printf("[USER's Turn]\n");
        printf("---------------------------------------\n");
        printf("주사위 눈 : %d\n\n", dice);
        user_pos = (user_pos + dice) % 12;
        print_map(user_pos);
        juru_result = play_juru(user_pos); // play_juru 함수의 리턴값을 받아옴  
        if (juru_result == 1) {
            user_count++;
        }
        else if (juru_result == 3) {
            user_count = user_count + 3;
        }
        else if (juru_result == 4) {
            user_count = user_count + 4;
        }
        else if (juru_result == -4) {
            comp_count = comp_count + 4;
        }
        else if (juru_result == -2) {
            if (user_count <= 2) user_count = 0; //주량이 -값이 될수는 없음 
            else user_count = user_count - 2;
        }


        if (user_count >= 14) break;   // user가 14잔 이상 마시면 나감.  
        else if (comp_count >= 14) break; //computer가 14잔 이상 마시면 나감. 

        comp_pos++;
        printf("[COMPUTER's Turn]\n");
        printf("---------------------------------------\n");

        if (user_pos == 3 || user_pos == 9) { //user가 미션 칸에 도달한 뒤 미션을 수행하면 컴퓨터는 1잔을 마시는 일 없이 턴이 넘어감.  
            printf("COMPUTER가 0잔 마시게 되었습니다.\n");
        }

        else if (comp_pos != 3 || comp_pos != 9) {
            printf("COMPUTER가 1잔 마시게 되었습니다.\n");
            comp_count++;
        }



        if (user_count >= 14) break;   // user가 14잔 이상 마시면 나감.  
        else if (comp_count >= 14) break; //computer가 14잔 이상 마시면 나감. 


        round++;
        print_drink(user_pos, user_count, comp_count);
        printf("\n주사위를 굴리시겠습니까?(0-굴림, -1-게임포기)\n");

    }
    print_drink(user_pos, user_count, comp_count); //while문을 종료했을 때 주량을 출력하고 게임 종료 함수를 호출 
    return game_end(user_pos, user_count, comp_count); // 정상적으로 게임을 종료한다면 -1이 리턴됨 


}





int game_info() {

    int go_main_menu = 0;

    while (go_main_menu != -1) { //-1이면 while문 빠져나옴 
        system("cls");
        printf("=============================== 주루마불 게임 설명 ===============================\n\n");
        printf("1. USER는 매턴 주사위를 던진다. 주사위를 던질 때 주사위의 눈은 플레이어가 결정한다.\n\n");
        printf("2. COMPUTER는 주사위를 던지지 않으며 매턴 1잔의 술을 마신다.\n\n");
        printf("3. USER와 COMPUTER의 주량은 소주 2병(14잔)이며, 14잔을 먼저 마신 쪽이 패배한다.\n\n");
        printf("4. 보드 칸은 5가지 칸으로 이루어져있으며 USER는 각 칸의 요구사항을 만족시켜야한다.\n\n");
        printf("==================================================================================\n\n");
        printf("메인 메뉴로 돌아가기(-1):");

        scanf("%d", &go_main_menu);

        if (go_main_menu == -1) {
            system("cls");
            return go_main_menu;
        }
    }

}


void print_drink(int user_pos, int user_count, int comp_count) {
    int i; // for문을 돌리는 인자 
    if (user_count >= 14) user_count = 14; // 주량은 최대 14잔까지임.  
    else if (comp_count >= 14) comp_count = 14;
    if (user_count >= 14 || comp_count >= 14) printf("\n\n게임이 종료되었습니다.\n");
    else printf("\n");
    printf("=======================================\n");
    printf("[USER - %d] ( %d/14)\n", user_pos, user_count);

    for (i = 1; i <= user_count; i++) {
        printf("■");
    }
    for (i = 1; i <= (14 - user_count); i++) {
        printf("□");

    }
    printf("\n\n");

    printf("[COMP - 0] ( %d/14)\n", comp_count);

    for (i = 1; i <= comp_count; i++) {
        printf("■");
    }
    for (i = 1; i <= (14 - comp_count); i++) {
        printf("□");

    }
    printf("\n");
    printf("=======================================\n");
}

void print_map(int user_pos) {

    char pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10, pos11;

    pos0 = set_position(user_pos, 0);
    pos1 = set_position(user_pos, 1);
    pos2 = set_position(user_pos, 2);
    pos3 = set_position(user_pos, 3);
    pos4 = set_position(user_pos, 4);
    pos5 = set_position(user_pos, 5);
    pos6 = set_position(user_pos, 6);
    pos7 = set_position(user_pos, 7);
    pos8 = set_position(user_pos, 8);
    pos9 = set_position(user_pos, 9);
    pos10 = set_position(user_pos, 10);
    pos11 = set_position(user_pos, 11);

    printf("+--------+--------+--------+--------+\n");
    printf("| 미션 %c | 찬스 %c | 일반 %c | 휴식 %c |\n", pos9, pos8, pos7, pos6);
    printf("+--------+--------+--------+--------+\n");
    printf("| 일반 %c |                 | 일반 %c |\n", pos10, pos5);
    printf("+--------+                 +--------+\n");
    printf("| 일반 %c |                 | 일반 %c |\n", pos11, pos4);
    printf("+--------+--------+--------+--------+\n");
    printf("| 시작 %c | 일반 %c | 찬스 %c | 미션 %c |\n", pos0, pos1, pos2, pos3);
    printf("+--------+--------+--------+--------+\n\n");

}

char set_position(int user_pos, int pos) {
    if (user_pos != pos) {
        return ' ';
    }
    else return '0';
}

int mission() {
    int play_game = rand() % 2; // 랜덤함수의 값을 0또는 1이 나오게 함. 
    if (play_game == 0) { // 0이면 369 게임  
        int result_369 = game_369();
        if (result_369 == 1) return 1;  //user가 이기면 1 반환 
        else return 0; //컴퓨터가 이기면 0 반환 
    }

    else if (play_game == 1) {
        int result_31 = game_31(); // 1이면 배스킨라빈스 게임 
        if (result_31 == 1) return 1; //user가 이기면 1 반환 
        else return 0; // 컴퓨터가 이기면 0 반환 

    }




}


int game_369() {
    int cnt; // 몇 번째 턴인지를 나타냄.  
    int choose_turn;
    //int win_or_lose = 1; // 1로 초기화하고, 지는 상황에 0으로 변수값이 바뀜. 
    int user_num;
    printf("369게임이 선택되었습니다.\n");
    printf("---------------------------------------\n");
    printf("★★★★★ 369 게임 ★★★★★\n");
    printf("---------------------------------------\n");
    choose_turn = rand() % 2; // 0이면 컴퓨터가 먼저, 1이면 유저가 먼저

    if (choose_turn == 0) { //컴퓨터의 턴이 먼저 시작되는 경우의 게임  
        for (cnt = 1; cnt <= 21; cnt++) {
            if (cnt % 2 == 1 && cnt % 10 == 3 || cnt % 10 == 9) { // 컴퓨터의 박수 턴  
                printf("COMP >> 0\n");
            }

            else if (cnt % 2 == 1) { // 컴퓨터의 일반수 턴  
                printf("COMP >> %d\n", cnt);
            }

            else if (cnt % 2 == 0 && cnt % 10 == 0) { //user의 10의 배수 턴 
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != 0) { //박수를 쳐야 하는데 치지 않은 경우  
                    cnt = 23; // while문을 벗어나며 21이 아닌 수 > 패배로 처리하도록 함.  

                }
            }

            else if (cnt % 2 == 0 && cnt % 10 == 6) { //user의 박수 턴 
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != 0) { //박수를 쳐야 하는데 치지 않은 경우  
                    cnt = 23; // for문을 벗어나며 21이 아닌 수 > 패배로 처리하도록 함.  

                }
            }

            else if (cnt % 2 == 0) {	// user의 일반수 턴 
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != cnt) { // 수를 다르게 친 경우  
                    cnt = 23; // for문을 벗어나며 21이 아닌 수 > 패배로 처리하도록 함.

                }
            }
        }
        // 정상적으로 모든 턴이 진행됐을경우 cnt값 22  
        if (cnt == 22) {
            printf("---------------------------------------\n");
            printf("USER가 승리하였습니다. \n");
            printf("COMPUTER가 4잔 마시게 되었습니다. \n\n");
            return 1; // user의 승리 : 1 반환 
        }

        else {
            printf("---------------------------------------\n");
            printf("COMPUTER가 승리하였습니다. \n");
            printf("USER가 4잔 마시게 되었습니다. \n\n");

            return 0; // 컴퓨터의 승리 : 0 반환 
        }
    }

    else { // user가 먼저 시작하는 경우의 게임  
        for (cnt = 1; cnt <= 21; cnt++) {
            if (cnt % 2 == 0 && cnt % 10 == 6 || cnt % 10 == 0) { // 컴퓨터의 박수 턴  
                printf("COMP >> 0\n");
            }

            else if (cnt % 2 == 0) { // 컴퓨터의 일반수 턴  
                printf("COMP >> %d\n", cnt);
            }

            else if (cnt % 2 == 1 && cnt % 10 == 3 || cnt % 10 == 9) { //user의 박수 턴 
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != 0) {
                    cnt = 23; // while문을 벗어나며 21이 아닌 수 > 패배로 처리하도록 함.  

                }
            }

            else if (cnt % 2 == 1) { //user의 일반수 턴  
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != cnt) {
                    cnt = 23; // while문을 벗어나며 21이 아닌 수 > 패배로 처리하도록 함.  

                }
            }

        }
        // 정상적으로 모든 턴이 진행됐을경우 cnt값 22  
        if (cnt == 22) {
            printf("---------------------------------------\n");
            printf("USER가 승리하였습니다. \n");
            printf("COMPUTER가 4잔 마시게 되었습니다. \n\n");
            return 1;
        }

        else {
            printf("---------------------------------------\n");
            printf("COMPUTER가 승리하였습니다. \n");
            printf("USER가 4잔 마시게 되었습니다. \n\n");

            return 0;
        }
    }
}

int game_31() { // 배스킨라빈스 31 게임 
    int cnt = 1; //while문을 계속해서 돌려주며  
    int choose_turn;
    int whos_turn = 1;
    int num_31;
    int coms_num;
    choose_turn = rand() % 2; //누가 먼저 시작하는지에 대한 난수 생성 
    printf("베스킨라빈스 게임이 선택되었습니다.\n");
    printf("--------------------------------------\n");
    printf("★★★★★ 베스킨라빈스 게임 ★★★★★\n");
    printf("--------------------------------------\n");

    if (choose_turn == 1) { // user의 턴이 먼저 시작되는 게임 
        while (cnt <= 31) {
            if (whos_turn % 2 == 1) { // user의 턴이면 1로 받아서 입력받고, computer의 턴이면 0으로 받아서 출력.  
                printf("USER >> ");
                scanf("%d", &num_31); // 몇 개 입력받을 것인지를 받는 변수  
                if (num_31 < 1 || num_31 >= 4) {
                    printf("WRONG INPUT");
                }

                else {
                    for (int i = 1; i <= num_31; i++) {
                        printf("%d ", cnt);
                        cnt++;
                        if (cnt == 32) break; // 31까지만 받고 탈출할 것 
                    }
                    whos_turn++;
                }

                printf("\n");
            }

            else if (whos_turn % 2 == 0) {
                coms_num = rand() % 3 + 1;
                printf("COMP >> %d \n", coms_num);
                for (int i = 1; i <= coms_num; i++) { //C99에서만 허용되는 문법입니다.  
                    printf("%d ", cnt);
                    cnt++;
                    if (cnt == 32) break; // 31까지만 받고 탈출할 것
                }
                whos_turn++;
                printf("\n");
            }


        }
        if (whos_turn % 2 == 1) {
            printf("--------------------------------------\n");
            printf("USER가 승리하였습니다.\n");
            printf("COMPUTER가 4잔 마시게 되었습니다.\n\n");
            return 1; // user 승리시 0을 반환 
        }

        else if (whos_turn % 2 == 0) {
            printf("--------------------------------------\n");
            printf("COMPUTER가 승리하였습니다.\n");
            printf("USER가 4잔 마시게 되었습니다.\n\n");
            return 0; // computer 승리시 0을 반환 
        }

    }

    else if (choose_turn == 0) { // computer의 턴이 먼저 시작되는 게임 
        while (cnt <= 31) {
            if (whos_turn % 2 == 0) { // user의 턴이면 0으로 받아서 입력받고, computer의 턴이면 1로 받아서 출력.  
                printf("USER >> ");
                scanf("%d", &num_31);  // 몇 개 입력받을 것인지를 받는 변수  
                if (num_31 < 1 || num_31 >= 4) {
                    printf("WRONG INPUT");
                }

                else {
                    for (int i = 1; i <= num_31; i++) {
                        printf("%d ", cnt);
                        cnt++;
                        if (cnt == 32) break; // 31까지만 받고 탈출할 것  
                    }
                    whos_turn++;
                }

                printf("\n");
            }

            else if (whos_turn % 2 == 1) {
                coms_num = rand() % 3 + 1;
                printf("COMP >> %d \n", coms_num);
                for (int i = 1; i <= coms_num; i++) {
                    printf("%d ", cnt);
                    cnt++;
                    if (cnt == 32) break; // 31까지만 받고 탈출할 것
                }
                whos_turn++;
                printf("\n");
            }


        }
        if (whos_turn % 2 == 0) {
            printf("--------------------------------------\n");
            printf("USER가 승리하였습니다.\n");
            printf("COMPUTER가 4잔 마시게 되었습니다.\n\n");
            return 1; // user 승리시 1을 반환 
        }

        else if (whos_turn % 2 == 1) {
            printf("--------------------------------------\n");
            printf("COMPUTER가 승리하였습니다.\n");
            printf("USER가 4잔 마시게 되었습니다.\n\n");

            return 0; // computer 승리시 0을 반환 
        }

    }
}



int play_juru(int user_pos) {
    int count = 0; // 추가할 주량  ]
    int chance_card;
    //   int mission_result, chance_result;
    int mission_result;
    switch (user_pos) {

    case 0:
        printf("시작 칸에 도착하였습니다.\n");
        printf("이번 턴은 아무것도 하지 않습니다.\n\n");
        break;


    case 1:
        printf("일반 칸에 도착하였습니다.\n");
        printf("USER가 1잔 마시게 되었습니다.\n\n");
        count = 1;
        break;



    case 2:
        printf("찬스 칸에 도착하였습니다.\n");
        chance_card = rand() % 2;
        if (chance_card == 0) {
            printf("'세잔 더!' 카드를 뽑았습니다.\n");
            printf("USER가 3잔 마시게 되었습니다.\n\n");
            count = 3;
        }
        else {
            printf("'여명808' 카드를 뽑았습니다.\n");
            printf("USER가 -2잔 마시게 되었습니다.\n\n");
            count = -2;
        }
        break;


    case 3:
        printf("미션 칸에 도착하였습니다.\n");
        mission_result = mission();
        if (mission_result == 1) count = -4; //USER 승리 시 1이 반환되므로 컴퓨터의 주량 4 추가(-4로 임의로 표시하였음) 
        else count = 4; // USER 패배시 0이 반환되므로 4인 경우 drink 함수에 USER 주량을 4잔 추가 
        break;


    case 4:
        printf("일반 칸에 도착하였습니다.\n");
        printf("USER가 1잔 마시게 되었습니다.\n\n");
        count = 1;
        break;

    case 5:
        printf("일반 칸에 도착하였습니다.\n");
        printf("USER가 1잔 마시게 되었습니다.\n\n");
        count = 1;
        break;

    case 6:
        printf("휴식 칸에 도착하였습니다.\n");
        printf("이번 턴은 아무것도 하지 않습니다.\n\n");
        break;

    case 7:
        printf("일반 칸에 도착하였습니다.\n");
        printf("USER가 1잔 마시게 되었습니다.\n\n");
        count = 1;
        break;

    case 8:
        printf("찬스 칸에 도착하였습니다.\n");
        chance_card = rand() % 2; //찬스 카드를 2가지 난수로 설정  
        if (chance_card == 0) { //0인 경우 세잔 더 카드 
            printf("'세잔 더!' 카드를 뽑았습니다.\n");
            printf("USER가 3잔 마시게 되었습니다.\n\n");
            count = 3;
        }
        else { // 1인 경우 여명 808 카드 
            printf("'여명808' 카드를 뽑았습니다.\n");
            printf("USER가 -2잔 마시게 되었습니다.\n\n");
            count = -2;
        }
        break;

    case 9:
        printf("미션 칸에 도착하였습니다.\n");
        mission_result = mission();
        if (mission_result == 1) count = -4;
        else count = 4;
        break;

    case 10:
        printf("일반 칸에 도착하였습니다.\n");
        printf("USER가 1잔 마시게 되었습니다.\n\n");
        count = 1;
        break;

    case 11:
        printf("일반 칸에 도착하였습니다.\n");
        printf("USER가 1잔 마시게 되었습니다.\n\n");
        count = 1;
        break;

    }
    return count;
}

int game_end(int user_pos, int user_count, int comp_count) { // game의 종료 결과를 출력하는 함수  

    int go_main_menu = 0;
    if (user_count > comp_count) user_count = 14;
    else comp_count = 14;
    if (user_count == 14) printf("* 결과 COMPUTER가 승리했습니다.\n\n");
    else printf("*결과 USER가 승리했습니다.\n\n"); 

    while (go_main_menu != -1) {
        printf("메인 메뉴로 돌아가기 (-1):"); // -1 이외 값은 고려하지 않음  
        scanf("%d", &go_main_menu);
        if (go_main_menu == -1) {
            system("cls");
            return go_main_menu;
        }
    }

}
