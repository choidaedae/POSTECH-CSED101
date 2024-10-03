// 20210716 �ִ��� ASSN3
// Visual Studio 2019���� �����Ͽ����ϴ�. 

#define _CRT_SECURE_NO_WARNINGS
#define MAX_FILE_NAME 30
#define MAX_SIZE 1000

#include<stdio.h>
#include<stddef.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"mystring.h"

void print_menu(); // �޴��� ����ϴ� �Լ� 

char* process_str(char* str); //mystrlower + Ư�����ڸ� ���� ó���ϴ� �Լ� 
 
void dic_sort(char** words, int cnt_word, int* freq_spam, int* freq_ham); // ���������� words�� �����ϰ�, �� ������ ���� �� �󵵵��� ������ �ٲ���. 

void train(char** words, int* freq_spam, int* freq_ham, char* fname, int* ham, int* spam);

char* mystrlower(char* str);

int main() {

    int ham = 1; int spam = 1;
    char fname[MAX_FILE_NAME]; // file�̸�
    char com[10];
    char go_menu; // menu�� ���ư��� space�� �Է¹ޱ� ���� ���� 
    int error = 1; // ���� �ٱ� while���� ������ ���� 
    int cnt_word = 0; // �ܾ� ���� 
    int i = 0; // for�� ������ ���� 
    int k; // for�� ������ ���� 
    // int train_cnt = 0;
    char* tok; //strtok�� ���� �ɰ� ���ڿ��� �ӽ÷� �����ϴ� ���� 
    char** words = NULL; //�����Ҵ��ؼ� �����, �ܾ���� ��� 2���� �޸�
    int* freq_spam = NULL; // �����Ҵ��ؼ� �����, �ܾ���� spam label���� ������ �󵵸� ������ 1���� �޸�
    int* freq_ham = NULL; // �����Ҵ��ؼ� �����, �ܾ���� ham label���� ������ �󵵸� ������ 1���� �޸�

    while (error != 0) { // error = 0 �̸� ����� 

        while (1) { // ���ѷ����� break�� ���� ��������. 

            print_menu(); 
            scanf("%s", com);

            mystrlower(com); // ��ҹ��� ������� ö�ڰ� ������ ���� �Է¹���. 

            if (strcmp(com, "train") == 0) {

                ham = 0; spam = 0;
                printf("File name: ");
                scanf("%s", fname); // ���� �̸��� �Է¹��� 

                
                train(words, freq_spam, freq_ham, fname, &ham, &spam); //train ��Ŵ 
        
                system("cls"); 

            }

            else if (strcmp(com, "test") == 0) { //test�� �� 

                FILE* fp = fopen("stats.txt", "r"); //train�� ����� stats.txt�� �б� ���� ������. 

                if (fp == NULL) {  //stats.txt�� ���� �� 
                    printf("Error: File does not exist ");
                    Sleep(1000);
                    system("cls");
                    error = 1;
                    break;
                }

                int mem_size = 5;
                char str[1000];
                int i = 0;
                char* tok = NULL;

                // ���� �Ҵ� �κ�
                words = (char**)calloc(mem_size, sizeof(char*)); 
                freq_spam = (int*)calloc(mem_size, sizeof(int));
                freq_ham = (int*)calloc(mem_size, sizeof(int));


                fgets(str, 1000, fp); // �� �� �� �޾ƿ� 
                if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = NULL;

                tok = strtok(str, ":"); // : ������ ���� ���� ���� 

                tok = strtok(NULL, ":"); 
                ham = atoi(tok); // ������ ������ָ鼭 �������� �����  (��, ham�� ��)

                tok = strtok(NULL, ":"); // ���� ���� ���� ����  (spam�� ��)
                spam = atoi(tok);

                fgets(str, 1000, fp); // �� �� �޾ƿ� 

                if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = NULL; // enter ������ 

       
                while (strlen(str) >= 5) { // �޾ƿ� �� ���� ���̴� �ּ� 5�̴�. 

                    if (i >= mem_size) { 

                        mem_size *= 2; // �޸� ũ�⸦ 2��� �ø� 

                        words = (char**)realloc(words, mem_size * sizeof(char*)); // ���Ҵ� 
                        freq_spam = (int*)realloc(freq_spam, mem_size * sizeof(int));
                        freq_ham = (int*)realloc(freq_ham, mem_size * sizeof(int));

                        for (k = (mem_size / 2); k < mem_size; k++) { //realloc�� �κ��� 0���� �ʱ�ȭ 
                            *(freq_spam + k) = 0;
                            *(freq_ham + k) = 0;
                        }
                    }


               
                    tok = strtok(str, ","); 
                    *(words + i) = (char*)calloc(strlen(tok) + 1, sizeof(char));
                    strcpy(*(words + i), tok);


                    tok = strtok(NULL, ","); //, ������ �ɰ��� ham �� �־���
                    *(freq_ham + i) = atoi(tok); 

                    tok = strtok(NULL, ","); //, ������ �ɰ��� spam �� �־���  
                    *(freq_spam + i) = atoi(tok);

                    i++;


                    fgets(str, 1000, fp); // �� �� �޾ƿ� 
                    if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = NULL;
                }

                char sen[1000];
                char test_sen[1000];

                float p_ham = (float)ham / (ham + spam); //  p(ham)
                float p_spam = (float)spam / (ham + spam); //  p(spam)
                float con_ham_p = 1; float con_spam_p = 1; 
                float prob_ham = p_ham; float prob_spam = p_spam;
                char test_word[50][50] = { 0 }; // test�� ���ڿ��� �־��ִ� �迭 

             
              

                printf("Enter a message: ");
                rewind(stdin);

                fgets(sen, 100, stdin);

                if (sen[strlen(sen) - 1] == '\n') sen[strlen(sen) - 1] = NULL;

                strcpy(test_sen, sen);

               process_str(sen);


                tok = strtok(sen, " ");


                printf("\nP(Ham) = %.3f, P(Spam) = %.3lf\n", p_ham, p_spam); //  spam Ȯ���� ��� 


                int cnt = 1;

                while (tok != NULL) { // �ɰ� ���� ���� ������
   
                    if (strlen(tok) >= 2) { //�ܾ� ���̰� 2 �̻��� ��쿡�� ó�� 

                        for (k = 0; k < cnt; k++) {

                            if (strcmp(test_word[k], tok) == 0) break; // �Է��� ���� ���� �ߺ��Ǵ� �ܾ �ִٸ� while�� break 
                        }

                        if (k < cnt) {
                            tok = strtok(NULL, " "); //��ũ����¡ �� ���� while������ �Ѿ 
                            continue; 
                        }

                        else strcpy(test_word[k], tok); 

                        for (k = 0; k < i; k++) {

                            if (strcmp(*(words + k), tok) == 0) {
                                
                                break;
                            }

                        }

                            if (k < i) { 
                               

                                if (freq_ham[k] == 0) con_ham_p = 0.1 / ham;  //��迡 ���ԵǾ����� ������ 0�� ��� Ȯ�� ���� 0�� �ǹǷ�, �� ��� Ȯ�� ���� 0.1 / (Spam�� ����� ��) �Ǵ� 0.1 / (Ham�� ����� ��)�� �Ѵ�.
                                else con_ham_p = freq_ham[k] / ((spam + ham) * p_ham); // p(w_i|y)

                                if (freq_spam[k] == 0) con_spam_p = 0.1 / spam;
                                else con_spam_p = freq_spam[k] / ((spam + ham) * p_spam);// p(w_i| y)

                                        printf("P(%s | Ham) = %.3f, P(%s | Spam) = %.3f\n", tok, con_ham_p, tok, con_spam_p);

                                        prob_ham *= con_ham_p;  // p(Spam) �� p(w_i|Spam)
                                         
                                        prob_spam *= con_spam_p; // p(Ham) �� p(w_i|Ham)
                                           

                            
                                        cnt++;
                            }

                                

                       
                            
                    }
                    tok = strtok(NULL, " "); // �ɰ��� 

                }


                printf("\nP( Ham | '%s') : % .3f", test_sen, prob_ham); // ���� Ȯ�� ���
                printf("\nP(Spam | '%s') : % .3f\n\n", test_sen, prob_spam);  


                if (prob_ham > prob_spam) printf("This message is HAM\n");
                else if (prob_ham < prob_spam) printf("This message is SPAM\n");

                fclose(fp); // ���� �ݾ��� 

                for (i = 0; i < cnt_word; i++) { // �����Ҵ� ���� 

                    free(*(words + i));

                }
                free(words);
                free(freq_spam);
                free(freq_ham);

                rewind(stdin); // �Է¹��� ����� 
                scanf("%c", &go_menu); // enter �Է��� ��ٸ�. 
                rewind(stdin);


                system("cls");


            }



            else if (strcmp(com, "exit") == 0) { // exit�� �Է��ϸ� 
                
                
                return 0; // ���� 
            }

            else { // 3���� Ŀ�ǵ� �̿��� ���� �Է��ϸ� 

                error = 1;
                printf("Error: Invalid input"); // error ���� ��� 
                Sleep(1000);
                system("cls");
            }

        }
    }

    return 0;
}

void print_menu() {

    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("CSED 101\n");
    printf("Assignment 3\n\n");

    printf("Naive Bayesian Classifier for Spam Filtering\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Command: ");
}

char* process_str(char* str) { // ���ڿ� �����ϴ� �Լ� 

    int i;

    for (i = 0; str[i] != NULL; i++) {

        if (str[i] >= 'A' && str[i] <= 'Z')   str[i] = str[i] + 32; // �빮���� ��� 
        else if ((str[i] >= 33 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 96) || str[i] >= 123) str[i] = 32; // Ư�������� �ƽ�Ű �ڵ忡 �ش� 
    }
    return str;
}



void dic_sort(char** words, int cnt_word, int* freq_spam, int* freq_ham) {

    int i, j;
    char temp[30];
    int tp1, tp2;

    for (i = 0; i < cnt_word; i++) { // 2�� for��

        for (j = 0; j < cnt_word - 1; j++) {


            tp1 = 0;
            tp2 = 0;

            if (strcmp(*(words + j), *(words + j + 1)) > 0) { // ������ ����:strcmp�� �˰����� ���� ������ ���� �ܾ �� ũ�ٸ� 

                strcpy(temp, *(words + j)); 
                strcpy(*(words + j), *(words + j + 1));
                strcpy(*(words + j + 1), temp); // ���ڿ����� swap �Լ� ��� ���� 

                tp1 = *(freq_spam + j);
                *(freq_spam + j) = *(freq_spam + j + 1); // swap �Լ��� �˰���� ����. 
                *(freq_spam + j + 1) = tp1;

                tp2 = *(freq_ham + j);
                *(freq_ham + j) = *(freq_ham + j + 1); // swap �Լ��� �˰���� ����. 
                *(freq_ham + j + 1) = tp2;


            }
        }

    }
}

void train(char** words, int* freq_spam, int* freq_ham, char* fname, int* ham, int* spam) {

    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {// ������ �ҷ����� �� �������� �� 
        printf("Error: File does not exist");  
        Sleep(1000);
        return 0;
    }

    FILE* stats = fopen("stats.txt", "w");

    char sentence[1000]; // �Է¹޴� ���� 
    char p_sentence[1000];
    int mem_size = 5;  // �ʱ� �޸� ������ 
    char label[30]; // label
    char text[1000]; // text
    char* tok = NULL; // strtok�� ����� ������ ���ڿ� ���� 
    int cnt_word = 0; // �ܾ� ���� 
    int i = 0; int k, l; // for�� �����ִ� ���� 
    int init_text = 0; // text�� ������ �� ��° �ܾ����� �����ϴ� ����  
    char go_menu;

    // �����Ҵ� �κ� 

    words = (char**)calloc(mem_size, sizeof(char*));
    freq_spam = (int*)calloc(mem_size, sizeof(int));
    freq_ham = (int*)calloc(mem_size, sizeof(int));

    while (!feof(fp)) {

        init_text = i; // text�� ������ �� ��° �ܾ����� ��������. 

        fgets(sentence, 1000, fp); // �� �� �޾ƿ� 

        if (sentence[strlen(sentence) - 1] == '\n') sentence[strlen(sentence) - 1] = NULL; // enterŰ ������ 

        strcpy(p_sentence, process_str(sentence));  // ���ڿ� �����ؼ� ���� 
        strcpy(label, (strtok(p_sentence, "\t"))); // label ���� 
        strcpy(text, (strtok(NULL, "\t"))); // text ���� 


        tok = strtok(text, " ");  // words �����Ҵ� ; words[�ܾ� ����][�ܾ� ����(�ܾ�� �޶���)]; 

        while (tok != NULL) { // strtok ���� NULL�� �ƴ� ���� (FILE���� ���̻� �ɰ� ���� ���� ����)


            if (strlen(tok) >= 2 && strlen(tok) <= 20) { // �ܾ� ���� 2~20���� ��ȿ��. 

                if (i >= mem_size) { // �ʱ� mem_size = 5 

                    mem_size *= 2; // ���Ҵ��� memory ũ��  

                    words = (char**)realloc(words, mem_size * sizeof(char*)); // 2��� ���Ҵ��ϴ� �κ� 
                    freq_spam = (int*)realloc(freq_spam, mem_size * sizeof(int));
                    freq_ham = (int*)realloc(freq_ham, mem_size * sizeof(int));

                    for (k = (mem_size / 2); k < mem_size; k++) { // realloc �� �κ��� 0���� �ʱ�ȭ 
                        *(freq_spam + k) = 0;
                        *(freq_ham + k) = 0;
                    }
                }



                for (k = 0; k < i; k++) {

                    if ((strcmp(*(words + k), tok)) == 0) {

                        if (strcmp(label, "spam") == 0) {
                            for (l = init_text; l < i; l++) { // init_text(text�� ù ��) ���� for�� ���� 
                                if (((strcmp(*(words + l), tok)) == 0)) freq_spam[l]--; // �ߺ��Ǵ� ���� ������ �� 1 ���� 
                            }
                            freq_spam[k]++; // �� 1 ������ 
                        }
                        if (strcmp(label, "ham") == 0) { 
                            for (l = init_text; l < i; l++) { // init_text(text�� ù ��) ���� for�� ����
                                if (((strcmp(*(words + l), tok)) == 0)) freq_ham[l]--; // �ߺ��Ǵ� ���� ������ �� 1 ���� 
                            }
                            freq_ham[k]++; // �� 1 ������ 
                        }
                        break;
                    }
                }

                if (k == i) {
         
               
                    *(words + i) = (char*)calloc(strlen(tok)+4, sizeof(char)); // words�� i��° �࿡ �ܾ� ���̸�ŭ �����Ҵ� (strlen+4 �̻��� �����Ҵ��� �ؾ� ������ ���� �ʴµ� ������ �� �𸣰ڽ��ϴ�..)

                    strcpy(*(words + i), tok); // ���ڿ� ���� 

                    if (strcmp(label, "spam") == 0) { // label�� spam�̸� �� 1 ���� 
                        
                        freq_spam[i]++;
                    }

                    if (strcmp(label, "ham") == 0) { // label�� ham�̸� �� 1 ����

                        freq_ham[i]++;
                    }
                    cnt_word++; // �ܾ� ���� ���� 

                    i++; // for�� �� �� ���Ҵ��� ���� 
                }
            }

            tok = strtok(NULL, " ");  // �ܾ �ϳ� �ɰ��� ������ 

        }
   
        if (strcmp(label, "spam") == 0) (*(spam))++; // �����Ͱ� ����Ű�� spam �� ������ 
        else if (strcmp(label, "ham") == 0) (*(ham))++; // �����Ͱ� ����Ű�� hpam �� ������ 

    }

    dic_sort(words, cnt_word, freq_spam, freq_ham); // ���������� �������� 

    fprintf(stats, "Ham:%d, Spam:%d\n", *ham, *spam); 

    printf("\nAfter training...\n");
    printf("Ham:%d, Spam:%d\n", *ham, *spam);

    for (i = 0; i < cnt_word; i++) {

        fprintf(stats, "%s,%d,%d\n", *(words + i), *(freq_ham + i), *(freq_spam + i)); // ������ ������ ����� txt ���Ͽ� ������� 
        printf("%s,%d,%d\n", *(words + i), *(freq_ham + i), *(freq_spam + i)); //������ ������ ����� ������� 
    }

    fclose(fp); fp = NULL; // �б� ���� �ݾ��� 
    fclose(stats); stats = NULL; // ���� ���� �ݾ��� 
  
    free(freq_ham);
    free(freq_spam);
    free(words); // �����Ҵ� �������� 
    
    rewind(stdin); // �Է¹��� ��� 
    scanf("%c", &go_menu); // enter �Է¹��� 

 
}



