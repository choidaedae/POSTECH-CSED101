#define _CRT_SECURE_NO_WARNINGS
#define MAX 6
#include<stdio.h>
void bubble_sort(int a[], int size);
void input_array(int a[], int size);
void print_array(int a[], int size);
void swap(int *x, int *y);

int main(){
	
	int ary[MAX];
	printf("Input integer numbers to be sorted: ");
	input_array(ary, MAX);
	printf("  Unsorted:	");
	print_array(ary, MAX);
	
	printf("---------------------------------------------\n");
	bubble_sort(ary, MAX);
	printf("---------------------------------------------\n");
	
	printf(" Sorted: 	");
	print_array(ary, MAX);
	
	return 0;
		
}

void input_array(int a[], int size){
	int i;
	for(i=0; i<size; i++){
		scanf("%d", &a[i]);
	}
}
void print_array(int a[], int size){
	int i;
	for(i=0; i<size; i++){
		printf("%2d  ", a[i]);
	}
	printf("\n");
	
}
void bubble_sort(int a[], int size){
	int i,j;
	for(i=0; i<size-1; i++){
		for(j=size-1; j>i; j--){
			if(a[j]<a[j-1]) swap(&a[j], &a[j-1]);
		}
						printf("[step %d]:	", i+1);
						print_array(a, MAX);
	}
}

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}
