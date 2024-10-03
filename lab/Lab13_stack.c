/* 
 * �ۼ���: 2021�� 12�� 7�� 
 * ��  ��: 20210716 
 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STRING 20

// ���� ��� ����ü NODE ����

typedef struct node{
	char data; 
	struct node* next; 
	
}NODE;


typedef struct stack{
	
	int count; 
	NODE *top;
	
}STACK;

void printStack(STACK *s);
int push(STACK *s, char data);
int pop(STACK *s, char *data);
int isEmpty(STACK *s);

int main()
{
	int len, i, ioRes;
	char str[MAX_STRING];
	STACK *stack;
	stack = (STACK*) malloc(sizeof(STACK));


	if (!stack)
	{
		printf("���� �Ҵ� ����\n");
		return 100;
	}

	stack->count = 0;
	stack->top = NULL; 



	while (1)
	{
		printf(">> ");
		ioRes = scanf("%s", str);

		if (ioRes == EOF) // ctrl + Z Z
			break;

		len = strlen(str);
		for (i = 0; i < len; i++)
		{
			push(stack, str[i]);
		}
		printStack(stack);

	} // while

	free(stack);
	printf("bye!\n");

	return 0;
} // main

void printStack(STACK *s)
{
	char data;

	printf("   ");
	while (pop(s, &data)) {
	
		printf("%c", data);
	}
	printf("\n\n");

} // printStack

// push ������ 1, ���н� 0�� ��ȯ
int push(STACK *s, char data)
{
	NODE *temp;
	int success = 1;

	temp = (NODE *)malloc(sizeof(NODE));

	if (!temp) // ���� �Ҵ� ���н�
		success = 0;
	else
	{
		temp->data = data; 
		temp->next = s->top;
		s->top = temp;
		s->count++;

	}

	return success;
} // push

// pop ������ 1, ���н� 0�� ��ȯ
int pop(STACK *s, char *data)
{
	NODE *temp;
	int success = 1;


	if (!isEmpty(s)) // ������ ��� ���� ������(isEmpty �Լ� ȣ��)
	{
		
		temp = (NODE *)malloc(sizeof(NODE));
		*data = s->top->data;
		temp = s->top; 
		s->top = temp ->next;
		s->count--;
		
		free(temp); // ��� ����
	}
	else
		success = 0;

	return success;
} // pop

// ������ ��� ������ 1, �׷��� ������ 0�� ��ȯ
int isEmpty(STACK *s)
{
	return s->top == NULL; 
} // isEmpty
