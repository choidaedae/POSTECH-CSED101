#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int find_minmax(int *arr, int size, int *max, int *min);

int main(){
	
	int size, i;
	int *arr;
	int min=100000; int max=0;
	printf("Enter array size: ");
	scanf("%d", &size);
	arr = (int * )malloc(sizeof(int)*size);
	for(i=0; i<size; i++){
		scanf("%d", (arr+i));
	}
	printf("Enter numbers are \n");
	for(i=0; i<size; i++){
		printf("%d ", *(arr+i));
	}
	find_minmax(arr, size, &max, &min);
	printf("\nMaximum is %d\n", max);
	printf("Minimum is %d\n", min);
	min = 1000000; max = 0;
	printf("\nEnter changed array size: ");
	scanf("%d", &size);
	
	arr = (int *)realloc(arr, sizeof(int)*size);
	for(i=0; i<size; i++){
		scanf("%d", (arr+i));
	}
	
	printf("Enter numbers are \n");
	for(i=0; i<size; i++){
		printf("%d ", *(arr+i));
	}
	find_minmax(arr, size, &max, &min);
	printf("\nMaximum is %d\n", max);
	printf("Minimum is %d", min);
	
	
	
}

int find_minmax(int *arr, int size, int *max, int *min){
	
	int i;
	
	for(i=0; i<size; i++){
		if(*(arr+i)>*max) *max = *(arr+i);
		if(*(arr+i)<*min) *min = *(arr+i);	
	}
}
