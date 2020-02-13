#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "lexical.h"

#define MAXSIZE 20


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
  NOTHING = -1,

  // keyword tokens
  IF_TOKEN = 0,
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
  OPENING_PARENTHESES_TOKEN,
  CLOSING_PARENTHESES_TOKEN,

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
} tokens;

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


void assignToken(tokens _token) {
  if (_token == NOTHING) {
    for (int i = 0; i < KEYWORDS_LIST_SIZE; i++) {
      if (strcmp(buffer, keywords[i]) == 0) {
        token = i;
        return;
      }
    }
    token = ID_TOKEN;
    return;
  }
  token = _token;
}

void addChartoBuffer(){
	buffer[offssetBuffer++]= nextChar;
	buffer[offssetBuffer]= '\0'; 
}

void clearBuffer(){
	offssetBuffer=0;
	buffer[offssetBuffer]= '\0';
}

void get_next_char(){
	nextChar= getc(f);
}

bool get_next_token(){
	
	do {
	  clearBuffer();
	  if(is_number()) {
      //printf("is reading number\n");
	    read_number();
    }
	  else if (is_legal_char()) {
      //printf("is reading legal character\n");
	    read_word();
    }
	  else if( is_special()) {
      //printf("is reading special\n");
	    read_special();
    }
	  else if (isSeparator()) {
      //printf("is reading separator\n");
	    read_separator();
    }
	  else if(is_EOF()) {
      //printf("is reading EOF\n");
	    return false;
    }
	  else
	    read_error();
	} while(offssetBuffer ==0);
	return true;
}

bool is_number(){
	if(nextChar>='0' && nextChar<='9'){
		return true ;
	}
	else
		return false;	
}

bool is_char(){
	if((nextChar>='a' && nextChar<='z')| (nextChar>='A' && nextChar<='Z') ){
		return true ;
	}
	else
		return false;	
}

bool is_legal_char() {
  if (nextChar == '_' || is_char())
    return true;
  else
    return false;
}

bool is_special(){
	switch(nextChar){
		case '+':
      return true;
    case '-':
      return true;
    case '*':
      return true;
    case '/':
      return true;  
    case '%':
      return true;
    case '^':
      return true;
    case '>':
      return true;
    case '<':
      return true;
    case '=':
      return true;
    case '!':
      return true;
    case '|':
      return true;       
    case '&':
      return true;
    case '(':
      return true;
    case ')':
      return true;
	}
	return false;

}

bool is_EOF(){
  if(nextChar == EOF ){
    return true ;
  }
  else
    return false;	
}

void read_word(){
	do {
			addChartoBuffer();
			get_next_char();

	}while (is_char() || is_number() || is_legal_char());
  assignToken(NOTHING);
}


void read_number(){
	do {
			addChartoBuffer();
			get_next_char();

	}while ( is_number());
  assignToken(NUMERIC_TOKEN);
}



void read_special() {
  do {
    addChartoBuffer();
    get_next_char();
  } while (is_special());
  assignToken(NOTHING);
}

void read_error(){
  printf (" \t error\n");
  get_next_char();
}

void read_separator(){
  do {
    get_next_char();
  } while(isSeparator());
  assignToken(SEPARATOR_TOKEN);
}

void read_EOF() {
  assignToken(EOF_TOKEN);
}

int main(int argc,char**argv){

	f=fopen("code.R","r");
	clearBuffer();
	get_next_char();
	while(get_next_token()){
		
    printf(" buffer  %s\n", buffer);
		printf(" %d",token);
		printf("   %s   \n",buffer);
		
		//clearBuffer();
	}

	printf("  fin   !!\n");

	return 0;
}

