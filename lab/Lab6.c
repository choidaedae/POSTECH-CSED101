#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
int main(){
	FILE *infile;
	FILE *outfile;
	
	int stuID, mid, final;
	int cnt=0;
	float sum = 0;
	float score;
	float avg = 0;
	char grade; 
	infile = fopen("score.txt", "r");
	outfile = fopen("report.txt", "w");
	
	fprintf(outfile, "=============================\n");
	fprintf(outfile, "  ÇÐ¹ø             ÃÑÁ¡(ÇÐÁ¡)\n");
	fprintf(outfile, "=============================\n");
	
	while(fscanf(infile, "%d %d %d", &stuID, &mid, &final) == 3){
		cnt++;
		score = mid* 0.4 + final* 0.6; 
		sum = sum + score;
		if(score>=90) grade = 'A';
		else if(score>=80) grade = 'B';
		else if(score>=70) grade = 'C';
		else if(score>=60) grade = 'D';
		else grade = 'F';
		fprintf(outfile, "%d             %.1f(%c)\n", stuID, score, grade);
	}
	
	avg = sum / cnt;
	fprintf(outfile, "=============================\n");
	fprintf(outfile, "  Æò±Õ               %.1f      \n", avg);
	fprintf(outfile, "=============================\n");
	fclose(infile);
	fclose(outfile);

	

	
	return 0;
}
