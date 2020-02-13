#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"

#define MAXSIZE 10


FILE *f;
char buffer[MAXSIZE];
char nextChar=' ';
int offssetBuffer ;


/*
typedef enum _tokens{ID_TOKEN,NUM_TOKEN,PROGRAM_TOKEN,CONST_TOKEN,VAR_TOKEN,IF_TOKEN,
REPEAT_TOKEN,WHILE_TOKEN,DO_TOKEN,PV_TOKEN,PT_TOKEN,EG_TOKEN,PLUS_TOKEN,MOINS_TOKEN,
MULT_TOKEN,DIV_TOKEN,VIR_TOKEN,AFF_DIRECT_TOKEN,AFF_EGAL_TOKEN,AFF_INDIRECT_TOKEN,INF_TOKEN,INFEG_TOKEN,SUP_TOKEN,SUPEG_TOKEN,DIFF_TOKEN,
PO_TOKEN,PF_TOKEN,ERREUR_TOKEN,COMMENTAIRE,NEWLINE_TOKEN,FUNCTION_TOKEN,AND_TOKEN,OR_TOKEN,NOT_TOKENWHILE_TOKEN,
FOR_TOKEN,IN_TOKEN,NEXT_TOKEN,BREAK_TOKEN,NOT_TOKEN
}tokens;
*/

typedef enum _tokens {
  // Other tokens ??
  NOTHING = -1

  // keyword tokens
  IF_TOKEN,
  ELSE_TOKEN,
  REPEAT_TOKEN,
  WHILE_TOKEN,
  FUNCTION_TOKEN,
  FOR_TOKEN,
  IN_TOKEN,
  NEXT_TOKEN,
  BREAK_TOKEN,
  TRUE_TOKEN,
  FALSE_TOKEN,
  NULL_TOKEN,
  INF_TOKEN,
  NAN_TOKEN,
  NA_INTEGER_TOKEN,
  NA_REAL_TOKEN,
  NA_COMPLEX_TOKEN,
  NA_CHARACTER_TOKEN,

  // Symbol tokens
  PLUS_TOKEN,
  SUBSTRACT_TOKEN,
  MULTIPLY_TOKEN,
  DEVIDE_TOKEN,
  MODULO_TOKEN,
  QUOTIENT_TOKEN,
  POWER_TOKEN,
  LESS_TOKEN,
  GREATER_TOKEN,
  EQUAL_TOKEN,
  LESS_EQUAL_TOKEN,
  GREATER_EQUAL_TOKEN,
  NOT_EQUAL_TOKEN,
  AND_TOKEN,
  OR_TOKEN,
  NOT_TOKEN,
  LOGICAL_AND_TOKEN,
  LOGICAL_OR_TOKEN,
  LEFT_ASSIGN_TOKEN,
  RIGHT_ASSIGN_TOKEN,

  // Special tokens
  ID_TOKEN,
  STRING_TOKEN,
  NUMERIC_TOKEN,
  INTEGER_TOKEN,
  COMPLEX_TOKEN,

  // Separator token
  SEPARATOR_TOKEN,
  
  EOF_TOKEN,
  COMMENT_TOKEN
}

tokens token ;


bool isSeparator(){
	switch (nextChar){
		case ' ': return true;
		case '\n':	return true;
		case '\r' :	return true;
		case ';' :	return true;
		default :
			return false;
	}

}

bool isBufferNUmber(){
	if(buffer[0]>='0' && buffer[0]<='9'){
		return true;
	}return false;
}


void assignToken() {
	if (strcmp(buffer,"var")==0){
		token =VAR_TOKEN;
	}
	else if (isBufferNUmber()) 	token= NUM_TOKEN;
	else if(!strcmp(buffer, "if" ))   token=IF_TOKEN;
    else if(!strcmp(buffer, "repeat")) token=REPEAT_TOKEN;
    else if(!strcmp(buffer, "while")) token=WHILE_TOKEN;
    else if(!strcmp(buffer, "do")) token=DO_TOKEN;
    else if(!strcmp(buffer, "for")) token=FOR_TOKEN;
    else if(!strcmp(buffer, "in")) token=IN_TOKEN;
    else if(!strcmp(buffer, "next")) token=NEXT_TOKEN;
    else if(!strcmp(buffer, "break")) token=BREAK_TOKEN;
    else if(!strcmp(buffer, "function")) token=FUNCTION_TOKEN;
	else{
		token=ID_TOKEN;
	}

}

void addChartoBuffer(){
	buffer[offssetBuffer++]= nextChar;
	buffer[offssetBuffer]= '\0'; 
}

void clearBuffer(){
	offssetBuffer=0;
	buffer[offssetBuffer]= '\0';
}

void getNextChar(){
	nextChar= getc(f);
}

bool getNextToken(){
	
	do {
	if(isNumber()){
		readNumber();
		assignToken();
	}
	else if (isChar()){
		readWord();
		assignToken();
	}
	else if( isSpecial())
		readSpecial();
	else if (isSeparator())
		readSeparator();
	else if(isEOF())
		return false;
	else
		readError();
		}while(offssetBuffer ==0);
	return true;
}

bool isNumber(){
	if(nextChar>='0' && nextChar<='9'){
		return true ;
	}
	else
		return false;	
}

bool isChar(){
	if((nextChar>='a' && nextChar<='z')| (nextChar>='A' && nextChar<='Z') ){
		return true ;
	}
	else
		return false;	
}

bool isSpecial(){
	switch(nextChar){
		case ';': token=PV_TOKEN;	return true;
        case '=': token=EG_TOKEN;	return true;
        case '.': token=PT_TOKEN;	return true;
        case '+': token=PLUS_TOKEN; return true;  

        case '-': token=MOINS_TOKEN ;	return true;
           
        

        case '*': token=MULT_TOKEN;	return true;
        case '/': token=DIV_TOKEN;	return true;
        case '#': token=COMMENTAIRE;	return true;
        case '&': token=AND_TOKEN;	return true;
        case '|': token=OR_TOKEN;	return true;
        case '!': addChartoBuffer(); getNextChar();
        	if(nextChar=='='){
        		token=DIFF_TOKEN;	return true;
        	}else{
        	 token=NOT_TOKEN;	return true;
        	}
                         
        case ':': getNextChar();
                      if(nextChar=='='){
                            token=AFF_EGAL_TOKEN;	return true;
                      }	return false;

        case '<': addChartoBuffer(); getNextChar();
                      if(nextChar=='='){
                            token=INFEG_TOKEN;	return true;
                      }else if(isChar()||isNumber()||isSeparator()){
                            token=INF_TOKEN ;	return true;
                      }
                      else if(nextChar=='-'){
                      		token = AFF_INDIRECT_TOKEN ;return true;}
                      return false;
        case '>':addChartoBuffer(); getNextChar();
                      if(nextChar=='='){
                            token=SUPEG_TOKEN;	return true;
                      }else if(isChar()||isNumber()||isSeparator()){
                            token=SUP_TOKEN;	return true;
                      }	return false;
        case '(': token=PO_TOKEN;	return true;
        case ')': token=PF_TOKEN;	return true;
	}
	return false;

}

bool isEOF(){
	if(nextChar == EOF ){
		return true ;
	}
	else
		return false;	
}

void readWord(){
	do {
			addChartoBuffer();
			getNextChar();

	}while (isChar() || isNumber());
}


void readNumber(){
	do {
			addChartoBuffer();
			getNextChar();

	}while ( isNumber());
}



void readSpecial(){
	do {
			addChartoBuffer();
			getNextChar();

	}while ( isSpecial());
}

void readError(){
	printf (" \t error\n");
	getNextChar();
}

void readSeparator(){
	do {
			getNextChar();
	}while(isSeparator());
}

int main(int argc,char**argv){

	f=fopen("code.R","r");
	clearBuffer();
	getNextChar();
	while(getNextToken()){
		
		printf(" %d",token);
		printf("   %s   \n",buffer);
		
		clearBuffer();
	}

	printf("  fin   !!");

	return 0;
}

