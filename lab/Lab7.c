#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define SIZE 10 
int seqSearch(int a[], int size, int num);
int main(){
	int i; int a[SIZE], result,num;
	printf("Input 10 interger values: ");
	for(i=0; i<SIZE; i++){
		scanf("%d", &a[i]);
	}
	
	printf("Entered number is       : ");
	for(i=0; i<SIZE; i++){
		printf("%d ", a[i]);
	}
	printf("\nInput an interger that you want to find: ");
	scanf("%d", &num);
	result = seqSearch(a, SIZE, num);
	if(result==-1) printf("Not Found");
	else printf("The index of %d is %d", num, result);
	return 0;
}

int seqSearch(int a[], int size, int num){
	int i, result;
	for(i=0; i<size; i++){
		
		if(a[i]==num){
		result = i; 
		i=(SIZE+1); // for문 빠져나오게 함  
	}
		else result = -1;
	}
	return result; 
}
