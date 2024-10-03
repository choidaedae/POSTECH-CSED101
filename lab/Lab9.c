#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void partial_print(int *arr_start, int size);
int partial_sum(int *arr_start, int *arr_end);

int main(){
	int a[10];
	int s,e,i,sum;
	printf("Enter 10 elements of array: ");
	for(i=0; i<10; i++){
		scanf("%d", (a+i));
	}
	printf("Numbers that you enter are: ");
	partial_print(a, 10);
	
	printf("\nEnter the starting and ending index: ");
	scanf("%d %d", &s, &e);
	
	sum = partial_sum(a+s, a+s+e);
	printf("sum from array[%d] to array[%d] is %d\n", s,e, sum);
	printf("Partial array output: ");
	partial_print(a+s, e-s+1);
	
	
	
	return 0;	
}

void partial_print(int *arr_start, int size){
	int i;
	for(i=0; i<size; i++){
		printf("%d ", *(arr_start+i));
	}
	
}

int partial_sum(int *arr_start, int *arr_end){
	int i;
	int sum=0;
	for(i=0; i<arr_end-arr_start; i++){
		sum+=*(arr_start+i)	;	
	}
	return sum;
}
