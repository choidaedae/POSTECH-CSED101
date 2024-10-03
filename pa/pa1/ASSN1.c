#define _CRT_SECURE_NO_WARNINGS

// 20210716 �ִ��� assn1
// ����ȯ���� dev-C++�� ����Ͽ����ϴ�.  

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int print_menu(); // �޴��� ����ϴ� �Լ� 
int rescan_menu(); // �޴��� �ٽ� �Է¹޴� �Լ� 
int game_info(); //������ ��Ģ�� �����ϴ� �Լ� 
int game_start(); // ������ �����ϴ� �Լ� 
void print_drink(int user_pos, int user_count, int comp_count); //�ַ��� ����ϴ� �Լ� 
void print_map(int user_pos); //user�� ��ġ�� ���Ե� ���� ����ϴ� �Լ�  
char set_position(int user_pos, int pos);
int play_juru(int user_pos); // ���������� void������ ����������, int������ �ٲپ ����Ͽ����ϴ�.  
int game_369(); // 369 ������ �����ϴ� �Լ�  
int game_31(); // �轺Ų��� 31 ������ �����ϴ� �Լ�  
int mission(); //�̼� ĭ�� �������� �� 369���Ӱ� �轺Ų��� 31 ������ �������� �����ϴ� �Լ�  
int game_end(int user_pos, int user_count, int comp_count); //������ ������ ���ǿ��� ȣ��Ǿ� ������ �����ϴ� �Լ�  


int print_menu() {
    int menu_num;
    printf("[�ַ縶��]\n");
    printf("=======================================\n");
    printf("1. ���� ����\n");
    printf("2. ���� ����\n");
    printf("3. ���� ����\n");
    printf("=======================================\n");
    printf("�Է�: ");
    scanf("%d", &menu_num);
    return menu_num;

}

int rescan_menu() {
    int menu_num = print_menu();
    while (menu_num < 1 || menu_num > 3) { 
        system("cls");
        printf("�޴��� �ٽ� �Է��ϼ���.\n");
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
        if (menu_num < 1 || menu_num>3) { // �޴����� 1~3 ���� �ƴ� ��� �ٽ� �Է��ϵ��� ��.  
            system("cls");
            printf("�޴��� �ٽ� �Է��ϼ���.\n");
            menu_num = rescan_menu();

        }

        switch (menu_num) {

        case 1:   //�޴����� 1�� �������� ��� ȭ���� ����� ���� ��Ģ ���� 
            system("cls");
            info = game_info();
            break;

        case 2:  //�޴����� 2�� �������� ��� ȭ���� ����� ���� ����  
            system("cls");
            start = game_start();
            break;

        case 3: //�޴����� 3�� �������� ��� ���� ���� 
            printf("���α׷��� �����մϴ�...");
            a = 0;
            break;
        }

    }
    return 0;
}


int game_start() {
    int user_pos = 0; // user�� ��ġ 
    int comp_pos = 0; // ��ǻ���� ��ġ 
    int user_count = 0; //user�� �ַ� 
    int comp_count = 0; // ��ǻ���� �ַ� 
    int choice; //user�� �ֻ����� �����ų�, ���ϴ� ĭ�� �Է��ϰų�, ������ ������ �� �Է¹޴� ����  
    int dice;
    int round = 1; //������ ����, ó�� ������ �� 1�̹Ƿ� 1�� �ʱ�ȭ  
    int juru_result; // play_juru �Լ��� ��� (�ַ�)��ȯ 

    system("cls");
    printf("[�ַ縶�� ����]\n"); // �ʱ� ȭ��  
    printf("=======================================\n");
    printf("+--------+--------+--------+--------+\n");
    printf("| �̼�   | ����   | �Ϲ�   | �޽�   |\n");
    printf("+--------+--------+--------+--------+\n");
    printf("| �Ϲ�   |                 | �Ϲ�   |\n");
    printf("+--------+                 +--------+\n");
    printf("| �Ϲ�   |                 | �Ϲ�   |\n");
    printf("+--------+--------+--------+--------+\n");
    printf("| ���� 0 | �Ϲ�   | ����   | �̼�   |\n");
    printf("+--------+--------+--------+--------+\n");
    printf("=======================================\n");
    printf("[USER - 0] ( 0/14)\n");
    printf("����������������\n\n");
    printf("[COMP - 0] ( 0/14)\n");
    printf("����������������\n");
    printf("=======================================\n\n");
    printf("�ֻ����� �����ðڽ��ϱ�?(0-����, -1-��������)\n");

    while (user_count < 14 && comp_count < 14) { // �� ���� �ַ��� 14���� �Ǹ� ���� �� 

        scanf("%d", &choice);
        while (choice < -1 || choice > 6) {
            scanf("%d", &choice);
        }
        if (choice == -1) {
            system("cls"); //-1�� �����ϰ� game_start() �Լ� ����  
            return -1;
        }
        else if (choice == 0) {
            dice = rand() % 6 + 1; //���� ���� 
        }
        else if (choice >= 1 && choice <= 6) {
            dice = choice;
        }

        system("cls");
        printf("=======================================\n");
        printf("������ ROUND %d ������������������������\n", round); // ���� ���  
        printf("=======================================\n");
        printf("[USER's Turn]\n");
        printf("---------------------------------------\n");
        printf("�ֻ��� �� : %d\n\n", dice);
        user_pos = (user_pos + dice) % 12;
        print_map(user_pos);
        juru_result = play_juru(user_pos); // play_juru �Լ��� ���ϰ��� �޾ƿ�  
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
            if (user_count <= 2) user_count = 0; //�ַ��� -���� �ɼ��� ���� 
            else user_count = user_count - 2;
        }


        if (user_count >= 14) break;   // user�� 14�� �̻� ���ø� ����.  
        else if (comp_count >= 14) break; //computer�� 14�� �̻� ���ø� ����. 

        comp_pos++;
        printf("[COMPUTER's Turn]\n");
        printf("---------------------------------------\n");

        if (user_pos == 3 || user_pos == 9) { //user�� �̼� ĭ�� ������ �� �̼��� �����ϸ� ��ǻ�ʹ� 1���� ���ô� �� ���� ���� �Ѿ.  
            printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n");
        }

        else if (comp_pos != 3 || comp_pos != 9) {
            printf("COMPUTER�� 1�� ���ð� �Ǿ����ϴ�.\n");
            comp_count++;
        }



        if (user_count >= 14) break;   // user�� 14�� �̻� ���ø� ����.  
        else if (comp_count >= 14) break; //computer�� 14�� �̻� ���ø� ����. 


        round++;
        print_drink(user_pos, user_count, comp_count);
        printf("\n�ֻ����� �����ðڽ��ϱ�?(0-����, -1-��������)\n");

    }
    print_drink(user_pos, user_count, comp_count); //while���� �������� �� �ַ��� ����ϰ� ���� ���� �Լ��� ȣ�� 
    return game_end(user_pos, user_count, comp_count); // ���������� ������ �����Ѵٸ� -1�� ���ϵ� 


}





int game_info() {

    int go_main_menu = 0;

    while (go_main_menu != -1) { //-1�̸� while�� �������� 
        system("cls");
        printf("=============================== �ַ縶�� ���� ���� ===============================\n\n");
        printf("1. USER�� ���� �ֻ����� ������. �ֻ����� ���� �� �ֻ����� ���� �÷��̾ �����Ѵ�.\n\n");
        printf("2. COMPUTER�� �ֻ����� ������ ������ ���� 1���� ���� ���Ŵ�.\n\n");
        printf("3. USER�� COMPUTER�� �ַ��� ���� 2��(14��)�̸�, 14���� ���� ���� ���� �й��Ѵ�.\n\n");
        printf("4. ���� ĭ�� 5���� ĭ���� �̷���������� USER�� �� ĭ�� �䱸������ �������Ѿ��Ѵ�.\n\n");
        printf("==================================================================================\n\n");
        printf("���� �޴��� ���ư���(-1):");

        scanf("%d", &go_main_menu);

        if (go_main_menu == -1) {
            system("cls");
            return go_main_menu;
        }
    }

}


void print_drink(int user_pos, int user_count, int comp_count) {
    int i; // for���� ������ ���� 
    if (user_count >= 14) user_count = 14; // �ַ��� �ִ� 14�ܱ�����.  
    else if (comp_count >= 14) comp_count = 14;
    if (user_count >= 14 || comp_count >= 14) printf("\n\n������ ����Ǿ����ϴ�.\n");
    else printf("\n");
    printf("=======================================\n");
    printf("[USER - %d] ( %d/14)\n", user_pos, user_count);

    for (i = 1; i <= user_count; i++) {
        printf("��");
    }
    for (i = 1; i <= (14 - user_count); i++) {
        printf("��");

    }
    printf("\n\n");

    printf("[COMP - 0] ( %d/14)\n", comp_count);

    for (i = 1; i <= comp_count; i++) {
        printf("��");
    }
    for (i = 1; i <= (14 - comp_count); i++) {
        printf("��");

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
    printf("| �̼� %c | ���� %c | �Ϲ� %c | �޽� %c |\n", pos9, pos8, pos7, pos6);
    printf("+--------+--------+--------+--------+\n");
    printf("| �Ϲ� %c |                 | �Ϲ� %c |\n", pos10, pos5);
    printf("+--------+                 +--------+\n");
    printf("| �Ϲ� %c |                 | �Ϲ� %c |\n", pos11, pos4);
    printf("+--------+--------+--------+--------+\n");
    printf("| ���� %c | �Ϲ� %c | ���� %c | �̼� %c |\n", pos0, pos1, pos2, pos3);
    printf("+--------+--------+--------+--------+\n\n");

}

char set_position(int user_pos, int pos) {
    if (user_pos != pos) {
        return ' ';
    }
    else return '0';
}

int mission() {
    int play_game = rand() % 2; // �����Լ��� ���� 0�Ǵ� 1�� ������ ��. 
    if (play_game == 0) { // 0�̸� 369 ����  
        int result_369 = game_369();
        if (result_369 == 1) return 1;  //user�� �̱�� 1 ��ȯ 
        else return 0; //��ǻ�Ͱ� �̱�� 0 ��ȯ 
    }

    else if (play_game == 1) {
        int result_31 = game_31(); // 1�̸� �轺Ų��� ���� 
        if (result_31 == 1) return 1; //user�� �̱�� 1 ��ȯ 
        else return 0; // ��ǻ�Ͱ� �̱�� 0 ��ȯ 

    }




}


int game_369() {
    int cnt; // �� ��° �������� ��Ÿ��.  
    int choose_turn;
    //int win_or_lose = 1; // 1�� �ʱ�ȭ�ϰ�, ���� ��Ȳ�� 0���� �������� �ٲ�. 
    int user_num;
    printf("369������ ���õǾ����ϴ�.\n");
    printf("---------------------------------------\n");
    printf("�ڡڡڡڡ� 369 ���� �ڡڡڡڡ�\n");
    printf("---------------------------------------\n");
    choose_turn = rand() % 2; // 0�̸� ��ǻ�Ͱ� ����, 1�̸� ������ ����

    if (choose_turn == 0) { //��ǻ���� ���� ���� ���۵Ǵ� ����� ����  
        for (cnt = 1; cnt <= 21; cnt++) {
            if (cnt % 2 == 1 && cnt % 10 == 3 || cnt % 10 == 9) { // ��ǻ���� �ڼ� ��  
                printf("COMP >> 0\n");
            }

            else if (cnt % 2 == 1) { // ��ǻ���� �Ϲݼ� ��  
                printf("COMP >> %d\n", cnt);
            }

            else if (cnt % 2 == 0 && cnt % 10 == 0) { //user�� 10�� ��� �� 
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != 0) { //�ڼ��� �ľ� �ϴµ� ġ�� ���� ���  
                    cnt = 23; // while���� ����� 21�� �ƴ� �� > �й�� ó���ϵ��� ��.  

                }
            }

            else if (cnt % 2 == 0 && cnt % 10 == 6) { //user�� �ڼ� �� 
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != 0) { //�ڼ��� �ľ� �ϴµ� ġ�� ���� ���  
                    cnt = 23; // for���� ����� 21�� �ƴ� �� > �й�� ó���ϵ��� ��.  

                }
            }

            else if (cnt % 2 == 0) {	// user�� �Ϲݼ� �� 
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != cnt) { // ���� �ٸ��� ģ ���  
                    cnt = 23; // for���� ����� 21�� �ƴ� �� > �й�� ó���ϵ��� ��.

                }
            }
        }
        // ���������� ��� ���� ���������� cnt�� 22  
        if (cnt == 22) {
            printf("---------------------------------------\n");
            printf("USER�� �¸��Ͽ����ϴ�. \n");
            printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�. \n\n");
            return 1; // user�� �¸� : 1 ��ȯ 
        }

        else {
            printf("---------------------------------------\n");
            printf("COMPUTER�� �¸��Ͽ����ϴ�. \n");
            printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n\n");

            return 0; // ��ǻ���� �¸� : 0 ��ȯ 
        }
    }

    else { // user�� ���� �����ϴ� ����� ����  
        for (cnt = 1; cnt <= 21; cnt++) {
            if (cnt % 2 == 0 && cnt % 10 == 6 || cnt % 10 == 0) { // ��ǻ���� �ڼ� ��  
                printf("COMP >> 0\n");
            }

            else if (cnt % 2 == 0) { // ��ǻ���� �Ϲݼ� ��  
                printf("COMP >> %d\n", cnt);
            }

            else if (cnt % 2 == 1 && cnt % 10 == 3 || cnt % 10 == 9) { //user�� �ڼ� �� 
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != 0) {
                    cnt = 23; // while���� ����� 21�� �ƴ� �� > �й�� ó���ϵ��� ��.  

                }
            }

            else if (cnt % 2 == 1) { //user�� �Ϲݼ� ��  
                printf("USER >> ");
                scanf("%d", &user_num);
                if (user_num != cnt) {
                    cnt = 23; // while���� ����� 21�� �ƴ� �� > �й�� ó���ϵ��� ��.  

                }
            }

        }
        // ���������� ��� ���� ���������� cnt�� 22  
        if (cnt == 22) {
            printf("---------------------------------------\n");
            printf("USER�� �¸��Ͽ����ϴ�. \n");
            printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�. \n\n");
            return 1;
        }

        else {
            printf("---------------------------------------\n");
            printf("COMPUTER�� �¸��Ͽ����ϴ�. \n");
            printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n\n");

            return 0;
        }
    }
}

int game_31() { // �轺Ų��� 31 ���� 
    int cnt = 1; //while���� ����ؼ� �����ָ�  
    int choose_turn;
    int whos_turn = 1;
    int num_31;
    int coms_num;
    choose_turn = rand() % 2; //���� ���� �����ϴ����� ���� ���� ���� 
    printf("����Ų��� ������ ���õǾ����ϴ�.\n");
    printf("--------------------------------------\n");
    printf("�ڡڡڡڡ� ����Ų��� ���� �ڡڡڡڡ�\n");
    printf("--------------------------------------\n");

    if (choose_turn == 1) { // user�� ���� ���� ���۵Ǵ� ���� 
        while (cnt <= 31) {
            if (whos_turn % 2 == 1) { // user�� ���̸� 1�� �޾Ƽ� �Է¹ް�, computer�� ���̸� 0���� �޾Ƽ� ���.  
                printf("USER >> ");
                scanf("%d", &num_31); // �� �� �Է¹��� �������� �޴� ����  
                if (num_31 < 1 || num_31 >= 4) {
                    printf("WRONG INPUT");
                }

                else {
                    for (int i = 1; i <= num_31; i++) {
                        printf("%d ", cnt);
                        cnt++;
                        if (cnt == 32) break; // 31������ �ް� Ż���� �� 
                    }
                    whos_turn++;
                }

                printf("\n");
            }

            else if (whos_turn % 2 == 0) {
                coms_num = rand() % 3 + 1;
                printf("COMP >> %d \n", coms_num);
                for (int i = 1; i <= coms_num; i++) { //C99������ ���Ǵ� �����Դϴ�.  
                    printf("%d ", cnt);
                    cnt++;
                    if (cnt == 32) break; // 31������ �ް� Ż���� ��
                }
                whos_turn++;
                printf("\n");
            }


        }
        if (whos_turn % 2 == 1) {
            printf("--------------------------------------\n");
            printf("USER�� �¸��Ͽ����ϴ�.\n");
            printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n\n");
            return 1; // user �¸��� 0�� ��ȯ 
        }

        else if (whos_turn % 2 == 0) {
            printf("--------------------------------------\n");
            printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
            printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n\n");
            return 0; // computer �¸��� 0�� ��ȯ 
        }

    }

    else if (choose_turn == 0) { // computer�� ���� ���� ���۵Ǵ� ���� 
        while (cnt <= 31) {
            if (whos_turn % 2 == 0) { // user�� ���̸� 0���� �޾Ƽ� �Է¹ް�, computer�� ���̸� 1�� �޾Ƽ� ���.  
                printf("USER >> ");
                scanf("%d", &num_31);  // �� �� �Է¹��� �������� �޴� ����  
                if (num_31 < 1 || num_31 >= 4) {
                    printf("WRONG INPUT");
                }

                else {
                    for (int i = 1; i <= num_31; i++) {
                        printf("%d ", cnt);
                        cnt++;
                        if (cnt == 32) break; // 31������ �ް� Ż���� ��  
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
                    if (cnt == 32) break; // 31������ �ް� Ż���� ��
                }
                whos_turn++;
                printf("\n");
            }


        }
        if (whos_turn % 2 == 0) {
            printf("--------------------------------------\n");
            printf("USER�� �¸��Ͽ����ϴ�.\n");
            printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n\n");
            return 1; // user �¸��� 1�� ��ȯ 
        }

        else if (whos_turn % 2 == 1) {
            printf("--------------------------------------\n");
            printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
            printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n\n");

            return 0; // computer �¸��� 0�� ��ȯ 
        }

    }
}



int play_juru(int user_pos) {
    int count = 0; // �߰��� �ַ�  ]
    int chance_card;
    //   int mission_result, chance_result;
    int mission_result;
    switch (user_pos) {

    case 0:
        printf("���� ĭ�� �����Ͽ����ϴ�.\n");
        printf("�̹� ���� �ƹ��͵� ���� �ʽ��ϴ�.\n\n");
        break;


    case 1:
        printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
        printf("USER�� 1�� ���ð� �Ǿ����ϴ�.\n\n");
        count = 1;
        break;



    case 2:
        printf("���� ĭ�� �����Ͽ����ϴ�.\n");
        chance_card = rand() % 2;
        if (chance_card == 0) {
            printf("'���� ��!' ī�带 �̾ҽ��ϴ�.\n");
            printf("USER�� 3�� ���ð� �Ǿ����ϴ�.\n\n");
            count = 3;
        }
        else {
            printf("'����808' ī�带 �̾ҽ��ϴ�.\n");
            printf("USER�� -2�� ���ð� �Ǿ����ϴ�.\n\n");
            count = -2;
        }
        break;


    case 3:
        printf("�̼� ĭ�� �����Ͽ����ϴ�.\n");
        mission_result = mission();
        if (mission_result == 1) count = -4; //USER �¸� �� 1�� ��ȯ�ǹǷ� ��ǻ���� �ַ� 4 �߰�(-4�� ���Ƿ� ǥ���Ͽ���) 
        else count = 4; // USER �й�� 0�� ��ȯ�ǹǷ� 4�� ��� drink �Լ��� USER �ַ��� 4�� �߰� 
        break;


    case 4:
        printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
        printf("USER�� 1�� ���ð� �Ǿ����ϴ�.\n\n");
        count = 1;
        break;

    case 5:
        printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
        printf("USER�� 1�� ���ð� �Ǿ����ϴ�.\n\n");
        count = 1;
        break;

    case 6:
        printf("�޽� ĭ�� �����Ͽ����ϴ�.\n");
        printf("�̹� ���� �ƹ��͵� ���� �ʽ��ϴ�.\n\n");
        break;

    case 7:
        printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
        printf("USER�� 1�� ���ð� �Ǿ����ϴ�.\n\n");
        count = 1;
        break;

    case 8:
        printf("���� ĭ�� �����Ͽ����ϴ�.\n");
        chance_card = rand() % 2; //���� ī�带 2���� ������ ����  
        if (chance_card == 0) { //0�� ��� ���� �� ī�� 
            printf("'���� ��!' ī�带 �̾ҽ��ϴ�.\n");
            printf("USER�� 3�� ���ð� �Ǿ����ϴ�.\n\n");
            count = 3;
        }
        else { // 1�� ��� ���� 808 ī�� 
            printf("'����808' ī�带 �̾ҽ��ϴ�.\n");
            printf("USER�� -2�� ���ð� �Ǿ����ϴ�.\n\n");
            count = -2;
        }
        break;

    case 9:
        printf("�̼� ĭ�� �����Ͽ����ϴ�.\n");
        mission_result = mission();
        if (mission_result == 1) count = -4;
        else count = 4;
        break;

    case 10:
        printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
        printf("USER�� 1�� ���ð� �Ǿ����ϴ�.\n\n");
        count = 1;
        break;

    case 11:
        printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
        printf("USER�� 1�� ���ð� �Ǿ����ϴ�.\n\n");
        count = 1;
        break;

    }
    return count;
}

int game_end(int user_pos, int user_count, int comp_count) { // game�� ���� ����� ����ϴ� �Լ�  

    int go_main_menu = 0;
    if (user_count > comp_count) user_count = 14;
    else comp_count = 14;
    if (user_count == 14) printf("* ��� COMPUTER�� �¸��߽��ϴ�.\n\n");
    else printf("*��� USER�� �¸��߽��ϴ�.\n\n"); 

    while (go_main_menu != -1) {
        printf("���� �޴��� ���ư��� (-1):"); // -1 �̿� ���� ������� ����  
        scanf("%d", &go_main_menu);
        if (go_main_menu == -1) {
            system("cls");
            return go_main_menu;
        }
    }

}
