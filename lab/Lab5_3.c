#include<stdio.h>
int main(){ 
	
	int num, sum, digit;
	sum = 0;
	printf("Enter a number : ");
	scanf("%d", &num);
	
	while(num !=0){
		digit = num % 10;
		num = num / 10;
		sum = sum + digit;
	}
	printf("The sum of the digits is %d", sum);
	
	return 0;
}
