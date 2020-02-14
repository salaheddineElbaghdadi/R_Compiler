
#include<stdio.h>
#include<stdlib.h>
#include"global.h"
#include"lexical.h"

int main(int argc,char**argv){
	init();
	f=fopen("code.R","r");
	clearBuffer();
	get_next_char();
	while(get_next_token()){
		
		printf(" %d",token);
		printf("   %s   \n",buffer);
		
		//clearBuffer();
	}

	printf("  fin   !!\n");

	return 0;
}