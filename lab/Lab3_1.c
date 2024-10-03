#include<stdio.h>

int add(int x, int y){
	return x+y;
	
	
}
float average(float x, float y){

	return (x+y)/2; 
	
}

void printResults(int x, int y, int sum, float avg){
	printf("The sum of %d and %d is %d\n", x, y, sum);
	printf("The average of numbers is %.1f", avg);
	
	return;
}
int main(){
	int x, y, sum;
	float avg;
	printf("Enter two intergers: ");
	scanf("%d %d", &x, &y);
	sum = add(x,y);
	avg = average(x,y);
	
	printResults(x, y, sum, avg);
	
	return 0;
}
