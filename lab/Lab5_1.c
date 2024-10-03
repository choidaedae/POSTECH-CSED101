#include<stdio.h>

float calc_average(int a, int b);

char calc_grade(float avg);

int main(){
	
	int mid, final;
	float avg;
	char grade;
	
	printf("Enter you midterm score: ");
	scanf("%d", &mid);
	printf("Enter you midterm score: ");
	scanf("%d", &final);
	avg = calc_average(mid, final);
	grade = calc_grade(avg);
	
	printf("Average = %.1f\n", avg);
	printf("Grade = %c", grade);
	
	return 0;
}

float calc_average(int a, int b){
	
	return (float)(a+b)/2;
	
}

char calc_grade(float avg){
	
	char grade; 
	
	if(avg>=90){
		grade = 'A';
		
	}
	
	else if (avg<90 && avg >= 80){
		grade = 'B';
		
	}
	
	else if (avg<80 && avg >= 70){
		grade = 'C';
		
	}
	
	else if (avg<70 && avg >= 60){
		grade = 'D';

	}
	
	else grade = 'F';
	
	return grade; 
	}
