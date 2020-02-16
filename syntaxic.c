#include<stdio.h>
#include<stdlib.h>
#include"lexical.h"
#include"global.h"
#include"lexical.h"

bool PROG();
bool END();
bool BLOC();
bool DECISION();
bool OPERATION();
bool IDENTIF();
bool CALLFUNCTION();
bool OPERATOR();

void main(int argc,char**argv){
	f=fopen("code.R","r");
	clearBuffer();
	get_next_char();
	get_next_token();
	if(PROG()){
		printf("fin!!\n");
	}
	else{
		printf("syntax error\n");
	}

}

bool PROG(){
	printf("-->PROG\n");
	if(BLOC()){
		while(BLOC());
		if(END()){
			return true;
		}
		else{
			return false;
		}
	}
	else if(END()){
		return true;
	}
	else{
		return false;
	}
}

bool BLOC(){

	if(OPERATION()){
		get_next_token();
		if(token==EOL_TOKEN){
			get_next_token();
			while(token==EOL_TOKEN){
				get_next_token();
			}
			return true;
		}
	}
	else{
		return false;
	}
}

bool END(){
	if(token==EOF_TOKEN){
		printf("fin du fichier\n");
		return true;
	}
	else{
		return false;
	}
}
bool CALLFUNCTION(){
	return false;
}

bool IDENTIF(){
	if(token==NUMERIC_TOKEN){
		get_next_token();
		return true;
	}
	else if(token==ID_TOKEN){
		get_next_token();
		return true;
	}
	else if(token==CALLFUNCTION()){
		get_next_token();
		return true;
	}
	else{
		return false;
	}
}

bool OPERATOR(){
	switch(token){
		case EQUAL_TOKEN:{get_next_token();return true;}
		case LESS_TOKEN:{get_next_token();return true;}
		case LESS_EQUAL_TOKEN:{get_next_token();return true;}
		case GREATER_TOKEN:{get_next_token();return true;}
		case GREATER_EQUAL_TOKEN:{get_next_token();return true;}
		case PLUS_TOKEN:{get_next_token();return true;}
		case SUBSTRACT_TOKEN:{get_next_token();return true;}
		case MULTIPLY_TOKEN:{get_next_token();return true;}
		case DEVIDE_TOKEN:{get_next_token();return true;}
		case NOT_TOKEN:{get_next_token();return true;}
		case AND_TOKEN:{get_next_token();return true;}
		case LOGICAL_AND_TOKEN:{get_next_token();return true;}
		case OR_TOKEN:{get_next_token();return true;}
		case LOGICAL_OR_TOKEN:{get_next_token();return true;}
		case NOT_EQUAL_TOKEN:{get_next_token();return true;}
		case MODULO_TOKEN:{get_next_token();return true;}
		case POWER_TOKEN:{get_next_token();return true;}
		case QUOTIENT_TOKEN:{get_next_token();return true;}
		default:{
			return false;
		}
		

	}
}

bool OPERATION(){
	if(IDENTIF()){
		get_next_token();
		while(OPERATOR()){
			if(IDENTIF()){
				get_next_token();
				return true;
			}
			else{
				return false;
			}
		}
		get_next_token();
		return true;
	}
	else{
		return false;
	}
}




bool DECISION(){
	if(token==IF_TOKEN){
		get_next_token();
		if(token==OPENING_PARENTHESES_TOKEN){
			get_next_token();
			if(OPERATION()){
				if(token==CLOSING_PARENTHESES_TOKEN){
					get_next_token();
					if(token==EOL_TOKEN){
						get_next_token();
						if(token==OPENING_CURLY_BRACKETS_TOKEN){
							get_next_token();
							if(BLOC()){
								if(token==CLOSING_CURLY_BRACKETS_TOKEN){
									get_next_token();
									printf("function syn correcte\n");
								}
								else{
									return false;
								}
							}
							else{
								return false;
							}
						}
						else{
							return false;
						}
					}
					else if(token==OPENING_CURLY_BRACKETS_TOKEN){
							get_next_token();
							if(BLOC()){
								if(token==CLOSING_CURLY_BRACKETS_TOKEN){
									get_next_token();
									printf("function syn correcte\n");
								}
								else{
									return false;
								}
							}
							else{
								return false;
							}
			
						}
						else{
							return false;
						}
					
					
				}
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}
