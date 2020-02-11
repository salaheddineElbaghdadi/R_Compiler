#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 10


FILE *f;
char buffer[MAXSIZE];
char nextChar;
int offssetBuffer ;


typedef enum _tokens{ID_TOKEN,NUM_TOKEN,PROGRAM_TOKEN,CONST_TOKEN,VAR_TOKEN,IF_TOKEN,
THEN_TOKEN,WHILE_TOKEN,DO_TOKEN,PV_TOKEN,PT_TOKEN,EG_TOKEN,PLUS_TOKEN,MOINS_TOKEN,
MULT_TOKEN,DIV_TOKEN,VIR_TOKEN,AFF_TOKEN,INF_TOKEN,INFEG_TOKEN,SUP_TOKEN,SUPEG_TOKEN,DIFF_TOKEN,
PO_TOKEN,PF_TOKEN,ERREUR_TOKEN,COMMENTAIRE,NEWLINE_TOKEN,FUNCTION_TOKEN,AND_TOKEN,OR_TOKEN,NOT_TOKEN
}tokens;

typedef enum {
 ERR_CAR_INC, ERR_FICH_VID, ERR_ID_LONG,ERR_CONST_LONG,ERR_COMMENTAIRE
}Erreurs;

Erreurs ERR;

typedef struct {
		 Erreurs  CODE_ERR;
		 char mes[40];
	}TErreurs;

TErreurs MES_ERR[5]={{ERR_CAR_INC,"caractère inconnu"}, {ERR_FICH_VID,"fichier vide"},{ERR_ID_LONG,"IDF très long" },
{ERR_CONST_LONG,"constante très longue" },{ERR_COMMENTAIRE,"commentaire incorrect" }};
 

tokens token ;

typedef enum _bool{
	false,true
}bool;
bool getNextToken();
void getNextChar();
bool isNUmber();
bool isSpecial();
bool isChar();
bool isEOF();
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

void readNumber();
void readWord();
void readSpecial();
void readError();
void readSeparator();


void assignToken() {
	if (strcmp(buffer,"var")==0){
		token =VAR_TOKEN;
	}
	else if (isBufferNUmber()) 	token= NUM_TOKEN;
	else if(!stricmp(buffer, "if" ))   token=IF_TOKEN;
    else if(!stricmp(buffer, "then")) token=THEN_TOKEN;
    else if(!stricmp(buffer, "while")) token=WHILE_TOKEN;
    else if(!stricmp(buffer, "do")) token=DO_TOKEN;
    else if(!stricmp(buffer, "function")) token=FUNCTION_TOKEN;
    else if(strlen(buffer)>20) {ERR=ERR_ID_LONG;Erreur(ERR);
	}else{
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


int main(int argc,char**argv){

	f=fopen("code.R","r");
	clearBuffer();
	while(getNextToken()){
		printf("   %s   \n",buffer);
		assignToken();
		clearBuffer();
	}

	printf("  fin   !!");

	return 0;
}

void getNextChar(){
	nextChar= getc(f);
}

bool getNextToken(){
	do {
	if(isNUmber())
		readNumber();
	else if (isChar())
		readWord();
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

bool isNUmber(){
	if(nextChar>='0' && nextChar<='9'){
		return true ;
	}
	else
		return false;	
}

bool isChar(){
	if(nextChar>='a' && nextChar<='z'){
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
        case '+': token=PLUS_TOKEN;	return true;   
        case '-': token=MOINS_TOKEN;	return true;        
        case '*': token=MULT_TOKEN;	return true;
        case '/': token=DIV_TOKEN;	return true;
        case '#': token=COMMENTAIRE;	return true;
        case '&': token=AND_TOKEN;	return true;
        case '|': token=OR_TOKEN;	return true;
        case '!': token=NOT_TOKEN;	return true;
        case ':': getNextChar();
                      if(nextChar=='='){
                            token=AFF_TOKEN;	return true;
                      }else{
                            ERR=ERR_CAR_INC;Erreur(ERR);	return true;}
        case ':': getNextChar();
                      if(nextChar=='='){	
                            token=AFF_TOKEN;	return true;
                      }else{
                            ERR=ERR_CAR_INC;Erreur(ERR);	return true;}
        case '<': getNextChar();
                      if(nextChar=='='){
                            token=INFEG_TOKEN;	return true;
                      }else if(isChar()||isNUmber()||isSeparator()){
                            token=INF_TOKEN ;	return true;
                      }else if(Car_Cour=='>'){
                         token=DIFF_TOKEN;	return true;
                      }else {ERR=ERR_CAR_INC;Erreur(ERR);	return true;}
        case '>': getNextChar();
                      if(nextChar=='='){
                            token=SUPEG_TOKEN;	return true;
                      }else if(isChar()||isNUmber()||isSeparator()){
                            token=SUP_TOKEN;	return true;
                      }else {ERR=ERR_CAR_INC;Erreur(ERR);	return true;}
        case '(': token=PO_TOKEN;	return true;
        case ')': token=PF_TOKEN;	return true;
	
        default : ERR=ERR_CAR_INC;
                      Erreur(ERR);


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

	}while (isChar() || isNUmber())
}


void readNumber(){
	do {
			addChartoBuffer();
			getNextChar();

	}while ( isNUmber())
}



void readSpecial(){
	do {
			addChartoBuffer();
			getNextChar();

	}while ( isSpecial())
}

void readError(){
	printf (" \t error\n");
	getNextChar();
}

void readSeparator(){
	do {
			getNextChar();

	}while(isSeparator())
}