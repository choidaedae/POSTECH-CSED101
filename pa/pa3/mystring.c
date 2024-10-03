#include <stddef.h>

int mystrlen(char* str){
	int i, len;
	len = 0;
	for(i=0; str[i]!=NULL; i++){
		len++;
	}
	
	return len; 
}

int mystrcmp(char* str1, char* str2){
	int i=0; 
	while(str1[i]!=NULL || str2[i]!=NULL){
		
		if(str1[i]==str2[i]) i++; 
		else if(str1[i]>str2[i]) return 1;
		else if(str1[i]<str2[i]) return -1;
	}
	
	return 0;

}

char* mystrcpy(char* toStr, char* fromStr){
	int i=0;
	
	while((fromStr[i])!=NULL){
		toStr[i]=fromStr[i];
		i++;
	}
	toStr[i]=0;
	return toStr;
}

char* mystrlower(char* str){
	int i;
	
	for(i=0; str[i]!=NULL; i++){	
	
		if(str[i]>='A' && str[i]<='Z')	str[i] = str[i] + 32; 		
	}
	return str;
	
}
