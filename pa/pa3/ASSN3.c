// 20210716 최대현 ASSN3
// Visual Studio 2019에서 개발하였습니다. 

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

void print_menu(); // 메뉴를 출력하는 함수 

char* process_str(char* str); //mystrlower + 특수문자를 공백 처리하는 함수 
 
void dic_sort(char** words, int cnt_word, int* freq_spam, int* freq_ham); // 사전식으로 words를 정렬하고, 그 순서에 맞춰 각 빈도들의 순서를 바꿔줌. 

void train(char** words, int* freq_spam, int* freq_ham, char* fname, int* ham, int* spam);

char* mystrlower(char* str);

int main() {

    int ham = 1; int spam = 1;
    char fname[MAX_FILE_NAME]; // file이름
    char com[10];
    char go_menu; // menu로 돌아가는 space를 입력받기 위한 변수 
    int error = 1; // 가장 바깥 while문을 돌리는 변수 
    int cnt_word = 0; // 단어 갯수 
    int i = 0; // for문 돌리는 변수 
    int k; // for문 돌리는 변수 
    // int train_cnt = 0;
    char* tok; //strtok를 통해 쪼갠 문자열을 임시로 저장하는 변수 
    char** words = NULL; //동적할당해서 사용할, 단어들을 담는 2차원 메모리
    int* freq_spam = NULL; // 동적할당해서 사용할, 단어들이 spam label에서 나오는 빈도를 저장할 1차원 메모리
    int* freq_ham = NULL; // 동적할당해서 사용할, 단어들이 ham label에서 나오는 빈도를 저장할 1차원 메모리

    while (error != 0) { // error = 0 이면 종료됨 

        while (1) { // 무한루프를 break를 통해 빠져나감. 

            print_menu(); 
            scanf("%s", com);

            mystrlower(com); // 대소문자 관계없이 철자가 같으면 같게 입력받음. 

            if (strcmp(com, "train") == 0) {

                ham = 0; spam = 0;
                printf("File name: ");
                scanf("%s", fname); // 파일 이름을 입력받음 

                
                train(words, freq_spam, freq_ham, fname, &ham, &spam); //train 시킴 
        
                system("cls"); 

            }

            else if (strcmp(com, "test") == 0) { //test할 때 

                FILE* fp = fopen("stats.txt", "r"); //train한 결과인 stats.txt를 읽기 모드로 열어줌. 

                if (fp == NULL) {  //stats.txt가 없을 때 
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

                // 동적 할당 부분
                words = (char**)calloc(mem_size, sizeof(char*)); 
                freq_spam = (int*)calloc(mem_size, sizeof(int));
                freq_ham = (int*)calloc(mem_size, sizeof(int));


                fgets(str, 1000, fp); // 맨 윗 줄 받아옴 
                if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = NULL;

                tok = strtok(str, ":"); // : 전까지 나온 것은 버림 

                tok = strtok(NULL, ":"); 
                ham = atoi(tok); // 정수로 만들어주면서 나머지는 사라짐  (즉, ham의 빈도)

                tok = strtok(NULL, ":"); // 뒤의 숫자 값만 남음  (spam의 빈도)
                spam = atoi(tok);

                fgets(str, 1000, fp); // 한 줄 받아옴 

                if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = NULL; // enter 없애줌 

       
                while (strlen(str) >= 5) { // 받아온 한 줄의 길이는 최소 5이다. 

                    if (i >= mem_size) { 

                        mem_size *= 2; // 메모리 크기를 2배로 늘림 

                        words = (char**)realloc(words, mem_size * sizeof(char*)); // 재할당 
                        freq_spam = (int*)realloc(freq_spam, mem_size * sizeof(int));
                        freq_ham = (int*)realloc(freq_ham, mem_size * sizeof(int));

                        for (k = (mem_size / 2); k < mem_size; k++) { //realloc한 부분을 0으로 초기화 
                            *(freq_spam + k) = 0;
                            *(freq_ham + k) = 0;
                        }
                    }


               
                    tok = strtok(str, ","); 
                    *(words + i) = (char*)calloc(strlen(tok) + 1, sizeof(char));
                    strcpy(*(words + i), tok);


                    tok = strtok(NULL, ","); //, 단위로 쪼개서 ham 빈도 넣어줌
                    *(freq_ham + i) = atoi(tok); 

                    tok = strtok(NULL, ","); //, 단위로 쪼개서 spam 빈도 넣어줌  
                    *(freq_spam + i) = atoi(tok);

                    i++;


                    fgets(str, 1000, fp); // 한 줄 받아옴 
                    if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = NULL;
                }

                char sen[1000];
                char test_sen[1000];

                float p_ham = (float)ham / (ham + spam); //  p(ham)
                float p_spam = (float)spam / (ham + spam); //  p(spam)
                float con_ham_p = 1; float con_spam_p = 1; 
                float prob_ham = p_ham; float prob_spam = p_spam;
                char test_word[50][50] = { 0 }; // test한 문자열을 넣어주는 배열 

             
              

                printf("Enter a message: ");
                rewind(stdin);

                fgets(sen, 100, stdin);

                if (sen[strlen(sen) - 1] == '\n') sen[strlen(sen) - 1] = NULL;

                strcpy(test_sen, sen);

               process_str(sen);


                tok = strtok(sen, " ");


                printf("\nP(Ham) = %.3f, P(Spam) = %.3lf\n", p_ham, p_spam); //  spam 확률을 출력 


                int cnt = 1;

                while (tok != NULL) { // 쪼갤 것이 없을 때까지
   
                    if (strlen(tok) >= 2) { //단어 길이가 2 이상인 경우에만 처리 

                        for (k = 0; k < cnt; k++) {

                            if (strcmp(test_word[k], tok) == 0) break; // 입력한 문자 내에 중복되는 단어가 있다면 while문 break 
                        }

                        if (k < cnt) {
                            tok = strtok(NULL, " "); //토크나이징 후 다음 while문으로 넘어감 
                            continue; 
                        }

                        else strcpy(test_word[k], tok); 

                        for (k = 0; k < i; k++) {

                            if (strcmp(*(words + k), tok) == 0) {
                                
                                break;
                            }

                        }

                            if (k < i) { 
                               

                                if (freq_ham[k] == 0) con_ham_p = 0.1 / ham;  //통계에 포함되었으나 개수가 0인 경우 확률 값이 0이 되므로, 이 경우 확률 값을 0.1 / (Spam인 경우의 수) 또는 0.1 / (Ham인 경우의 수)로 한다.
                                else con_ham_p = freq_ham[k] / ((spam + ham) * p_ham); // p(w_i|y)

                                if (freq_spam[k] == 0) con_spam_p = 0.1 / spam;
                                else con_spam_p = freq_spam[k] / ((spam + ham) * p_spam);// p(w_i| y)

                                        printf("P(%s | Ham) = %.3f, P(%s | Spam) = %.3f\n", tok, con_ham_p, tok, con_spam_p);

                                        prob_ham *= con_ham_p;  // p(Spam) ∏ p(w_i|Spam)
                                         
                                        prob_spam *= con_spam_p; // p(Ham) ∏ p(w_i|Ham)
                                           

                            
                                        cnt++;
                            }

                                

                       
                            
                    }
                    tok = strtok(NULL, " "); // 쪼개줌 

                }


                printf("\nP( Ham | '%s') : % .3f", test_sen, prob_ham); // 최종 확률 출력
                printf("\nP(Spam | '%s') : % .3f\n\n", test_sen, prob_spam);  


                if (prob_ham > prob_spam) printf("This message is HAM\n");
                else if (prob_ham < prob_spam) printf("This message is SPAM\n");

                fclose(fp); // 파일 닫아줌 

                for (i = 0; i < cnt_word; i++) { // 동적할당 해제 

                    free(*(words + i));

                }
                free(words);
                free(freq_spam);
                free(freq_ham);

                rewind(stdin); // 입력버퍼 비워줌 
                scanf("%c", &go_menu); // enter 입력을 기다림. 
                rewind(stdin);


                system("cls");


            }



            else if (strcmp(com, "exit") == 0) { // exit을 입력하면 
                
                
                return 0; // 종료 
            }

            else { // 3가지 커맨드 이외의 것을 입력하면 

                error = 1;
                printf("Error: Invalid input"); // error 문구 출력 
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

char* process_str(char* str) { // 문자열 가공하는 함수 

    int i;

    for (i = 0; str[i] != NULL; i++) {

        if (str[i] >= 'A' && str[i] <= 'Z')   str[i] = str[i] + 32; // 대문자인 경우 
        else if ((str[i] >= 33 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 96) || str[i] >= 123) str[i] = 32; // 특수문자의 아스키 코드에 해당 
    }
    return str;
}



void dic_sort(char** words, int cnt_word, int* freq_spam, int* freq_ham) {

    int i, j;
    char temp[30];
    int tp1, tp2;

    for (i = 0; i < cnt_word; i++) { // 2중 for문

        for (j = 0; j < cnt_word - 1; j++) {


            tp1 = 0;
            tp2 = 0;

            if (strcmp(*(words + j), *(words + j + 1)) > 0) { // 사전식 정렬:strcmp와 알고리즘이 같기 때문에 앞의 단어가 더 크다면 

                strcpy(temp, *(words + j)); 
                strcpy(*(words + j), *(words + j + 1));
                strcpy(*(words + j + 1), temp); // 문자열에서 swap 함수 기능 구현 

                tp1 = *(freq_spam + j);
                *(freq_spam + j) = *(freq_spam + j + 1); // swap 함수의 알고리즘과 같음. 
                *(freq_spam + j + 1) = tp1;

                tp2 = *(freq_ham + j);
                *(freq_ham + j) = *(freq_ham + j + 1); // swap 함수의 알고리즘과 같음. 
                *(freq_ham + j + 1) = tp2;


            }
        }

    }
}

void train(char** words, int* freq_spam, int* freq_ham, char* fname, int* ham, int* spam) {

    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {// 파일을 불러오는 데 실패했을 때 
        printf("Error: File does not exist");  
        Sleep(1000);
        return 0;
    }

    FILE* stats = fopen("stats.txt", "w");

    char sentence[1000]; // 입력받는 문장 
    char p_sentence[1000];
    int mem_size = 5;  // 초기 메모리 사이즈 
    char label[30]; // label
    char text[1000]; // text
    char* tok = NULL; // strtok한 결과를 저장할 문자열 변수 
    int cnt_word = 0; // 단어 개수 
    int i = 0; int k, l; // for문 돌려주는 인자 
    int init_text = 0; // text의 시작이 몇 번째 단어인지 저장하는 변수  
    char go_menu;

    // 동적할당 부분 

    words = (char**)calloc(mem_size, sizeof(char*));
    freq_spam = (int*)calloc(mem_size, sizeof(int));
    freq_ham = (int*)calloc(mem_size, sizeof(int));

    while (!feof(fp)) {

        init_text = i; // text의 시작이 몇 번째 단어인지 저장해줌. 

        fgets(sentence, 1000, fp); // 한 줄 받아옴 

        if (sentence[strlen(sentence) - 1] == '\n') sentence[strlen(sentence) - 1] = NULL; // enter키 지워줌 

        strcpy(p_sentence, process_str(sentence));  // 문자열 가공해서 저장 
        strcpy(label, (strtok(p_sentence, "\t"))); // label 저장 
        strcpy(text, (strtok(NULL, "\t"))); // text 저장 


        tok = strtok(text, " ");  // words 동적할당 ; words[단어 개수][단어 길이(단어마다 달라짐)]; 

        while (tok != NULL) { // strtok 값이 NULL이 아닌 동안 (FILE에서 더이상 쪼갤 것이 없는 동안)


            if (strlen(tok) >= 2 && strlen(tok) <= 20) { // 단어 길이 2~20까지 유효함. 

                if (i >= mem_size) { // 초기 mem_size = 5 

                    mem_size *= 2; // 재할당할 memory 크기  

                    words = (char**)realloc(words, mem_size * sizeof(char*)); // 2배로 재할당하는 부분 
                    freq_spam = (int*)realloc(freq_spam, mem_size * sizeof(int));
                    freq_ham = (int*)realloc(freq_ham, mem_size * sizeof(int));

                    for (k = (mem_size / 2); k < mem_size; k++) { // realloc 한 부분을 0으로 초기화 
                        *(freq_spam + k) = 0;
                        *(freq_ham + k) = 0;
                    }
                }



                for (k = 0; k < i; k++) {

                    if ((strcmp(*(words + k), tok)) == 0) {

                        if (strcmp(label, "spam") == 0) {
                            for (l = init_text; l < i; l++) { // init_text(text의 첫 줄) 부터 for문 돌림 
                                if (((strcmp(*(words + l), tok)) == 0)) freq_spam[l]--; // 중복되는 값이 있으면 빈도 1 빼줌 
                            }
                            freq_spam[k]++; // 빈도 1 더해줌 
                        }
                        if (strcmp(label, "ham") == 0) { 
                            for (l = init_text; l < i; l++) { // init_text(text의 첫 줄) 부터 for문 돌림
                                if (((strcmp(*(words + l), tok)) == 0)) freq_ham[l]--; // 중복되는 값이 있으면 빈도 1 빼줌 
                            }
                            freq_ham[k]++; // 빈도 1 더해줌 
                        }
                        break;
                    }
                }

                if (k == i) {
         
               
                    *(words + i) = (char*)calloc(strlen(tok)+4, sizeof(char)); // words의 i번째 행에 단어 길이만큼 동적할당 (strlen+4 이상의 동적할당을 해야 오류가 나지 않는데 이유를 잘 모르겠습니다..)

                    strcpy(*(words + i), tok); // 문자열 복사 

                    if (strcmp(label, "spam") == 0) { // label이 spam이면 빈도 1 증가 
                        
                        freq_spam[i]++;
                    }

                    if (strcmp(label, "ham") == 0) { // label이 ham이면 빈도 1 증가

                        freq_ham[i]++;
                    }
                    cnt_word++; // 단어 개수 세줌 

                    i++; // for문 몇 번 돌았는지 세줌 
                }
            }

            tok = strtok(NULL, " ");  // 단어를 하나 쪼개서 가져옴 

        }
   
        if (strcmp(label, "spam") == 0) (*(spam))++; // 포인터가 가리키는 spam 값 더해줌 
        else if (strcmp(label, "ham") == 0) (*(ham))++; // 포인터가 가리키는 hpam 값 더해줌 

    }

    dic_sort(words, cnt_word, freq_spam, freq_ham); // 사전식으로 정렬해줌 

    fprintf(stats, "Ham:%d, Spam:%d\n", *ham, *spam); 

    printf("\nAfter training...\n");
    printf("Ham:%d, Spam:%d\n", *ham, *spam);

    for (i = 0; i < cnt_word; i++) {

        fprintf(stats, "%s,%d,%d\n", *(words + i), *(freq_ham + i), *(freq_spam + i)); // 사전식 정렬한 결과를 txt 파일에 출력해줌 
        printf("%s,%d,%d\n", *(words + i), *(freq_ham + i), *(freq_spam + i)); //사전식 정렬한 결과를 출력해줌 
    }

    fclose(fp); fp = NULL; // 읽기 파일 닫아줌 
    fclose(stats); stats = NULL; // 쓰기 파일 닫아줌 
  
    free(freq_ham);
    free(freq_spam);
    free(words); // 동적할당 해제해줌 
    
    rewind(stdin); // 입력버퍼 비움 
    scanf("%c", &go_menu); // enter 입력받음 

 
}



