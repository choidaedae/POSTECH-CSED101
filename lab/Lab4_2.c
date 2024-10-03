#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void randData(int *a, int *b, int *c){

	*a= rand()%76 + 5;
	*b= rand()%76 + 5;	
	*c= rand()%76 + 5;
	
}

float arithmeticMean(int a, int b){
	return (float)(a+b)/2;
	
}

float geometricMean(int a, int b){
	return (float)sqrt(a*b);
	
}

float harmonicMean(int a, int b){
	return (float)((2*a*b)/(a+b));
	
}

int main(){
	
	int A1, A2, A3;
	int B1, B2, B3;
	srand(time(NULL));
	randData(&A1, &A2, &A3);
	randData(&B1, &B2, &B3);
	
	printf("arithmeticMean(%d, %d) => %.2f\n", A1, B1, arithmeticMean(A1, B1));
	printf("geometricMean(%d, %d) => %.2f\n", A2, B2, arithmeticMean(A2, B2));
	printf("harmonicMean(%d, %d) => %.2f", A3, B3, arithmeticMean(A3, B3));
	
	
	
}
