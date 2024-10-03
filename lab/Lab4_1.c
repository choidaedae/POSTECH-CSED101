#include<stdio.h>
#include<math.h>

void triangle(int a, int b, float *perimeter,  float *area);

void print(float perimeter, float area);

int main(){
	
	int a, b;
	float perimeter, area;
	printf("Enter two integer sides: ");
	scanf("%d %d", &a, &b);
	triangle(a, b, &perimeter, &area);
	print(perimeter, area);	
	
	return 0;
}

void triangle(int a, int b, float *perimeter,  float *area){
	*perimeter = sqrt(a*a+b*b)+a+b;
	*area = 0.5*a*b;
	
	return;
}

void print(float perimeter, float area){
	
	printf("Perimeter: %f\n", perimeter);
	printf("Area: %f", area);	
	
	return;
}
