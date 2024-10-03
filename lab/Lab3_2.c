#include<stdio.h>
char upperToLower(char c){
	return c+32;
	
}
int getPosition(char c){
	return c-96;
}

int main(){
	
	int order;
	char a, low;
	printf("Input a character in Uppercase:");
	scanf("%c", &a);
	low = upperToLower(a);
	order = getPosition(low);
	printf("Lowercase of Entered character is %c\n", low);
	printf("Position of '%c' in English Alphabets is %d", low, order);
	

	
	
	return 0;
}
