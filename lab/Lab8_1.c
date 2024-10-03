#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 20
#include<stdio.h>
void print_matrix(int size, int arr[][MAX_SIZE]);
int main(){
	int size,i,j; 
	int arr[MAX_SIZE][MAX_SIZE]={0};
	printf("Enter the size of square : ");
	scanf("%d", &size);
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(i+j<size-1) arr[i][j] = 1;
			else if(i+j==size-1) arr[i][j] = 0;					
			else arr[i][j] = -1;
							
		}
	}
	
	print_matrix(size, arr);
	
	return 0;
}

void print_matrix(int size, int arr[][MAX_SIZE]){
	int i,j;
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf(" %2d", arr[i][j]);	
		}
		printf("\n");
	}
	
}			
