
#include<stdio.h>
#include<stdlib.h>
#include"global.h"
#include"lexical.h"


bool PROG();
bool BLOC();
bool END();
bool EXPRESSION();
bool LOOP();
bool FUNCTION();
bool DECISION();
bool OPERATION();
bool IDENTIF();
bool OPERATOR();
bool CALLFUNCTION();
bool DATA();


int main(int argc,char**argv){
	init();
	f=fopen(argv[1],"r");
	clearBuffer();
	get_next_char();
	get_next_token();
	if(PROG()){
		printf("fin!!");
	}
	else{
		printf("syntax error!");
	}
	
	//printf("  fin   !!\n");

	return 0;
}

bool PROG(){
	if(BLOC()){
		while(BLOC());
		if(END()){
			return true;
		}
		get_next_token();
	}
	else if (END()){
		
		return true;
	}
	else
	{
		return false;
	}
	
}

bool BLOC(){
	if(EXPRESSION()){
		get_next_token();
		return true;
		
	}
	else if(LOOP()){
		get_next_token();
		return true;
	}
	else if(FUNCTION()){
		get_next_token();
		return true;
	}
	else if (DECISION()){
		get_next_token();
		return true;
	}
	else{
		return false;
	}

}
bool END(){
	if (token==EOF_TOKEN){
		//printf("EOF");
		return true;
	}
}
bool EXPRESSION(){
	if(token==ID_TOKEN){
		get_next_token();
		if(token==LEFT_ASSIGN_TOKEN){
			get_next_token();
			if(OPERATION()){
				get_next_token();
				return true;
				
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

bool LOOP(){
	return false;
}

bool FUNCTION(){
	return false;
}
bool DECISION(){
	return false;
}

bool IDENTIF(){
	if(token==ID_TOKEN || CALLFUNCTION() || DATA()){
		get_next_token();
		return true;
	}
	else{
		return false;
	}
}

bool OPERATION(){
	if(IDENTIF()){
		while(OPERATOR()){
			if(!IDENTIF()){
				return false;
			}
		}
		get_next_char();
		if(is_end_of_line()){
			get_next_token();
			return true;
		}
		else{
			return false;
		}
		
	}
	if(token==OPENING_PARENTHESES_TOKEN){
		get_next_token();
		if(OPERATION()){
			while(OPERATION);
			if(token=CLOSING_PARENTHESES_TOKEN){
				get_next_token();
				return true;
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


bool OPERATOR(){
	switch(token){
		case EQUAL_TOKEN:{
			get_next_token();
			return true;
		}
		case LESS_TOKEN:{
			get_next_token();
			return true;
		}
		case GREATER_TOKEN:{
			get_next_token();
			return true;
		}
		case PLUS_TOKEN:{
			get_next_token();
			return true;
		}
		case SUBSTRACT_TOKEN:{
			get_next_token();
			return true;
		}
		case MULTIPLY_TOKEN:{
			get_next_token();
			return true;
		}
		
		case DEVIDE_TOKEN:{
			get_next_token();
			return true;
		}
		case LESS_EQUAL_TOKEN:{
			get_next_token();
			return true;
		}
		case GREATER_EQUAL_TOKEN:{
			get_next_token();
			return true;
		}
		case NOT_TOKEN:{
			get_next_token();
			return true;
		}
		case AND_TOKEN:{
			get_next_token();
			return true;
		}
		case OR_TOKEN:{
			get_next_token();
			return true;
		}
		case NOT_EQUAL_TOKEN:{
			get_next_token();
			return true;
		}
		case LOGICAL_OR_TOKEN:{
			get_next_token();
			return true;
		}
		case LOGICAL_AND_TOKEN:{
			get_next_token();
			return true;
		}
		case MODULO_TOKEN:{
			get_next_token();
			return true;
		}
		case QUOTIENT_TOKEN:{
			get_next_token();
			return true;
		}
		case POWER_TOKEN:{
			get_next_token();
			return true;
		}

	}
}

bool DATA(){
	return false;
}

bool CALLFUNCTION(){
	return false;
}